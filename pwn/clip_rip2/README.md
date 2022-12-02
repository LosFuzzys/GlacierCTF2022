# ClipRip 2
## Details

- Category: PWN
- Author:   PaideiaDilemma

## Description

I knew that I would make a mistake at some point and copy a password with Ctrl-c.
However, that one was to be expected and the application itself is secure.
All my user input is handled securely, i think.

## Solution

1. leek some addresses via the format string vulnerability in argparse.hpp
2. enter a malicous entry that contains shell code to execute
   `listEntries` with `listSecure=true` (might be optional, but it is easier)
3. execute the shellcode with that fmtStr vuln, or directly leak the flag with the fmtStr vuln
4. enjoy flag.
