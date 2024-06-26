#include <cs50.h>
#include <stdio.h>

int main()
{
    int answer;
    // Prompt for asking for a number between 1 and 8
    do
    {
        answer = get_int("Enter the size of the pyramid (1-8 inclusive): ");
    }
    while (!(answer > 0 && answer < 9));
    // Print pyramid with height of answer
    for (int i = 1; i < answer + 1; i++)
    {
        for (int j = i; j < answer; j++)
        {
            printf(" ");
        }
        for (int j = 1; j < i + 1; j++)
        {
            printf("#");
        }
        printf("  ");
        for (int j = 1; j < i + 1; j++)
        {
            printf("#");
        }
        printf("\n");
    }
}
