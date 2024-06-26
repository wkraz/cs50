#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};
int main(void)
{
    string p1 = get_string("Player 1: ");
    string p2 = get_string("Player 2: ");
    // Go through each char in each string, find points value equivalent, add it to sum
    int sum1 = 0;
    for (int i = 0, n = strlen(p1); i < n; i++)
    {
        if (isupper(p1[i]))
        {
            sum1 += POINTS[p1[i] - 'A'];
        }
        else if (islower(p1[i]))
        {
            sum1 += POINTS[p1[i] - 'a'];
        }
    }
    int sum2 = 0;
    for (int i = 0, n = strlen(p2); i < n; i++)
    {
        if (isupper(p2[i]))
        {
            sum2 += POINTS[p2[i] - 'A'];
        }
        else if (islower(p2[i]))
        {
            sum2 += POINTS[p2[i] - 'a'];
        }
    }
    // Compare totals, print winner
    if (sum1 > sum2)
    {
        printf("Player 1 wins!\n");
    }
    else if (sum1 < sum2)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }
}
