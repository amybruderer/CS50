/*
 * caesar.c
 * 
 * Amy Bruderer
 * amy.bruderer@gmail.com
 *
 * Encrypts messages using Caesar's cipher.
 */

#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// prototypes
char Encrypt(char c, int key, char base);
void PrintEncryptedMessage(string str, int key);

int main(int argc, string argv[])
{
    // Validate arguments
    if (argc != 2)
    {
        printf("Usage: %s <key>\n", argv[0]);
        return 1;
    }
    
    int k = atoi(argv[1]);
    
    // Validate key
    if (k < 0)
    {
        printf("Key must be a non-negative integer.");
        return 1;
    }
    
    // Get message to encrypt
    string message = GetString();

    // Print encrypted message
    PrintEncryptedMessage(message, k);
    
    // Clean up memory allocated by GetString()
    free(message);   
    return 0;
}

/*
 * Encrypt character using key and base character
 */
char Encrypt(char c, int key, char base)
{
    return ((c - base + key) % 26) + base;
}

/*
 * Encrypt and print message using key
 */
void PrintEncryptedMessage(string str, int key)
{
    for (int i = 0, len = strlen(str); i < len; ++i)
    {
        char c = str[i];

        if (isupper(c))
        {
            c = Encrypt(c, key, 'A');
        }
        else if (islower(c))
        {
            c = Encrypt(c, key, 'a');
        }

        printf("%c", c);
    }

    printf("\n");
}
