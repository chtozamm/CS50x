#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define BLOCK_SIZE 512

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // Check usage
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }

    // Open file
    FILE *raw_image = fopen(argv[1], "r");
    if (raw_image == NULL)
    {
        printf("Could not open %s\n", argv[1]);
        return 1;
    }

    // Set outfile pointer to null
    FILE *recovered_jpg = NULL;

    // Create an array to store bytes from input file
    BYTE buffer[BLOCK_SIZE];

    // Create jpg counter
    int count_jpg = 0;

    // Create a string to hold a filename
    char filename[8]={0};

    // fread - to read a file
    while (fread(buffer, BLOCK_SIZE, sizeof(BYTE), raw_image) == sizeof(BYTE))
    {
        // Check the first four bytes to find jpg
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // Check if jpg was found before
            if (recovered_jpg != NULL)
            {
                // Close jpg file
                fclose(recovered_jpg);
            }

            // Create jpg
            sprintf(filename, "%03i.jpg", count_jpg++);

            // Open jpg
            recovered_jpg = fopen(filename, "w");
        }

        // Keep writing to jpg file until new jpg found
        if (recovered_jpg != NULL)
        {
            // Write to jpg
            fwrite(buffer, BLOCK_SIZE, sizeof(BYTE), recovered_jpg);
        }
    }

    // Close files
    if (recovered_jpg != NULL) fclose(outptr);
    fclose(raw_image);

    return 0;
}