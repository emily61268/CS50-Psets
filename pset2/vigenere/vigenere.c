// Cryptosystem: Vigenere
#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Error\n");
        return 1;
    }
    string key = argv[1];
    for (int w = 0, m = strlen(key); w < m; w++)
    {
        if (!isalpha(key[w]))
        {
            printf("Error\n");
            return 1;
        }
    }
    string p = get_string("Plaintext: ");
    printf("ciphertext: ");
    for (int i = 0, j = 0, n = strlen(p); i < n; i++)
    {
        if (isalpha(p[i])) // Check if each character is alphabetical
        {
            if (islower(p[i]))
            {
                j %= strlen(key);
                int k = (tolower (key[j])) - 'a';
                p[i] = ((p[i] - 'a') + k) % 26; // Transfer ASCII to alphabetical index
                printf("%c", p[i] + 'a'); // Transfer alphabetical to ASCII
            }
            if (isupper(p[i]))
            {
                j %= strlen(key);
                int k = (toupper (key[j])) - 'A';
                p[i] = ((p[i] - 'A') + k) % 26; // Transfer ASCII to alphabetical index
                printf("%c", p[i] + 'A'); // Transfer alphabetical to ASCII
            }
            j++;
        }
        else
        {
            printf("%c", p[i]);
        }
    }
    printf("\n");
}