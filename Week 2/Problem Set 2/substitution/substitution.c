#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

string substitution(string plaintext, string key);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    else if (strlen(argv[1]) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 2;
    }

    // Assign Comand Line Argument to a variable
    string key = argv[1];

    // Prompts plaintext
    string plaintext = get_string("plaintext: ");

    // Calls a function to get ciphertext
    string ciphertext = substitution(plaintext, key);

    // Prints ciphertext and exit successfully
    printf("ciphertext: %s\n", ciphertext);
    return 0;
}

string substitution(string plaintext, string key)
{
    // Assigns ciphertext to to plaintext to get the same string length
    string ciphertext = plaintext;

    int length = strlen(ciphertext);

    // Main function loop: creates ciphertext; preserves original case
    for (int i = 0; i < length; i++)
    {
        if (islower(plaintext[i]))
        {
            ciphertext[i] = key[plaintext[i] - 97];
            if (isupper(ciphertext[i]))
            {
                ciphertext[i] = tolower(ciphertext[i]);
            }
        }
        else if (isupper(plaintext[i]))
        {
            ciphertext[i] = key[plaintext[i] - 65];
            if (islower(ciphertext[i]))
            {
                ciphertext[i] = toupper(ciphertext[i]);
            }
        }
    }

    return ciphertext;
}