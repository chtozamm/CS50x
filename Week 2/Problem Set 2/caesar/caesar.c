#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    // Validates the Command Line Argument; Returns if not valid
    if (argc != 2 || !isdigit(*argv[1]))
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    // Prompts the string
    string plaintext = get_string("\n_plaintext: ");

    int length = strlen(plaintext);
    int k = atoi(argv[1]);

    int c = 0;

    printf("ciphertext: ");
    for (int i = 0; i < length; i++)
    {
        int x = plaintext[i];
         if (x >= 65 && x <= 90)
        {
            c = plaintext[i] + k;
            if (c > 90)
            {
                c -= 25;
            }
                printf("%c", c);
        }
        else if (x > 90 && x <= 122)
        {
            c = plaintext[i] + k;
            if (c > 122)
            {
                c -= 25;
            }
                printf("%c", c);
        }
    }
    printf("\n\n");
}