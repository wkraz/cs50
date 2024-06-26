#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    string text = get_string("Text: ");
    int letterCount = 0;
    int punctuationCount = 0;
    int wordCount = 1;
    // Go through each letter in array, use numbers to see if letter or period
    for (int letter = 0, n = strlen(text); letter < n; letter++)
    {
        if (isalpha(text[letter]))
        {
            letterCount++;
        }
        else if (text[letter] == 46 || text[letter] == 63 || text[letter] == 33)
        {
            punctuationCount++;
        }
        else if (text[letter] == ' ')
        {
            wordCount++;
        }
    }

    // L & S calculations
    float L = (float) letterCount / wordCount * 100;
    float S = (float) punctuationCount / wordCount * 100;
    // Index
    float index = (0.0588 * L) - (0.296 * S) - 15.8;
    index += 0.5;
    int intIndex = (int) index;

    // Use index to get grade level and display
    if (intIndex < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (intIndex > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", intIndex);
    }
}
