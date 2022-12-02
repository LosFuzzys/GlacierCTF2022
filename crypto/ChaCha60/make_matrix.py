#!/usr/bin/env python3
from sage.all import matrix, block_matrix, GF
import numpy as np

if __name__ == '__main__':
    m1 = m2 = m3 = matrix.zero(GF(2), 32, 64)

    while not m1.rank() == m2.rank() == m3.rank() == 32:
        m = matrix.random(GF(2), 32, 64)

        a1 = matrix.random(GF(2), 32, 32)
        a2 = matrix.random(GF(2), 32, 32)
        a3 = matrix.random(GF(2), 32, 32)

        m1 = a1 * m
        m2 = a2 * m
        m3 = a3 * m

    mm = block_matrix(3, 1, [m1, m2, m3])
    assert mm.rank() <= 32 # this is the backdoor

    mm_ech = mm.transpose().echelon_form()[:mm.rank()].transpose()

    m1_np = m1.numpy(dtype=np.uint8)
    m2_np = m2.numpy(dtype=np.uint8)
    m3_np = m3.numpy(dtype=np.uint8)

    np.savez('matrices.npz', m1=m1_np, m2=m2_np, m3=m3_np)
