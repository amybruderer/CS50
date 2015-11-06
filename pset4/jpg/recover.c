/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Recovers JPEGs from a forensic image.
 */

#include <stdio.h>

int main(int argc, char* argv[])
{
    // open forensic image
    FILE* file = fopen("card.raw", "r");

    // close forensic image
    fclose(file);
}
