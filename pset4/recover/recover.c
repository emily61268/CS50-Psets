#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        fprintf(stderr, "Usage: copy infile outfile\n");
        return 1;
    }
    // remember filename
    char *rawfile = argv[1];
    // open input file
    FILE *inptr = fopen(rawfile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", rawfile);
        return 2;
    }
    // create a buffer sized 512 blocks of 1 byte (temporary storage)
    unsigned char bytes[512];
    // filename nees 8 bytes because "000.jpg\0"
    char filename[8];
    int filenumber = 0;
    // open output file
    FILE *img = fopen(filename, "w");
    // repeat until end of card memory
    while (fread(bytes, sizeof(char), 512, inptr) == 512)
    {
        //start of a new JPEG?
        if (bytes[0] == 0xff &&
            bytes[1] == 0xd8 &&
            bytes[2] == 0xff &&
            (bytes[3] & 0xf0) == 0xe0)
        {
            // already found a JPEG? if yes, close it
            if (img != NULL)
            {
                fclose(img);
            }
            // if not, start the loop
            sprintf(filename, "%03i.jpg", filenumber++);
            img = fopen(filename, "w");
            fwrite(bytes, sizeof(char), 512, img);
        }
        else
        {
            fwrite(bytes, sizeof(char), 512, img);
        }
    }

    // close rawfile
    fclose(inptr);
    return 0;
}