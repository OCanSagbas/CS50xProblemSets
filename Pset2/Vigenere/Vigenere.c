#include <cs50.h>
#include <stdio.h>
#include <ctype.h>  //tolower toupper
#include <string.h>
#include <math.h>
#include <stdlib.h>
bool only_letter(string s);
void encrypt(string plaintext, string ciphertext, string cipher);

int main(int argc, string argv[])
{
    if (argc!=2 || !only_letter(argv[1]))
    {
        printf("Usage: ./vigenere keyword\n");
        return 1;
    }
    string s = get_string ("plaintext:");
    string c_i = argv[1];
    int n = strlen(s);
    char ciphertext[n+1];
    encrypt(s,ciphertext,c_i);
    printf("ciphertext:%s\n", ciphertext);
    return 0;
}
void encrypt(string plaintext, string ciphertext, string cipher)
{
    int i=0;
    int k=0;

    for(i=0; i< strlen(plaintext); i++)  //Meet me
    {
        if(!isalpha(plaintext[i]))
        {
            ciphertext[i]= plaintext[i];
            continue;
        }
        else
        {
                k = k % strlen(cipher);
                printf("k: %d\n", k);
                char c = plaintext[i]; //M
            /*if(strlen(cipher) >= strlen(plaintext))  //Bacon
            {*/
                char ci = cipher[k]; // B
                char ci_low = tolower(ci); //b
                printf("Ci_low : %c\n", ci_low);
                int ci_integer = ci_low - 'a';
                printf("Ci_integer : %d\n", ci_integer);
                char c1 = tolower(plaintext[i]);
                char c_new = ((c1-'a'+ci_integer)%26) + 'a';
                printf("C_new : %c\n", c_new);
                ciphertext[i] = islower(c) ? c_new : toupper(c_new);

            /*}
            else
            {
                if(strlen(cipher) < i)  // cipher: bacon, plaintext: Meet me at the park.
                {
                int k = i % strlen(cipher);

                char ci = cipher[j]; // D
                printf("Ci2 : %c\n", ci);
                char ci_low = tolower(ci); //d
                printf("Ci_low2 : %c\n", ci_low);
                int ci_integer = ci_low - 'a';
                char c1 = tolower(plaintext[i]);
                char c_new = ((c1-'a'+ci_integer)%26) + 'a';
                ciphertext[i] = islower(c) ? c_new : toupper(c_new);
                }
            }*/
        k++;
        }

    }
    ciphertext[i]= '\0';
}
bool only_letter(string s)
{
    for(int i=0;i<strlen(s);i++)
    {
        char c = s[i];
        if(!isalpha(c))
        {
        return false;
        }
    }
    return true;
}