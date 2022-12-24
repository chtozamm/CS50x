//
// Printing a pyrimide using recursion
//
#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void draw(int height);

int main(int argc, string argv[])
{
    if (argc != 2) return 1;
    int height = atoi(argv[1]);
    if (height <= 0) return 1;
    draw(height);
}

void draw(int height)
{
    for (int i = 0; i < height; i++)
    {
        if (height - i == 0) return;
        for (int j = 0; j < i+1; j++)
        {
            printf("#");
        }
        printf("\n");
    }
}