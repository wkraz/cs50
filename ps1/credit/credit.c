#include <cs50.h>
#include <stdio.h>

int main()
{
    // prompt user for number
    long n = get_long("Number: ");
    long l = n;
    int length = 0;
    // getting length of the card number
    while (l > 0)
    {
        l = l / 10;
        length++;
    }
    // making sure number is either 13, 15, 16
    if (length != 13 && length != 15 && length != 16)
    {
        printf("INVALID\n");
        return 1;
    }
    // Initialize all the variables we'll need
    int sum1 = 0;
    int sum2 = 0;
    long x = n;
    int total = 0;
    int mod1 = 0;
    int mod2 = 0;
    int d1 = 0;
    int d2 = 0;
    // Running Luhn algorithm
    do
    {
        // Remove last digit and add to sum1
        mod1 = x % 10;
        x = x / 10;
        sum1 += mod1;

        // Remove second to last digit
        mod2 = x % 10;
        x = x / 10;

        // Double second to last digit and add digits to sum2
        mod2 *= 2;
        d1 = mod2 % 10;
        // if d1 > 10, add 1 to sum2
        d2 = mod2 / 10;
        sum2 = sum2 + d1 + d2;
    }
    while (x > 0);

    total = sum1 + sum2;

    // Now check Luhn algorithm
    if (total % 10 != 0)
    {
        printf("INVALID\n");
        return 0;
    }

    // Now check first 2 digits and determine the card type
    // Get first 2 digits of n
    long s = n;
    do
    {
        s = s / 10;
    }
    while (s > 100);

    // Now that we have s, check to see the card type
    if ((s / 10 == 5) && (0 < s % 10 && s % 10 < 6) && length == 16)
    {
        printf("MASTERCARD\n");
    }
    else if ((s / 10 == 3) && (s % 10 == 4 || s % 10 == 7) && length == 15)
    {
        printf("AMEX\n");
    }
    else if (s / 10 == 4 && (length == 13 || length == 16))
    {
        printf("VISA\n");
    }
    else
    {
        printf("INVALID\n");
    }
}
