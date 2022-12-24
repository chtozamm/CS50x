#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Prompt user to agree to something
    char c = get_char("Do you agree?\n");

    // Check whether user agree
    if (c == 'y' || c == 'Y')
    {
        printf("Agreed.\n");
    }
    else if (c == 'n' || c == 'N')
    {
        printf("Not agreed.\n");
    }
}