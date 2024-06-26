#include <stdio.h>
#include <cs50.h>
#include <string.h>

// Typedef; creating our own data structures
typedef struct
{
    string name;
    string number;
}
person;


int main(void)
{
    person people[3];

    people[0].name = "Carter";
    people[0].number = "617-495-1000";

    people[1].name = "David";
    people[1].number = "617-495-1000";

    people[2].name = "John";
    people[2].number = "949-468-2750";




    /* Brute force defns
    string names[] = {"Carter", "David", "John"};
    string numbers[] = {"617-495-1000", "617-495-1000", "949-468-2750"};
    */
    string name = get_string("Enter a name: ");
    for (int i = 0; i < 3; i++)
    {
        /* Brute force
        if (strcmp(names[i], name) == 0)
        {
            printf("Found %s\n", numbers[i]);
            return 0;
        }
         */
        if (strcmp(people[i].name, name) == 0)
        {
            printf("Found %s\n", people[i].number);
            return 0;
        }

    }


    printf("Not found\n");
    return 1;
}
