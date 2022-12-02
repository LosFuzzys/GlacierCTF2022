f = open("ciphertext.txt", "r")
ciphertext = f.read()

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
