import os, base64, tempfile

# Python wrapper so I can use tempdir
print("Please enter the base64 encoded payload")
print("Maximum decoded size is 32kb")
b64 = input()


payload = base64.b64decode(b64)
if len(payload) > 32 * 1024:
    print("Payload too big")
    os.exit(-1)
tempdir = tempfile.TemporaryDirectory()
path = f"{tempdir.name}"
binpath = f"{path}/payload"
with open(binpath, "wb") as f:
    f.write(payload)
    os.chmod(path, 0o755)
    os.chown(path, 1042, 1042)
    os.chmod(binpath, 0o755)
    os.chown(binpath, 1042, 1042)

os.spawnv(os.P_WAIT, "./sandbox", ["sandbox", path])

