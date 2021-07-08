def main():
    while True:
        try:
            credit = int(input("Number: "))
            if credit > 0:
                credit = str(credit)
                break
        except:
            continue
    print(is_valid_card(credit))
    print(get_pay_system(credit))


def is_valid_card(credit):
    sum_even = 0
    sum_odd = 0
    flag = False

    for i in range(len(credit) - 1, -1, -1):
        # print(i, credit[i])
        if flag:
            if int(credit[i]) * 2 > 9:
                sum_even += 1 + (int(credit[i]) * 2) % 10
            else:
                sum_even += int(credit[i]) * 2
        else:
            sum_odd += int(credit[i])
        flag = not flag

    print("sum_even: ", sum_even)
    print("sum_odd: ", sum_odd)
    if (sum_even + sum_odd) % 10 == 0:
        return True
    return False


def get_pay_system(n):
    if len(n) == 15 and (n[:2] == "34" or n[:2] == "37") and is_valid_card(n):
        return "AMEX"
    if len(n) == 15 and n[:2] == "60" and is_valid_card(n):
        return "DISCOVER"
    if len(n) == 14 and n[:2] == "30" and is_valid_card(n):
        return "DINERCCLUB"
    if len(n) == 16 and n[:2] == "35" and is_valid_card(n):
        return "JCB"
    if len(n) == 16 and (n[:2] == "22" or n[:2] == "51" or n[:2] == "55") and is_valid_card(n):
        return "MASTERCARD"
    if len(n) == 16 and (n[:2] == "13" or n[:2] == "40" or n[:2] == "41" or n[:2] == "42") and is_valid_card(n):
        return "VISA"
    return "INVALID"


if __name__ == "__main__":
    main()