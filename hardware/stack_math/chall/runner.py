
#!/usr/bin/env python3
# -*- coding: utf-8 -*-
import os
import solver
from Crypto.Util.number import getPrime

# Checks if a correct solution is possible within the constraints
def getValidPrime():
    while True:
        prime = getPrime(32)

        p, s = solver.getEasyFactors(prime)
        s += "DONE\n"

        assembled = solver.asm(s)
        if len(assembled) < 85:
            return prime




if __name__ == "__main__":
    prime = getValidPrime()
    os.spawnv(os.P_WAIT, "/VStackmachine", ["VStackmachine", str(prime)])
    
    