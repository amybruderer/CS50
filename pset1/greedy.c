#include <cs50.h>
#include <math.h>
#include <stdio.h>

float GetChange(void);
int ConvertToCents(float change);
int CalcTotalCoins(int cents);

int main(void)
{
    float change = GetChange();
    printf("%i\n", CalcTotalCoins(ConvertToCents(change)));
}

float GetChange(void)
{
    float change = 0;
    
    // Prompt user for change owed
    do
    {
        printf("How much change is owed?\n");
        change = GetFloat();
    }
    // Verify amount is greater than 0
    while (change <= 0.0f);

    return change;
}

int ConvertToCents(float change)
{
    return (int) (roundf(change * 100.0f));
}

int CalcTotalCoins(int cents)
{
    int numCoins = 0;
    static const int MAX_COINS = 4;
    static const int COIN_VALUE[MAX_COINS] = 
    {
        25, // Quarter
        10, // Dime
         5, // Nickel
         1, // Penny
    };
    
    for (int i = 0, remaining = cents; (i < MAX_COINS) && (remaining > 0); ++i)
    {
        numCoins += (remaining / COIN_VALUE[i]);
        remaining = (remaining % COIN_VALUE[i]);
    }
    
    return numCoins;
}
