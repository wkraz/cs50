#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

void substitute();

int main(int argc, string argv[])
{
    // Making sure there's only one argument
    if (argc == 2)
    {
        if (strlen(argv[1]) == 26)
        {
            for (int i = 0; i < strlen(argv[1]); i++)
            {
                // Seeing if it contains non alphabet
                if (!isalpha(argv[1][i]))
                {
                    printf("Key must contain 26 characters.\n");
                    return 1;
                }
                // Checking for duplicates
                for (int j = i + 1; j < strlen(argv[1]); j++)
                {
                    if (toupper(argv[1][j]) == toupper(argv[1][i]))
                    {
                        printf("Key must not contain repeated alphabets.\n");
                        return 1;
                    }
                }
            }
            // Run our substitution function after passing every test
            substitute(argv[1]);
        }
        else
        {
            printf("Key must contain 26 characters.\n");
            return 1;
        }
    }
    else
    {
        printf("Error. Must give only two arguments.\n");
        return 1;
    }
    return 0;
}

void substitute(string key)
{
    string plaintext = get_string("plaintext:  ");
    int plaintext_length = strlen(plaintext);
    char ciphertext[plaintext_length + 1];
    for (int i = 0, n = strlen(key); i < n; i++)
    {
        key[i] = toupper(key[i]);
    }
    // Go through input
    for (int i = 0, n = strlen(plaintext); i < n; i++)
    {
        int keyNum = 0;
        if isupper (plaintext[i])
        {

            keyNum = key[plaintext[i] - 'A'];
            ciphertext[i] = keyNum;
        }
        else if islower (plaintext[i])
        {
            keyNum = key[plaintext[i] - 'a'];
            ciphertext[i] = keyNum + 32;
        }
        else
        {
            ciphertext[i] = plaintext[i];
        }
    }
    ciphertext[plaintext_length] = '\0';

    printf("ciphertext: %s\n", ciphertext);
}
