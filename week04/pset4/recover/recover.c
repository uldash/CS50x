// https://cs50.harvard.edu/x/2021/psets/4/recover/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <cs50.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "rb");
    if (input == NULL)
    {
        printf("Could not open raw file.\n");
        return 1;
    }

    char fname[8];
    int i = 0;
    FILE *output = NULL;

    BYTE buffer[512];

    while (fread(&buffer, 512 * sizeof(BYTE), 1, input))
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff)
        {
            if (output != NULL)
            {
                fclose(output);
            }

            sprintf(fname, "%03i.jpg", i);
            i++;
            // printf("%s Found\n", fname);

            output = fopen(fname, "wb");
        }
        if (output != NULL)
        {
            fwrite(&buffer, 512 * sizeof(BYTE), 1, output);
        }
    }

    if (output != NULL)
    {
        fclose(output);
    }
    fclose(input);
    return 0;
}