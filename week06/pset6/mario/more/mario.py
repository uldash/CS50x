while True:
    try:
        h = int(input("Height: "))
        if h >= 1 and h <= 8:
            break
    except:
        continue

for i in range(h):
    print(" " * (h - i - 1), end="")
    print("#" * (i + 1), end="")
    print("  ", end="")
    print("#" * (i + 1))