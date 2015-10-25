/*
 * vigenere.c
 * 
 * Amy Bruderer
 * amy.bruderer@gmail.com
 *
 * Encrypts messages using Vigenere's cipher.
 */

#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// prototypes
int GetShift(char c);
char Encrypt(char c, int shift);
void PrintEncryptedMessage(string str, string key);

int main(int argc, string argv[])
{
    // Validate arguments
    if (argc != 2)
    {
        printf("Usage: %s <keyword>\n", argv[0]);
        return 1;
    }
    
    string k = argv[1];
    
    // Validate key
    for (int i = 0, len = strlen(k); i < len; ++i)
    {
        char c = k[i];
        
        if (!((isupper(c)) || (islower(c))))
        {
            printf("Keyword must only contain letters A-Z and a-z");
            return 1;
        }
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
 * Return the shift value for a given character
 *
 * @note: assumes character is either upper or lower case
 * and nothing else
 */
 int GetShift(char c)
 {
    return isupper(c) ? (c - 'A') : (c - 'a');
 }

/*
 * Encrypt character using shift
 */
char Encrypt(char c, int shift)
{
    char base = isupper(c) ? 'A' : 'a';
    return ((c - base + shift) % 26) + base;
}

/*
 * Encrypt and print message using key
 */
void PrintEncryptedMessage(string str, string key)
{
    for (int i = 0, encrypted = 0, len = strlen(str), keylen = strlen(key); i < len; ++i)
    {
        char c = str[i];

        if (isupper(c) || islower(c))
        {
            int shift = GetShift(key[(encrypted % keylen)]);
            c = Encrypt(c, shift);
            ++encrypted;
        }

        printf("%c", c);
    }

    printf("\n");
}
