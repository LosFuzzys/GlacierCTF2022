#cython: language_level=3, annotation_typing=True, embedsignature=True, boundscheck=False, wraparound=False, cdivision=True
#distutils: language = c++

from libc.string cimport memset, memcpy, memcmp
from libc.stdio cimport printf
from cython.parallel cimport prange

ctypedef unsigned char uint8_t
ctypedef unsigned short uint16_t
ctypedef unsigned int uint32_t
ctypedef unsigned long uint64_t

ctypedef char int8_t
ctypedef short int16_t
ctypedef int int32_t
ctypedef long int64_t

cdef extern from "chacha20.hpp":
    cdef cppclass Chacha20Block:
        uint32_t state[16];

    cdef cppclass Chacha20:
        Chacha20Block block;
        uint8_t keystream8[64];
        size_t position;

        Chacha20(const uint8_t key[32], const uint8_t nonce[8], uint64_t counter) nogil
        void crypt(uint8_t *bytes, size_t n_bytes) nogil

import numpy as np


cdef void _matmul(uint8_t *res, const uint8_t[:, ::1] mat, uint32_t vec) nogil:
    cdef int i, j
    for i in range(12):
        res[i] = 0

    for i in range(32):
        if not (vec & (<uint32_t> 1 << i)):
            continue

        for j in range(12):
            res[j] ^= mat[j, i]

def matmul(const uint8_t[:, ::1] mat, uint32_t vec):
    cdef uint8_t[::1] res_view
    res = np.zeros(12, np.uint8)
    res_view = res
    _matmul(&res_view[0], mat, vec)
    return res


def bruteforce(const uint8_t [:, ::1] mat, const uint8_t[::1] target):
    cdef uint64_t i
    cdef uint8_t[12] keys
    cdef uint8_t[32] key
    cdef uint8_t[8] nonce
    cdef uint8_t[16] buf
    cdef Chacha20 *cipher = NULL
    cdef uint8_t[::1] res_view

    res = np.zeros(12, np.uint8)
    res_view = res

    assert mat.shape[0] == 12 and mat.shape[1] <= 32
    assert target.shape[0] <= 16

    memset(key, 0, sizeof(key))
    memset(nonce, 0, sizeof(nonce))

    for i in range(1ULL << mat.shape[1]):
        if i & ((1 << 24) - 1) == 0:
            printf("0x%08llx / 0x%08llx\n", <long long int>i, 1ULL << mat.shape[1])

        _matmul(keys, mat, i)
        memset(buf, 0, sizeof(buf))


        memcpy(&key[0], &keys[0], 4)
        cipher = new Chacha20(key, nonce, 0)
        cipher.crypt(buf, sizeof(buf))
        del cipher

        memcpy(&key[0], &keys[4], 4)
        cipher = new Chacha20(key, nonce, 0)
        cipher.crypt(buf, sizeof(buf))
        del cipher

        memcpy(&key[0], &keys[8], 4)
        cipher = new Chacha20(key, nonce, 0)
        cipher.crypt(buf, sizeof(buf))
        del cipher

        if memcmp(buf, &target[0], target.shape[0]) == 0:
            #with gil:

            for i in range(12):
                res_view[i] = keys[i]
            return res
