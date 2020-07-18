import sys
from cs50 import get_string
from cs50 import get_int

# Prompt user for key
if len(sys.argv) == 2:
    for j in sys.argv[1]:
        if j.isalpha() == 0:
            print("Error")
            break
        elif sys.argv[1].isalpha():
            s = get_string("Plaintext: ")
            break
else:
    print("Error")

key = sys.argv[1]
a = ord('a')
b = ord('A')
k = 0
print("ciphertext: ", end="")

# Check each character in the plaintext
for i in s:
    # Check if each character is alphabetical
    if i.isalpha():
        if i.islower():
            # Keep track of key
            k %= len(key)
            # Each character is converted to digit
            p = ord(str.lower(key[k])) - a
            # Transfer ASCII to alphabetical index
            i = ((ord(i) - a) + p) % 26
            # Transfer alphabetical to ASCII
            i = chr(i + a)
            print(i, end="")
        elif i.isupper():
            k %= len(key)
            p = ord(str.upper(key[k])) - b
            i = ((ord(i) - b) + p) % 26
            i = chr(i + b)
            print(i, end="")
        k += 1
    else:
        print(i, end="")
print()