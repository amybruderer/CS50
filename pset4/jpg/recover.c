/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Recovers JPEGs from a forensic image.
 */

#include <stdint.h>
#include <stdio.h>

// prototype
void safe_close(FILE* file);

int main(int argc, char* argv[])
{

    // forensic image filename
    static const char * filename = "card.raw";

    // open forensic image
    FILE* file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Could not open %s.\n", filename);
        return 1;
    }

    // block size
    static const int blockSize = 512;
    uint8_t block[blockSize];

    FILE* outfile = NULL;
    int curFile = 0;

    // read the file block by block
    for (size_t bytesRead = 0; (bytesRead = fread(block, sizeof(*block), blockSize, file)) == blockSize; )
    {
        // check for JPEG signature
        if (((block[0] == 0xff) && (block[1] == 0xd8) && (block[2] == 0xff)) &&
            ((block[3] == 0xe0) || (block[3] == 0xe1)))
        {
            // close current outfile, if open
            safe_close(outfile);

            // start writing new file
            char filename[4];
            sprintf(filename, "%03i.jpg", curFile++);
            outfile = fopen(filename, "wb");
        }

        // write block to outfile, if open
        if (outfile != NULL)
        {
            fwrite(block, sizeof(*block), blockSize, outfile);
        }
    }

    // close outfile, if open
    safe_close(outfile);

    // close forensic image
    fclose(file);
}

// closes file pointer if not null
void safe_close(FILE* file)
{
    if (file != NULL)
    {
        fclose(file);
    }
}
