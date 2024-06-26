#include <cs50.h>
#include code<stdio.h>

int main()
{
    string answer = get_string("What's your name? ");
    printf("hello, %s\n", answer);
    return 0;
}
