#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <stdlib.h>

typedef struct
{
    string name;
    string number;
}
person;

int main(int argc, string argv[])
{
    if (argc < 2 || argc > 2) {
        return 1;
    }

    person people[2];
    people[0].name = "David";
    people[0].number = "+7-3432-43";

    people[1].name = "Caesar";
    people[1].number = "+8-3434-66";

    int array_length = sizeof(people);
    string key = argv[1];
    for (int i = 0; i < array_length; i++)
    {
        if (strcmp(people[i].name, key) == 0)e
        {
            printf("Number of %s is: %s\n", people[i].name, people[i].number);
            return 0;
        }
    }
    printf("Not found.\n");
    return 1;
}