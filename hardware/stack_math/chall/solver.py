from re import L, S
import sys
from Crypto.Util.number import getPrime
from sympy.ntheory import factorint, nextprime

# insructions from the stackmachine
INSTRUCTIONS = {
    "ZERO": "0",
    "ONE": "1",
    "DEC": "2",
    "INC": "3",
    "SWAP": "4",
    "DUP": "6",
    "ADD": "8",
    "SUB": "9",
    "MUL": "a",
    "NOP": "c",
    "DONE": "e",
}




# create hex string from instructions
def asm(s):
    out = ""
    for line in s.split("\n"):
        if line.startswith("#") or line.strip() == "":
            continue
        out += INSTRUCTIONS[line.strip()]

    return out




FACTOR_MAX = 13

# Some hardcoded and (hopefully) optimal paths to small primes

def create2(lastNumber):
    if lastNumber == 2:
        return "DUP\n" # 1 ins
    else:
        return "ONE\nINC\n" # 2 ins

def create3(lastNumber):
    if lastNumber == 2:
        return "DUP\nINC\n" # 2 ins
    elif lastNumber == 3:
        return "DUP\n" # 1 ins
    else:
        return create2(lastNumber) + "INC\n" # 3 ins, 

def create5(lastNumber):
    if lastNumber == 5:
        return "DUP\n" # 1 ins
    else: return create3(lastNumber) + "INC\nINC\n" #3 ins if 3, 4 if 2, 5 else

def create7(lastNumber):
    if lastNumber == 5:
        return "DUP\nINC\nINC\n" # 3 ins
    elif lastNumber == 2:
        return "DUP\nDUP\nINC\nMUL\nINC" # 5 if last is 2
    elif lastNumber == 3: 
        return "DUP\nDUP\nADD\nINC\n"
    else:
        return create2(lastNumber) + "DUP\nINC\nMUL\nINC\n" # 6 ins

def create11(lastNumber):
    if lastNumber == 5:
        return "DUP\nDUP\nADD\nINC\n"
    elif lastNumber == 3:
        return "DUP\nDUP\nMUL\nINC\nINC\n"
    elif lastNumber == 7:
        return "DUP\nDEC\nDUP\nMUL\nDEC\n"
    else:
        return create3(lastNumber) + "DUP\nMUL\nINC\nINC\n" # 7 ins

def create13(lastNumber):
    if lastNumber == 11:
        return "DUP\nINC\nINC\n"
    elif lastNumber == 7:
        return "DUP\nDUP\nMUL\nDEC\n"
    else:
        return create11(lastNumber) + "INC\nINC\n"
    
funs = {
    2: create2,
    3: create3,
    5: create5,
    7: create7,
    11: create11,
    13: create13,
}


#
def getEasyFactors(prime, depth = 0, lastnum = 0):
    ins = ""
    decfactors = factorint(prime - 1)
    incfactors = factorint(prime + 1)
    # Choose either prime+1 or prime-1, depending on which one has smaller factors
    factors = decfactors if max(decfactors) < max(incfactors) else incfactors
    
    for f in factors:
        n = factors[f]
        if f > FACTOR_MAX:
            # recursively create all smaller factors of non-hardcoded primes
            # remember the last number on the stack for optimizations
            lastnum, s = getEasyFactors(f, depth=depth+1, lastnum=lastnum)
            ins += s
            # Duplicate to have the right number of factors on stack
            ins += "DUP\n" * (n - 1)
        else:
            # Use hardcoded function to get a prime, using the last number on the stack for potential optimizations
            ins += funs[f](lastnum)
            # Duplicate to have the right number of factors on stack
            ins += "DUP\n" * (n - 1)

    # multiply all factors on stack
    ins += "MUL\n" * (sum(factors.values()) - 1)
    if factors == incfactors:
        ins += "DEC\n"
    else:
        ins += "INC\n"
    return prime, ins
    






import sys
import math
import threading
# Function o brute-force find the longest required instructions for primes in range.
# Obsolete, because 99% of primes can be generated in 85 instructions, as determined by verifier.py
def brute(start, end, id):
    current = nextprime(start)
    m = 0
    p = 0
    while current < end:
        
        prime, ins = getEasyFactors(current)
        
        l = len(ins.split("\n"))
        if m < l:
            m = l
            p = current

            print(f"Thread {id:2d}: Longest prime at {m:3d} instructions: {p:12d}   -   {math.ceil((current - start) / (end - start) * 100)}%")
            #
        current = nextprime(current)
    sys.stdout.write(f"Thread {id}: Final Longest prime at {m:03d} instructions: {p:012d}\n")
    sys.stdout.flush()



def verifyByBruteForce():
    start = (1 << 31)
    end = (1 << 32) - 1
    intervals = (end - start) // 16
    threads = []
    for i in range(16):
        t = threading.Thread(target=brute, args=(start + intervals * i, start + intervals * (i+1), i))
        t.start()
        threads.append(t)
        

    for t in threads:
        t.join()
    print("Done")


if __name__ == "__main__":
    verifyByBruteForce()
    


