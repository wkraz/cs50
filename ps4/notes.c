/*
& - asks computer where something is stored
* - used for pointers - actually takes you to a location
pointers typically take 8 bytes of space, ints usually take 4
strings are just pointers that point to the first char in the string and end at null char
typedef char *string; is in <cs50.h>
run: valgrind ./notes
    shows you information about your memory usage: malloc and free
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h> // so you can use malloc & free

void swap(int *a, int *b);
int main(void) {
    int n = 50;
    int *p = &n; // p is a pointer that stores address of n
    printf("%p\n", &n); // prints out the address of variable int n
    printf("%p\n", p); // prints out pointer p
    printf("%i\n", *p); // prints out variable p points to --> n (50)
    // string s = "HI!";
    // printf("%p\n", s); // print out location of string s -- can't do this w/out string.h
    // printf("%p\n", &s[1]); // location of "I" -- have to add & for specific char
    char *s = "HI!"; // strings are really just char pointers
    printf("%s\n", s);
    // typedef uint8_t BYTE; // C doesn't have a way of expressing bytes -- unsigned integer w/ 8 bits
    printf("%c\n", *(s + 1)); // prints out "I" -- pointer arithmetic

    // copying s without altering s when t is altered
    char *t = malloc(strlen(s) + 1); // malloc asks computer for however many bytes you input
    /* unnecessarily hard way to string copy; can just use strcpy
    for (int i = 0, n0 = strlen(s); i < n0; i++)
    {
        t[i] = s[i];
    }
    t[strlen(s)] = '\0'; // need to make sure null char is present
    */
    strcpy(t, s); // first argument is the output, second is input
    t[0] = tolower(t[0]);
    printf("%s\n", t);

    free(t); // free is opposite of malloc; gives back the memory malloc took to your OS

    // scanf
    int n1;
    printf("n1: ");
    scanf("%i", &n1); // uses pointer to go to location of n1 and change the value to whatever is input
    printf("n1: %i\n", n1);

    char s1[4]; // have to use char arrays for scanf strings, not pointers
    printf("s1: ");
    scanf("%s", s1);
    printf("s1: %s\n", s1);

    // file I/O
    // FILE *file = fopen("phonebook.csv", "a"); // a for append, can use w and r for write and read

    // char *name = get_string("Name: ");
    // char *number = get_string("Number: ");
    // fprintf(file, "%s, %s\n", name, number);
    // fclose(file);

    /*
    BYTE b;
    FILE *src = fopen(argv[1], "rb");
    FILE *dst = fopen(argv[2], "wb");

    while (fread(&b, sizeof(b), 1, src) != 0)
    {
        fwrite(&b, sizeof(b), 1, dst);
    }
    fclose(dst);
    fclose(src);

    */

}

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}
