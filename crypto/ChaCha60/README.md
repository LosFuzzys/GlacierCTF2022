## Details

- Category: crypto
- Author:   fanosta


## Description

Name: ChaCha60

You receive an encrypted flag.png.
It is encrypted with 3 layers of ChaCha20.
The master key is a 64-bit random key wich is expanded into 3 separate 32-bit keys for the 3 ChaCha20 instances.
The key expansion is performed by multiplying the master key with a separate 64x32 matrix for each key:

$$ K_1 = M_1 \cdot K $$
$$ K_2 = M_2 \cdot K $$
$$ K_3 = M_3 \cdot K $$

## Solution

While each matrix on its own is strong (of full rank).
They are linearly dependent.
Concretely, if you consider the matrix $M$ built by concatenating the rows of $M_1$, $M_2$, and $M_3$, this matrix only has rank 32.

Therefore, in total there are only $2^{32}$ keys which can be feasibly bruteforced.
In essence, the matrices are chosen in such a way that if you know one of the keys, all the other are uniquely determined.

My implementation needed 9 minutes to bruteforce the 32-bits in a trial run.
Depending on the specific key it might take longer (up to ~45 minutes).
