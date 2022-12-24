#include <cs50.h>
#include <stdio.h>

void drawBlocks(void);

int main(void)
{
    drawBlocks();
}






void drawBlocks(void)
{
    int n = 0;
    while (n < 1 || n > 8)
    {
        n = get_int("Height: ");
    }
    int spaces = n;
    int counter = 1;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < spaces; j++)
        {
            printf(" ");
        }
        spaces--;
        for (int k = 0; k < counter; k++)
        {
            printf("#");
        }
        printf("  ");
        for (int l = 0; l < counter; l++)
        {
            printf("#");
        }
        counter++;
        printf("\n");
    }
}