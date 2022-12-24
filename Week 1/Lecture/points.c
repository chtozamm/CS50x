#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int points = get_int("How many points did you lose?\n");
    const int DAVID_POINTS = 2;

    if (points < DAVID_POINTS)
    {
        printf("You lost less points than David!\n");
    }
    else if (points > DAVID_POINTS)
    {
        printf("You lost more points than David.\n");
    }
    else
    {
        printf("You lost the same number of points as David!\n");
    }
}