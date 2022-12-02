## Details

- Category: REV
- Author:   hweissi

## Description

Steve's company has a custom service that executes binaries in a sandbox.
The admins changed his password though - can you still get in and leak theirs as revenge?

## Solution

1. "Guess" that the username is `steve` (should be easy with the description)
2. Try to log in as steve, get the password hash
3. Reverse the password hashing function (basically b64encode(AES_ECB(input ^ xor_key, static_password))
4. Log in as steve, it allows you to upload a b64encoded elf binary (has to be small, but there exist lightweight libc implementations, e.g. diet, or you can write custom code)
5. The FD of the password file is still open in the sandbox, so read the file and reverse the hash
