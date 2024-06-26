#include <cs50.h>
#include <stdio.h>

void draw(int n);

int main(void)
{
    int height = get_int("Height: ");
    draw(height);
}

// Recursive definition
void draw(int n)
{
    // If reach the base case, exit
    if (n <= 0)
    {
        return;
    }
    // Print pyramid of n - 1
    draw(n - 1);

    // Print the last row
    for (int i = 0; i < n; i++)
    {
        printf("#");
    }
    printf("\n");
}
