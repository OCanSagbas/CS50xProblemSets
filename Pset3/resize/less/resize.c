// Copies a BMP file

#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: copy infile outfile\n");
        return 1;
    }
    int n = atoi (argv[1]);
    // remember filenames
    char *infile = argv[2];
    char *outfile = argv[3];

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
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
        return 4;
    }
    int oldwidth = bi.biWidth;
    int oldheight = bi.biHeight;
    int newwidth = oldwidth * n;
    int newheight = oldheight * n;
    int inpadding = (4 - (oldwidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int outpadding = (4 - (newwidth * sizeof(RGBTRIPLE)) % 4) % 4;
    bi.biWidth = newwidth;
    bi.biHeight = newheight;
    bi.biSizeImage = ((sizeof (RGBTRIPLE)*newwidth)+ outpadding) * abs(newheight);
    bf.bfSize = bi.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    RGBTRIPLE scanline [newwidth * sizeof (RGBTRIPLE)];

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(oldheight); i < biHeight; i++)
    {
        // iterate over pixels in scanline
        for (int j = 0; j < oldwidth; j++)
        {
            // temporary storage
            RGBTRIPLE triple;

            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

            for(int k = 0; k< n; k++)
            {
                scanline[(j*n)+k] = triple;
            }
        }

        // skip over padding, if any
        fseek(inptr, inpadding, SEEK_CUR);

        // then add it back (to demonstrate how)
        for (int j = 0; j < n; j++)
        {
            fwrite(scanline, sizeof (RGBTRIPLE), newwidth, outptr);

            for(int k=0; k<outpadding; k++)
            {
                fputc (0x00, outptr);
            }
        }
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
