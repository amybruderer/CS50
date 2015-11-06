/**
 * resize.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Resizes a BMP by a factor of n.
 */
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: ./resize n infile outfile\n");
        return 1;
    }
    
    // remember resize factor
    int factor = atoi(argv[1]);
    
    // make sure factor is valid
    if (!((factor > 0) && (factor <= 100)))
    {
        printf("Factor must be a positive integer less than or equal to 100.\n");
        return 2;
    } 

    // remember filenames
    char* infile = argv[2];
    char* outfile = argv[3];

    // open input file 
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 3;
    }

    // open output file
    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 4;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 5;
    }

    // copy infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bfOut = bf;

    // copy infile's BITMAPINFOHEADER
    BITMAPINFOHEADER biOut = bi;

    // modify outfile's width and height
    biOut.biWidth = bi.biWidth * factor;
    biOut.biHeight = bi.biHeight * factor;

    // determine outfiles's padding for scanlines
    int paddingOut =  (4 - (biOut.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // determine outfiles's bytes per scanline
    int bytesPerLine = ((biOut.biWidth * sizeof(RGBTRIPLE)) + paddingOut);

    // modify outfile's image size
    biOut.biSizeImage = abs(biOut.biHeight) * bytesPerLine;

    // modify outfile's size
    bfOut.bfSize = bfOut.bfOffBits + biOut.biSizeImage;

    // write outfile's BITMAPFILEHEADER
    fwrite(&bfOut, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&biOut, sizeof(BITMAPINFOHEADER), 1, outptr);

    // determine infile's padding for scanlines
    int padding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        // remember start of scanline
        fpos_t pos;
        fgetpos(inptr, &pos);

        // write each line factor times
        for (int j = 0; j < factor; j++)
        {
            // move to the start of scanline
            fsetpos(inptr, &pos);

            // iterate over pixels in scanline
            for (int k = 0; k < bi.biWidth; k++)
            {
                // temporary storage
                RGBTRIPLE triple;

                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                // write RGB triple to outfile factor times
                for (int l = 0; l < factor; l++)
                {
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }
            }

            // skip over padding, if any
            fseek(inptr, padding, SEEK_CUR);

            // write outfile's padding, if any
            for (int m = 0; m < paddingOut; m++)
            {
                fputc(0x00, outptr);
            }
        }
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}
