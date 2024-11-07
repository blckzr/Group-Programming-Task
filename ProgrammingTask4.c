// Group Members:
// Clarence Ignacio
// Gabriel Valderama 
// Jan Kevin Gerona
// Karl Joseph Logdat

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node* left;
    struct Node* right;
} Node;

Node* NewNode(int value) {
    Node* node = (Node*) malloc(sizeof(Node));
    node->value = value;
    node->left = NULL;
    node->right = NULL;

    return node;
}

void InOrder(Node* node) {
    if (node == NULL)
        return;

    InOrder(node->left);
    printf("%d ",node->value);
    InOrder(node->right);
}

void PreOrder(Node* node) {
    if (node == NULL)
        return;
    
    printf("%d ",node->value);
    PreOrder(node->left);
    PreOrder(node->right);
}

void PostOrder(Node* node) {
    if (node == NULL)
        return;
    
    PostOrder(node->left);
    PostOrder(node->right);
    printf("%d ", node->value);
}

int main(){
    // TEST CODE LANG TONG ASA MAIN
    // Delete niyo nalang if ccode niyo na mismo
    //      1
    //     / \
    //    2  3
    //   / \ 
    //  4  5
    Node* root = NewNode(1);
    root->left = NewNode(2);
    root->right = NewNode(3);
    root->left->left = NewNode(4);
    root->left->right = NewNode(5);

    InOrder(root);
    printf("\n");
    PreOrder(root);
    printf("\n");
    PostOrder(root);
    printf("\n");

    return 0;
}