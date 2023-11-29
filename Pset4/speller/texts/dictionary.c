// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>

#include "dictionary.h"

// Represents number of buckets in a hash table
#define N 26

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Represents a hash table
node *hashtable[N];

// Hashes word to a number between 0 and 25, inclusive, based on its first letter
unsigned int hash(const char *word)
{
    return tolower(word[0]) - 'a';
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Initialize hash table
    for (int i = 0; i < N; i++)
    {
        hashtable[i] = NULL;
    }

    // Open dictionary
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        unload();
        return false;
    }

    // Buffer for a word
    char word[LENGTH + 1];

    // Insert words into hash table
    while (fscanf(file, "%s", word) != EOF)
    {
        node *new_node = malloc(sizeof(node));

         if (new_node == NULL)
        {
            return false;
        }

            strcpy(new_node->word, word);
        // head elde etmek için elde kelimeyi hash hale getirin
        head = hash(word);
        // Yeni işaretçi ayarla
        new_node->next = hashtable[head];
        // head'i yeni işaretçiye ayarla
        hashtable[head] = new_node;
        // Kelime sayısını artır
        word_count++;

    }

    // Close dictionary
    fclose(file);

    // Indicate success
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    if (word_count > 0)
    {
        // yüklenen kelime sayısını verir
        return word_count;
    }
    return 0;
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{
     head = hash(word);
    //bağlantılı listeye eriş
    node *cursor = hashtable[head];
//bağlantılı listeyi gözden geçirin
    while (cursor != NULL)
    {
        //kelimenin eşleşip eşleşmediğini kontrol edin
        if (strcasecmp(word, cursor->word) == 0)
        {
            return true;
        }
//imleci sonraki düğüme taşı
        cursor = cursor->next;
    }
    return false;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
     for (int i = 0; i < N; i++)
    {
        // Her hash kovası için cursor'u ayarlar
        node *cursor = hashtable[i];

   while (cursor != NULL)
   {
       node *temp = cursor;
       cursor = cursor ->next;
       free (temp);
   }
   // Eğer cursor NULL ise
        if (i == N - 1 && cursor == NULL)
        {
            return true;
        }
    }
    return false;
}
