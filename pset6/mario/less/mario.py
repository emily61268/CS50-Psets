from cs50 import get_int

# Prompt user for a number for height
while True:
    h = get_int("Height (choose an integer between 1 to 23): ")
    if h >= 0 and h <= 23:
        break
n = 2
# Build pyramid
for i in range(h):
    for g in range(h - i - 1):
        print(" ", end="")
    for n in range(i + 2):
        print("#", end="")
    print()