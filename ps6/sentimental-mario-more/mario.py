from cs50 import get_int

while True:
    height = get_int("Height: ")
    if height <= 8 and height >= 1:
        break

for i in range(height):
    i += 1  # because range is 0 --- height - 1 and we want 1 --- height
    print(" " * (height - i), end="")
    print("#" * i, end="")
    print("  ", end="")
    print("#" * i, end="")
    print()
