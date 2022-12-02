#!/usr/bin/env python3
# -*- coding: utf-8 -*-
from pwn import *
import solver
from Crypto.Util.number import getPrime
exe = context.binary = ELF('obj_dir/VStackmachine')
context.log_level = 'info'

def start(argv=[], *a, **kw):
    '''Start the exploit against the target.'''
    if args.GDB:
        return gdb.debug([exe.path] + argv, gdbscript=gdbscript, *a, **kw)
    else:
        return process([exe.path] + argv, *a, **kw, level='error')

gdbscript = '''
tbreak main
continue
'''.format(**locals())

# -- Exploit goes here --



log.info("Starting solver verification")

tried = 0
toolong = 0
errors = 0

prog = log.progress(f"Status: ")

while True:
    prime = getPrime(32)

    p, s = solver.getEasyFactors(prime)
    s += "DONE\n"
    
    #print(len(s.split("\n")))
    assembled = solver.asm(s)
    #print(assembled)
    #print(prime, p)
    if len(assembled) > 85:
        toolong += 1
        continue
    io = start([str(prime)])
    
    io.sendline(assembled.encode("ascii"))
    #io.interactive()

    io.recvuntil(b"OUTPUT: ")
    out = io.recvline().decode("ascii").strip()
    #print(out)
    #print(prime)
    if int(out) != prime:
        errors += 1
    if len(assembled) > 85:
        toolong += 1
    tried += 1
    prog.status(f"Attempted {tried:9d} solves, {toolong:4d} were too long and {errors:4d} were wrong")


    io.close()

