import sys
from cs50 import get_string
from cs50 import get_int

if len(sys.argv) == 2:
    s = get_string("Plaintext: ")
else:
    print("Error")

key = int(sys.argv[1])
a = ord('a')
b = ord('A')
print("ciphertext: ", end="")

# Check each character in the plaintext
for i in s:
    # If the character is alphabetical
    if i.isalpha():
        if i.islower():
            # Each character is converted to digit
            j = ord(i)
            # Transfer ASCII to alphabetical index
            i = ((j - a) + key) % 26
            # Transfer alphabetical to ASCII
            i = chr(i + a)
            print(i, end="")
        else:
            j = ord(i)
            i = ((j - b) + key) % 26
            i = chr(i + b)
            print(i, end="")
    else:
        print(i, end="")
print()
