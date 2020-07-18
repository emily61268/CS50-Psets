// Mario (less) practice

#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int h;
    do
    {
        // Prompt user for Height
        h = get_int("Height (choose an integer between 1 to 23): ");
    }
    while (h < 0 || h > 23);
    // Generate half-pyramid
    for (int t = 2; t < h + 2; t++)
    {
        for (int i = 0; i < h - t + 1; i++)
        {
            printf(" ");
        }
        for (int n = 0; n < t; n++)
        {
            printf("#");
        }
        printf("\n");
    }
}