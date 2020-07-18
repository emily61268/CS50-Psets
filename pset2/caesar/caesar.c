// Cryptosystem: Caesar
#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, string argv[])
{
    string p;

    if (argc == 2)
    {
        p = get_string("Plaintext: "); // Prompt user for plaintext
    }
    else
    {
        printf("Error\n");
        return 1;
    }
    printf("ciphertext: ");
    int k = atoi(argv[1]); // Turn key into integer
    for (int i = 0, n = strlen(p); i < n; i++)
    {
        if (isalpha(p[i])) // Check if each character is alphabetical
        {
            if (islower(p[i]))
            {
                p[i] = ((p[i] - 'a') + k) % 26; // Transfer ASCII to alphabetical index
                printf("%c", p[i] + 'a'); // Transfer alphabetical to ASCII
            }
            else
            {
                p[i] = ((p[i] - 'A') + k) % 26; // Transfer ASCII to alphabetical index
                printf("%c", p[i] + 'A'); // Transfer alphabetical to ASCII
            }
        }
        else
        {
            printf("%c", p[i]);
        }
    }
    printf("\n");
}
