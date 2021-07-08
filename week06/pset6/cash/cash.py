def main():
    while True:
        try:
            owned = float(input("Change owed: "))
            if owned > 0:
                break
        except:
            continue

    monets = [25, 10, 5, 1]
    cents = round(owned * 100)
    count = 0

    for n in monets:
        count += cents // n
        cents = cents % n

    print(count)


if __name__ == "__main__":
    main()
