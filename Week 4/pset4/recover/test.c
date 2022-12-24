#include "stdio.h"

typedef char * string;

int main(int argc, char *argv[])
{
    string name = argv[1];

    printf("Hello, %s\n", name);

    return 0;
}