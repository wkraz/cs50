#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int numbers[] = {20, 500, 10, 5, 100, 1, 50};
    printf("The array is [20, 500, 10, 5, 100, 1, 50]\n");
    int n = get_int("Number: ");

    // Linear search w/ integers
    printf("Linear search:\n");
    for (int i = 0; i < 7; i++)
    {
        if (numbers[i] == n)
        {
            printf("Found\n");
            return 0;
        }

    }
    printf("Not found\n");
    return 1;
}
