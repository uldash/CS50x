from cs50 import get_string

s = get_string("Do you agree? ")

if s.lower() in {"y", "yes"}:
    print("Agreed.")
elif s == "N" or s == "n":
    print("Not agreed")