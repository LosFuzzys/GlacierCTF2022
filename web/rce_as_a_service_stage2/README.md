# RCE as a Service (Stage 2)
## Details
- Category: Web
- Author: GEBIRGE

## Description

It came to our attention that a highly advanced `APT` targeted our `edge computing system`. In order to stop the attacks, we implemented *even more advanced* mitigations.

Think `seccomp`, but for the `web`!

Now there's **no** way an attacker could run malicious code, right?

(Goal: Read `flag.txt` at the filesystem's root.)

## Solution

You can have a look at `curl_stage2.org` for possible solution payloads.

Basically we now block `IO` operations through the standard library with a simple regex.
One possible solution could be to compile a custom .NET6 library that `does` use `System.IO` and load it dynamically *inside* our request to do the necessary flag reading operation.

Otherwise I've written extensively about it [here](https://gebir.ge/blog/privesc-part-1/) and [here](https://gebir.ge/blog/privesc-part-2/).
