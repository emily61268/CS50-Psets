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

    // remember filenames
    int t = atoi(argv[1]);
    char *infile = argv[2];
    char *outfile = argv[3];

    if (t < 0 || t > 100)
    {
        fprintf(stderr, "Please enter a positive integer which is less than or equal to 100.\n");
        return 2;
    }
    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 3;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
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

    bi.biWidth *= t;
    bi.biHeight *= t;
    // determine padding for scanlines
    int padding_n = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int padding = (4 - ((bi.biWidth / t) * sizeof(RGBTRIPLE)) % 4) % 4;
    bi.biSizeImage = ((sizeof(RGBTRIPLE) * bi.biWidth) + padding_n) * abs(bi.biHeight);
    bf.bfSize = bi.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // resize horizontally
    for (int a = 0, biHeight = abs(bi.biHeight); a < biHeight / t; a++)
    {
        for (int i = 0; i < t - 1; i++)
        {
            for (int g = 0; g < bi.biWidth / t; g++)
            {
                RGBTRIPLE triple;
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
                if (triple.rgbtBlue == 0xff)
                {
                    for (int c = 0; c < t; c++)
                    {
                        fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                    }
                }
                else if (triple.rgbtGreen == 0xff)
                {
                    for (int c = 0; c < t; c++)
                    {
                        fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                    }
                }
                else if (triple.rgbtRed == 0xff)
                {
                    for (int c = 0; c < t; c++)
                    {
                        fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                    }
                }
                else
                {
                    fseek(inptr, padding, SEEK_CUR);
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }
            }
            // add the new padding
            for (int p = 0; p < padding_n; p++)
            {
                fputc(0x00, outptr);
            }
            // send infile cursor back
            fseek(inptr, -(bi.biWidth / t * 3), SEEK_CUR);
        }
        // resize vertically
        for (int g = 0; g < bi.biWidth / t; g++)
        {
            RGBTRIPLE triple;
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
            if (triple.rgbtBlue == 0xff)
            {
                for (int c = 0; c < t; c++)
                {
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }
            }
            else if (triple.rgbtGreen == 0xff)
            {
                for (int c = 0; c < t; c++)
                {
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }
            }
            else if (triple.rgbtRed == 0xff)
            {
                for (int c = 0; c < t; c++)
                {
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }
            }
            else
            {
                fseek(inptr, padding, SEEK_CUR);
                fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
            }
        }
        // add the new padding
        for (int p = 0; p < padding_n; p++)
        {
            fputc(0x00, outptr);
        }
        fseek(inptr, padding, SEEK_CUR);
    }
    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
