// Group Members:
// Clarence Ignacio
// Gabriel Valderama 
// Jan Kevin Gerona
// Karl Joseph Logdat

// REFERENCE
// - https://www.geeksforgeeks.org/print-postorder-from-given-inorder-and-preorder-traversals/
// - https://stackoverflow.com/questions/5850000/how-to-split-array-into-two-arrays-in-c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Remove all whitespaces and newline characters from a string
void cleanAndTrimString(char *string){
    int length = strlen(string);

    int j = 0;
    for (int i = 0; i < length; i++){
        if (string[i] != ' ' && string[i] != '\n'){
            string[j] = string[i];
            j++;
        }
    }
    string[j] = '\0';
}

int search(char* arr, int n, char x) {
    for (int i = 0; i < n; i++)
        if (arr[i] == x)
            return i;
    return -1;
}

void printPostOrder(char* in, char* pre, int inStart, int inEnd, int* preIndex, int n) {
    // Base case
    if (inStart > inEnd)
        return;

    // Current root is at *preIndex in the preorder array
    char root = pre[*preIndex];
    (*preIndex)++;

    // Find the root index in the inorder array
    int rootIndex = search(in, n, root);

    // Recur for the left subtree
    printPostOrder(in, pre, inStart, rootIndex - 1, preIndex, n);

    // Recur for the right subtree
    printPostOrder(in, pre, rootIndex + 1, inEnd, preIndex, n);

    // Print the root (postorder)
    printf("%c", root);
}

int countElements(char *string) {
    int count = 0;
    for (int i = 0; string[i] != '\0'; i++) {
        count++; // Count each character until null terminator
    }
    return count;
}

void splitAndPrint(char *line){
    char pre[50], in[50];
    int count = countElements(line);
    int mid = count / 2;

    strncpy(pre, line, mid);
    pre[mid] = '\0';
    strncpy(in, line + mid, count - mid);
    in[count - mid] = '\0';

    int preIndex = 0;
    printPostOrder(in, pre, 0, mid - 1, &preIndex, mid);
    printf("\n");
}

void readFile() {
    // All variables declaration for this function
    FILE *file;
    char currentLine[100];

    file = fopen("input.txt", "r");
    if (file == NULL) {
        printf("Error: Could not open file.\n");
        return;
    }

    // Reads line and split into two array for pre-order and in-order
    while (fgets(currentLine, sizeof(currentLine), file)) {
        cleanAndTrimString(currentLine);
        splitAndPrint(currentLine);
    }

    fclose(file);
}

int main() {
    readFile();
    return 0;
}

