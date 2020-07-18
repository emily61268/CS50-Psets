// Let's save some coins!

#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    float g; //Amount owed
    int count = 0;
    do
    {
        // Prompt user for change owed
        g = get_float("Change owed: ");
    }
    while (g < 0);
    int t = roundf (g * 100);
    // How many quarters can be used and how much change left
    while (t >= 25)
    {
        count++; // The number of quarters used
        t -= 25;
    }
    // How many dimes can be used and how much change left
    while (t >= 10)
    {
        count++; // The number of dimes used
        t -= 10;
    }
    // How many nickels can be used and how much change left
    while (t >= 5)
    {
        count++; // The number of nickels used
        t -= 5;
    }
    // How many pennies can be used and how much change left
    while (t >= 1)
    {
        count++; // The number of pennies used
        t -= 1;
    }
    printf("We have used %i coin(s)!\n", count);
}