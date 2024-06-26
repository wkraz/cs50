#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef uint8_t BYTE; // so we can just use bytes

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Error: incorrect usage.\n");
        return 1;
    }
    FILE *inptr = fopen(argv[1], "r"); // read input file
    if (inptr == NULL)
    {
        printf("Could not open file.\n");
        return 2;
    }
    FILE *outptr = NULL; // output file
    BYTE buffer[512];
    // number array
    char filename[8] = {0}; // - - -.jpg is 7 chars + null char
    int count = 0;
    while (fread(buffer, sizeof(BYTE) * 512, 1, inptr) ==
           1) // when there isn't stuff to read, it stops
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0) // look for start of jpeg
        {
            if (outptr != NULL)
            {
                fclose(outptr);
            }
            sprintf(filename, "%03i.jpg", count++); // name jpeg w/ number 
            printf("jpeg detected%s\n", filename); // for debugging purposes
            outptr = fopen(filename, "w");         // opening file
        }
        if (outptr != NULL) // if jpeg is not detected, write another 512 bytes
        {
            fwrite(buffer, sizeof(BYTE) * 512, 1, outptr);
        }
    }
    fclose(inptr);
    if (outptr != NULL)
    {
        fclose(outptr);
    }
    return 0;
}
