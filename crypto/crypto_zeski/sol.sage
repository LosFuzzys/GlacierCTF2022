from Crypto.Util.number import *
from mt19937predictor import MT19937Predictor
from itertools import product

f = open("out.txt").readlines()

for line in f[1:]:
    exec(line)

pts = list(map(bytes_to_long, open("txt.txt", "rb").readlines()))

assert a*b == m

def roll_faster(x, y):
    if y == 0: return x
    return (int(pow(a, y, m))*x + b) % m

def get_y(ct, x):
    tmp = Mod(ct, b) / x
    y = tmp.log(Mod(a, b))
    return int(y)

def get_x(ct, y):
    return int(Mod(ct, b) / pow(a, y, b))

rand = []

for seed, ct, pt in zip(seeds, cts, pts):
    ct = ct ^^ pt
    y1 = get_y(ct, seed)
    x1 = get_x(ct, seed)
    assert roll_faster(x1, seed) == ct and roll_faster(seed, y1) == ct
    x = []
    y = []
    if  x1.bit_length() <= 512:
        x.append(x1)
        y.append(seed)
    if y1.bit_length() <= 512:
        x.append(seed)
        y.append(y1)
    rand.append(x)
    rand.append(y)

print([len(r) for r in rand])

for opt in product(*rand):
    rc = MT19937Predictor()

    for r in opt:
        rc.setrandbits(int(r), 512)

    x,y = rc.getrandbits(512), rc.getrandbits(512)

    flag = long_to_bytes(flag_ct ^^ roll_faster(x, y))
    if b"glacierctf" in flag:
        print(flag)
        break