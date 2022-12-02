import random
import string

def get_random_string(length):
    # choose from all lowercase letter
    letters = string.ascii_lowercase
    result_str = ''.join(random.choice(letters) for i in range(length))
    print("Random string of length", length, "is:", result_str)
    return result_str

##Generator
flag = "glacierctf{St1ck_3m_uP}"
ciphertext = "hZet3iAs1Rvi3eNwOvPlu4en5Sxiw"

for i in flag:
    ciphertext += i
    ciphertext += get_random_string(100)

print(ciphertext)

##Solution
flagformat= "glacierctf{"

for i in range(50):
    for j in range(1, len(ciphertext)//8):
        iterations = len(ciphertext)//j
        end_string = ""
        for k in range(iterations):
            if (k < len(flagformat) and ciphertext[i+k*j] != flagformat[k]):
                ##print("Break")
                break

            end_string += ciphertext[i+k*j]

            if (k == iterations-1):
                print("i = " + str(i) + "\n j = " + str(j))
                print(end_string)
