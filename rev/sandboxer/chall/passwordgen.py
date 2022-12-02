import base64
import sys
from Crypto.Cipher import AES

def byte_xor(ba1, ba2):
    return bytes([_a ^ _b for _a, _b in zip(ba1, ba2)])

xor_key = b"\x01\x35\xa7\x73\x3f\x55\x57\xc1\xa9\xac\x73\xf8\x09\x95\x9c\xe1\x2e\x0a\x70\xe3\xc2\x5b\x69\xbb\x0c\x39\xca\xbb\x31\x02\x2c\xc9";
aes_key = b"\xec\x12\x0d\x58\x47\x09\xc7\xca\x50\xe5\x7d\x08\x4f\x59\x28\xf4"

def hashpass(string):
    assert(len(string) <= 32)
    b_s = string.encode("ascii")

    fixed = b_s + b"\0" * (32 - len(b_s))
    print(len(fixed))


    cipher = AES.new(aes_key, AES.MODE_ECB)

    ct = byte_xor(xor_key, fixed)



    ret = cipher.encrypt(ct)
    print(base64.b64encode(ret))

def rev_hash(b):
    cipher = AES.new(aes_key, AES.MODE_ECB)
    pt = cipher.decrypt(b)
    plain = byte_xor(xor_key, pt)
    return plain


if len(sys.argv) == 2:
    hashpass(sys.argv[1])
else:
    print(rev_hash(base64.b64decode(sys.argv[2])))
