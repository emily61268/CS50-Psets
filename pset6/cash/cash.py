from cs50 import get_int
from cs50 import get_float

# Prompt user for change owed
while True:
    change = get_float("Change owed: ")
    if change > 0:
        break

t = round(change * 100)
# Initialize coin count
i = 0
# How many quarters can be used and how much change left
if t >= 25:
    i = t // 25
    t %= 25
# How many dimes can be used and how much change left
if t >= 10:
    i += t // 10
    t %= 10
# How many nickels can be used and how much change left
if t >= 5:
    i += t // 5
    t %= 5
# How many pennies can be used and how much change left
if t >= 1:
    i += t // 1
    t %= 1
print(f"We have used {i} coins.")
