/*
 * initials.c
 * 
 * Amy Bruderer
 * amy.bruderer@gmail.com
 *
 * Prompts a user for their name and prints their uppercase initials.
 */

#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// prototypes
string GetName();
void PrintInitial(const string str);

int main(void)
{
    string name = GetName();
    static const string DELIM = " ";

    // Get the individual words, one by one
    for (string str = name; ; str = NULL)
    {
        string token = strtok(str, DELIM);
        if (token == NULL)
        {
            break;
        }
        PrintInitial(token);
    }

    printf("\n");

    // Clean up memory allocated by GetString()
    free(name);
}

/*
 * Returns the user's name
 * 
 * @note: memory must be freed by caller
 */
string GetName()
{
    return GetString();
}

/*
 * Capitalize and print the first letter of the string
 */
void PrintInitial(const string str)
{
    if (strlen(str) > 1)
    {
        printf("%c", toupper(str[0]));
    }
}
