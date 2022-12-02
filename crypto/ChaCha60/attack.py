#!/usr/bin/env python3
from Crypto.Cipher import ChaCha20
import numpy as np
import tqdm
from binascii import hexlify
from time import time

from sage.all import GF, matrix, block_matrix

import pyximportcpp; pyximportcpp.install()
from bruteforce import *

import humanize


with np.load('matrices.npz') as f:
    m1 = matrix(GF(2), f.get('m1'))
    m2 = matrix(GF(2), f.get('m2'))
    m3 = matrix(GF(2), f.get('m3'))

m = block_matrix(3, 1, [m1,m2,m3])
m = m.T.echelon_form()[:m.rank()].T
m = np.array(m, dtype=np.uint8)
m = np.packbits(m, axis=0, bitorder='little')

with open('flag.png.enc', 'rb') as f:
    ct = f.read()

magic = b'\x89\x50\x4e\x47\x0d\x0a\x1a\x0a'
target = bytes((a ^ b for a, b in zip(ct[:8], magic)))

start = time()
keys = bruteforce(m, target)
end = time()
print(f'bruteforce took {humanize.precisedelta(end - start)}')
print('found key: ' + hexlify(bytes(keys)).decode())

k1 = bytes(keys[0:4]) + b'\0' * 28
k2 = bytes(keys[4:8]) + b'\0' * 28
k3 = bytes(keys[8:12]) + b'\0' * 28

nonce = b'\0' * 8
c1 = ChaCha20.new(key=k1, nonce=nonce)
c2 = ChaCha20.new(key=k2, nonce=nonce)
c3 = ChaCha20.new(key=k3, nonce=nonce)

pt = c3.encrypt(c2.encrypt(c1.encrypt(ct)))

with open('flag_rec.png', 'wb') as f:
    f.write(pt)
