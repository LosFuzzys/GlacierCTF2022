from typing import List

from pwn import process
from pwn import remote


def calc_primes(num: int, known_primes: List[int]):
    primes = []

    if num == 1:
        return primes
    for prime in known_primes:
        if num % prime == 0:
            new_number = num / prime
            return [prime] + calc_primes(new_number, known_primes)

    return [num]


def main() -> int:
    # target = process(["python", "server.py"])
    target = remote("pwn.glacierctf.com", 13370)

    # print(target.recvuntil(b"Name:"))
    target.recvuntil("Your Name:".encode())
    target.sendline("haxxor".encode())

    refund_codes = {}

    n = int(
        target.recvuntil(
            "Accountname".encode()
        ).decode().partition("Customernumber: ")[2].partition("\n")[0]
    )


    # buy the first item
    target.recvuntil(b"> ")
    target.sendline("2".encode())
    target.recvuntil(b"> ")
    target.sendline("Malduino".encode())

    refund_codes[2] = int(
        target.recvuntil(b"\nAccountname").decode().partition("Code:\n")[2].partition("\n")[0]
    )

    # get a refund to get the money back
    target.recvuntil(b"> ")
    print("...")
    target.sendline("3".encode())
    target.recvuntil(b"> ")
    target.sendline(f"{refund_codes[2]}".encode())
    target.recvuntil(b"> ")
    target.sendline("2".encode())

    # buy the second item
    target.recvuntil(b"> ")
    target.sendline("2".encode())
    target.recvuntil(b"> ")
    target.sendline("WIFI Deauther".encode())

    refund_codes[3] = int(
        target.recvuntil(b"\nAccountname").decode().partition("Code:\n")[2].partition("\n")[0]
    )

    # get a refund to get the money back
    target.recvuntil(b"> ")
    target.sendline("3".encode())
    target.recvuntil(b"> ")
    target.sendline(f"{refund_codes[3]}".encode())
    target.recvuntil(b"> ")
    target.sendline("3".encode())

    # buy the third item
    target.recvuntil(b"> ")
    target.sendline("2".encode())
    target.recvuntil(b"> ")
    target.sendline("Bluetooth Jammer".encode())

    refund_codes[5] = int(
        target.recvuntil(b"\nAccountname").decode().partition("Code:\n")[2].partition("\n")[0]
    )

    # get a refund to get the money back
    target.recvuntil(b"> ")
    target.sendline("3".encode())
    target.recvuntil(b"> ")
    target.sendline(f"{refund_codes[5]}".encode())
    target.recvuntil(b"> ")
    target.sendline("5".encode())

    # calc a new refund-code
    refund_amount = 1000000
    primes = calc_primes(refund_amount, refund_codes.keys())

    new_refund_code = 1

    for prime in primes:
        new_refund_code *= refund_codes[prime]

    new_refund_code = new_refund_code % n

    # try to get a refund with the self calculated refund code
    target.recvuntil(b"> ")
    target.sendline("3".encode())
    target.recvuntil(b"> ")
    target.sendline(f"{new_refund_code}".encode())
    target.recvuntil(b"> ")
    target.sendline(f"{refund_amount}".encode())

    # buy the flag
    target.recvuntil(b"> ")
    target.sendline("2".encode())
    target.recvuntil(b"> ")
    target.sendline("CTF-Flag".encode())

    target.recvuntil("Take this: ".encode())
    flag = target.recvuntil("\n".encode()).decode()

    print(f"Flag: {flag}")
    target.close()

    return 0


if __name__ == "__main__":
    raise SystemExit(main())
