#include <stdio.h>

void swap(int *a, int *b); // the function takes pointers to the addresses and swaps them, which makes the value of 'a' be equal to the value of 'b' and vice versa

int main(void)
{
    int a = 1;
    int b = 2;

    printf("a: %i, b: %i\n", a, b);

    swap(&a, &b); // in parenthesis we provide the addresses of the variables

    printf("a: %i, b: %i\n", a, b);
}

void swap(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}
