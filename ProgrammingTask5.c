// Group Members:
// Clarence Ignacio
// Gabriel Valderama 
// Jan Kevin Gerona
// Karl Joseph Logdat

// REFERENCE
// - https://www.geeksforgeeks.org/print-postorder-from-given-inorder-and-preorder-traversals/

#include <stdio.h>
#include <stdlib.h>

void getFile(){
    // file crud here
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
    printf("%c ", root);
}

int main() {
    // TODO: Input should be from text file
    char pre[] = {'D', 'B', 'A', 'C', 'E', 'G', 'F'};
    char in[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G'};
    int n = sizeof(in) / sizeof(in[0]);
    int preIndex = 0;

    printPostOrder(in, pre, 0, n - 1, &preIndex, n);
    return 0;
}