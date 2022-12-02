#!/usr/bin/python3

string = "glacierctf{W4SM_RE_1S_FUN}"
mask2 = "42"*len(string)

print(mask2)
encoded = ""
for counter in range(0,len(string),1):
    char_at_pos = (((counter << 3) & 0xFF) >> 2) & 0xFF ^ ord(string[counter]) ^ ord(mask2[counter])
    if(char_at_pos == 13):
      char_at_pos += 37
    elif(char_at_pos == 0):
      char_at_pos += 50
    # else:
    #     char_at_pos -= 3
    encoded += chr(char_at_pos)

print(encoded.encode())

xor_val = ""
for counter in range(0,len(string),1):
    char_at_pos = (((counter << 3) & 0xFF) >> 2) & 0xFF ^ ord(encoded[counter]) ^ ord(mask2[counter])
    if(char_at_pos == 13):
      char_at_pos += 37
    elif(char_at_pos == 0):
      char_at_pos += 50
    xor_val += chr(char_at_pos)

print(xor_val)
