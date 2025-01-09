// Group Members:
// Clarence Ignacio
// Gabriel Valderama 
// Jan Kevin Gerona
// Karl Joseph Logdat

// REFERENCE
// - https://www.geeksforgeeks.org/print-postorder-from-given-inorder-and-preorder-traversals/

#include <stdio.h>
#include <stdlib.h>

int search(int* arr, int n, int x) {
    for (int i = 0; i < n; i++)
        if (arr[i] == x)
            return i;
    return -1;
}

void printPostOrder(int* in, int* pre, int inStart, int inEnd, int preStart, int n) {
    // Base case
    if (inStart > inEnd)
        return;

    // Find the root index in the inorder array
    int rootIndex = search(in, n, pre[preStart]);

    // If left subtree is not empty, print left subtree
    if (rootIndex > inStart) {
        printPostOrder(in, pre, inStart, rootIndex - 1, preStart + 1, n);
    }

    // If right subtree is not empty, print right subtree
    if (rootIndex < inEnd) {
        printPostOrder(in, pre, rootIndex + 1, inEnd, preStart + rootIndex - inStart + 1, n);
    }

    // Print root
    printf("%d ", pre[preStart]);
}

int main() {
    int in[] = {4, 2, 5, 1, 3, 6};
    int pre[] = {1, 2, 4, 5, 3, 6};
    int n = sizeof(in) / sizeof(in[0]);

    printPostOrder(in, pre, 0, n - 1, 0, n);
    return 0;
}
