#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

int get_index(string s);
int main(void)
{
string text = get_string ("Text:");
int index = get_index(text);
    if(index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if(index>=16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade: %d\n", index);
    }
}
int get_index(string s)
{
    int letters=0, words=0, sentences=0;
    for(int i=0; i<strlen(s); i++)
    {
        char c = s[i];
        if(isalpha(c))
        {
            letters++;
        }
        if(isspace(c))
        {
            words++;
        }
        if(c=='.' || c=='!' || c=='?')
        {
            sentences++;
        }
    }
    words++;

    float L = (letters* 100.0f)/words;
    float S = (sentences* 100.0f)/words;
    return round(0.0588 * L - 0.296 * S - 15.8);
}