Here's a short writeup of the ChaCha60 challenge.

The key generation uses a 64 bit master key to generate 3 keys of 32 bits each. To do so, the master key is multiplied with `m1`, `m2`, and `m3` (performed modulo 2).

To see the vulnerability, instead of consider 3 separate linear functions from 64 bits to 32 bits, we consider one big linear function from 64 bits to 96 bits. This big linear function can be expressed using the matrix `M` which is build by concatenating `M1`, `M2`, and `M3` vertically. In sagemath, we can do it this as follows:
```python
with np.load('matrices.npz') as f:
    m1 = matrix(GF(2), f.get('m1'))
    m2 = matrix(GF(2), f.get('m2'))
    m3 = matrix(GF(2), f.get('m3'))
m = block_matrix(3, 1, [m1, m2, m3])
print(m.rank()) # m.rank() == 32
```
This matrix now can be multiplied onto a 64 bit vector (the master key) to generate all 3 keys. In sagemath, this might be done as follows:
```python
base_key = random_vector(GF(2), 64)
expanded_key = m * base_key
```

When analyzing this 96x64 matrix `M`, we can see properties of the expanded key. In particular, the rank of the matrix is only 32. Therefore, only 2^32 expanded keys exist which can be brute-forced.

To brute-force the expanded key, we need to find a better representation of `M`. This can be done by using Gaussian elimination on the columns of `M`. This way, we get lots of zero columns that we can ignore. In sagemath, we can use the following code
```python
m = m.T.echelon_form()[:m.rank()].T
```

Then, we get a matrix of size 96x32. By iterating over all bitvectors of 32 bits, we create all expanded keys as `expanded_key = M * v` . We can identify the correct key by decrypting and comparing against the magic values of the PNG file format. This way, we only need to perform at most `2^32` trial decryptions.
