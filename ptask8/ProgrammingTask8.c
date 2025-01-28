// Group Members:
// Clarence Ignacio
// Gabriel Valderama 
// Jan Kevin Gerona
// Karl Joseph Logdat

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define TABLE_SIZE 25000  // Size of the hash table

typedef struct Node {
    char *word;
    struct Node *next;
} Node;

typedef struct {
    Node *buckets[TABLE_SIZE];
} HashTable;

// Hash function - simple example
unsigned long hash(const char *str) {
    unsigned long hash = 5381;
    int c;

    while ((c = *str++))
        hash = ((hash << 5) + hash) + c;  // hash * 33 + c

    return hash % TABLE_SIZE;
}

// Comparator function for qsort
int char_cmp(const void *a, const void *b) {
    return *(char *)a - *(char *)b;
}

// Insert word into hash table
void insert(HashTable *ht, const char *word) {
    // Create a copy of the word
    char *copy = strdup(word);

    // Sort the word to get its key (alphagram)
    char key[strlen(copy) + 1];
    strcpy(key, copy);
    qsort(key, strlen(key), sizeof(char), char_cmp);

    // Compute the hash
    unsigned long index = hash(key);

    // Create a new node
    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->word = copy;
    new_node->next = ht->buckets[index];
    ht->buckets[index] = new_node;
}

// Load dictionary into hash table
void load_dictionary(HashTable *ht, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    char word[100];
    while (fscanf(file, "%s", word) != EOF) {
        // Normalize the word (convert to lowercase)
        for (char *p = word; *p; ++p) *p = tolower(*p);

        // Insert the word into the hash table
        insert(ht, word);
    }

    fclose(file);
}

// Search for anagrams of a given word and write to output file
void find_anagrams(HashTable *ht, const char *query, FILE *output) {
    // Normalize the query
    char norm_query[strlen(query) + 1];
    strcpy(norm_query, query);
    for (char *p = norm_query; *p; ++p) *p = tolower(*p);

    // Sort the query to get its key
    qsort(norm_query, strlen(norm_query), sizeof(char), char_cmp);
    unsigned long index = hash(norm_query);

    // Search the hash table for anagrams
    Node *current = ht->buckets[index];
    int count = 0;

    // Prepare to store the results
    char result[500] = ""; // Assume no line will exceed 500 characters
    strcat(result, query); // Start with the original query

    while (current) {
        char sorted_word[strlen(current->word) + 1];
        strcpy(sorted_word, current->word);
        qsort(sorted_word, strlen(sorted_word), sizeof(char), char_cmp);

        // Check if sorted word matches the sorted query and avoid self-matching
        if (strcmp(sorted_word, norm_query) == 0 && strcmp(query, current->word) != 0) {
            count++;
            strcat(result, " ");
            strcat(result, current->word);
        }
        current = current->next;
    }

    // Write the query, count, and all matching anagrams in the required format
    fprintf(output, "%s %d%s\n", query, count, count > 0 ? result + strlen(query) : "");
}

// Utility function for freeing the hash table
void free_table(HashTable *ht) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        Node *current = ht->buckets[i];
        while (current) {
            Node *next = current->next;
            free(current->word);
            free(current);
            current = next;
        }
    }
}

// Main function
int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <input_file> <output_file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    HashTable ht = {0};

    // Load the dictionary
    load_dictionary(&ht, "words.txt");

    FILE *input = fopen(argv[1], "r");
    FILE *output = fopen(argv[2], "w");
    if (!input || !output) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    char query[100];
    while (fscanf(input, "%s", query) != EOF) {
        // Find and write anagrams to output file
        find_anagrams(&ht, query, output);
    }

    fclose(input);
    fclose(output);

    // Clean up
    free_table(&ht);

    return 0;
}

