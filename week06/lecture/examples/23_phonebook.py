from cs50 import get_string

people = {
    "Brian": "+1-617-495-1000",
    "David": "+1-617-495-2750"
}

name = get_string("Name: ")

if name in people:
    print(f"Number: {people[name]}")
else:
    print("Not found")