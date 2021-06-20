// Check if the entered number is a valid credit card number
// Luhn’s Algorithm

// Card Type                    Number
// American Express             378282246310005
// American Express             371449635398431
// American Express Corporate   378734493671000
// Diners Club                  30569309025904
// Discover                     6011111111111117
// Discover                     6011000990139424
// JCB                          3530111333300000
// JCB                          3566002020360505
// Mastercard                   2221000000000009
// Mastercard                   2223000048400011
// Mastercard                   2223016768739313
// Mastercard                   5555555555554444
// Mastercard                   5105105105105100
// Visa                         4111111111111111
// Visa                         4012888888881881
// Visa                         4222222222222

#include <stdio.h>
#include <cs50.h>
#include <math.h>

int get_digits_count(long long n);
int get_first_n_digits(long long n, int count);
bool is_valid_card(long long n);
string get_pay_system(long long);

int main(void)
{
    long long credit = 0;
    do
    {
        credit = get_long("Number: ");
    }
    while (credit <= 0);

    // credit = 4003600000000014;

    printf("%s\n", get_pay_system(credit));
    // printf("%i\n", get_digits_count(credit));
    // printf("%i\n", get_first_n_digits(credit, 4));
    // if (is_valid_card(credit))
    // {
    //     printf("true");
    // }
    // else
    // {
    //     printf("false");
    // }

}

// return number of digits in a number
int get_digits_count(long long n)
{
    if (n < 9)
    {
        return 1;
    }
    if (n < 99)
    {
        return 2;
    }
    if (n < 999)
    {
        return 3;
    }
    if (n < 9999)
    {
        return 4;
    }
    if (n < 99999)
    {
        return 5;
    }
    if (n < 999999)
    {
        return 6;
    }
    if (n < 9999999)
    {
        return 7;
    }
    if (n < 99999999)
    {
        return 8;
    }
    if (n < 999999999)
    {
        return 9;
    }
    if (n < 9999999999)
    {
        return 10;
    }
    if (n < 99999999999)
    {
        return 11;
    }
    if (n < 999999999999)
    {
        return 12;
    }
    if (n < 9999999999999)
    {
        return 13;
    }
    if (n < 99999999999999)
    {
        return 14;
    }
    if (n < 999999999999999)
    {
        return 15;
    }
    if (n < 9999999999999999)
    {
        return 16;
    }
    if (n < 99999999999999999)
    {
        return 17;
    }
    if (n < 999999999999999999)
    {
        return 18;
    }
    if (n < 9223372036854775807 - 1)
    {
        return 19;
    }
    return 0;
}


int get_first_n_digits(long long n, int count)
{
    return n / pow(10, get_digits_count(n) - count);
}

bool is_valid_card(long long n)
{
    int sum_even = 0;
    int sum_odd = 0;
    bool flag = false;

    while (n != 0)
    {
        int current = n % 10;
        n /= 10;

        // printf("%i\n", current);

        if (flag)
        {
            if (2 * current > 9)
            {
                sum_even += 1 + (2 * current) % 10;
            }
            else
            {
                sum_even += 2 * current;
            }

            flag = false;
            // printf("sum_even: %i\n", sum_even);
        }
        else
        {
            sum_odd += current;

            flag = true;
        }
    }

    // printf("%i\n", sum_even);
    // printf("%i\n", sum_odd);

    if ((sum_odd + sum_even) % 10 == 0)
    {
        return true;
    }
    return false;
}

string get_pay_system(long long n)
{
    if (get_digits_count(n) == 15 &&
        (get_first_n_digits(n, 2) == 34 || get_first_n_digits(n, 2) == 37) &&
        is_valid_card(n))
    {
        return "AMEX";
    }
    if (get_digits_count(n) == 15 &&
        (get_first_n_digits(n, 2) == 60) &&
        is_valid_card(n))
    {
        return "DISCOVER";
    }
    if (get_digits_count(n) == 14 &&
        (get_first_n_digits(n, 2) == 30) &&
        is_valid_card(n))
    {
        return "DINERCCLUB";
    }
    if (get_digits_count(n) == 16 &&
        (get_first_n_digits(n, 2) == 35) &&
        is_valid_card(n))
    {
        return "JCB";
    }
    if (get_digits_count(n) == 16 &&
        (get_first_n_digits(n, 2) == 22 || get_first_n_digits(n, 2) == 51 || get_first_n_digits(n, 2) == 55) &&
        is_valid_card(n))
    {
        return "MASTERCARD";
    }
    if ((get_digits_count(n) == 16 || get_digits_count(n) == 13) &&
        (get_first_n_digits(n, 2) == 40 || get_first_n_digits(n, 2) == 41 || get_first_n_digits(n, 2) == 42) &&
        is_valid_card(n))
    {
        return "VISA";
    }
    return "INVALID";
}