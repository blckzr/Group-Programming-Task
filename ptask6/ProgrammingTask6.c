// Group Members:
// Clarence Ignacio
// Gabriel Valderama 
// Jan Kevin Gerona
// Karl Joseph Logdat

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Function to create the LPS (Longest Prefix Suffix) array for KMP
void computeLPSArray(char* pattern, int patternLength, int* lps) {
    int length = 0;
    lps[0] = 0; // lps[0] is always 0
    int i = 1;

    while (i < patternLength) {
        if (pattern[i] == pattern[length]) {
            length++;
            lps[i] = length;
            i++;
        } else {
            if (length != 0) {
                length = lps[length - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
}

// KMP algorithm to find pattern matches
int KMPSearch(char* pattern, char* text) {
    int patternLength = strlen(pattern);
    int textLength = strlen(text);

    int* lps = (int*)malloc(patternLength * sizeof(int));
    computeLPSArray(pattern, patternLength, lps);

    int i = 0; // index for text
    int j = 0; // index for pattern
    int matchCount = 0;

    while (i < textLength) {
        if (pattern[j] == text[i]) {
            j++;
            i++;
        }

        if (j == patternLength) {
            matchCount++;
            j = lps[j - 1];
        } else if (i < textLength && pattern[j] != text[i]) {
            if (j != 0) {
                j = lps[j - 1];
            } else {
                i++;
            }
        }
    }

    free(lps);
    return matchCount;
}

int main() {
    char filename[100];
    char text[1000];
    char pattern[100];
    char choice;

    do {
        printf("Enter filename: ");
        scanf("%s", filename);

        FILE* file = fopen(filename, "r");
        if (!file) {
            printf("Error: Unable to open file %s\n", filename);
            return 1;
        }

        // Read the content of the file into text
        if (!fgets(text, sizeof(text), file)) {
            printf("Error: Unable to read the file content\n");
            fclose(file);
            return 1;
        }
        fclose(file);

        // Remove the newline character if it exists
        text[strcspn(text, "\n")] = 0;

        printf("TEXT: %s\n", text);

        printf("Enter PATTERN: ");
        scanf("%s", pattern);

        int matchCount = KMPSearch(pattern, text);
        if (matchCount > 0) {
            printf("Total number of matches: %d\n", matchCount);
        } else {
            printf("No matches found!\n");
        }

        printf("Again (y/n): ");
        scanf(" %c", &choice);

    } while (choice == 'y' || choice == 'Y');

    return 0;
}

