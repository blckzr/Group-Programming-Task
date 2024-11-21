// Group Members:
// Clarence Ignacio
// Gabriel Valderama 
// Jan Kevin Gerona
// Karl Joseph Logdat

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    char value;
    struct Node* left;
    struct Node* right;
} Node;

Node* NewNode(char value) {
    Node* node = (Node*) malloc(sizeof(Node));
    node->value = value;
    node->left = NULL;
    node->right = NULL;

    return node;
}

// haha kita ko lang online ung way pano magsearch ng value sa tree
Node* SearchNode(Node* root, char value) {
    if (root == NULL) return NULL;
    if (root->value == value) return root;

    Node* left = SearchNode(root->left, value);
    if (left) return left;

    return SearchNode(root->right, value);
}

// double pointer because c pointer bs
// essentially, use double pointer to modify the passed pointer
// READ:
// https://stackoverflow.com/questions/5580761/why-use-double-indirection-or-why-use-pointers-to-pointers
// https://www.quora.com/Why-there-is-a-need-of-double-pointer
void AddNode(Node** root, char rootValue, char leftValue, char rightValue) {
    Node* rootNode = SearchNode(*root, rootValue);
    if (!rootNode) {
        rootNode = NewNode(rootValue);
        // if tree is empty
        if (*root == NULL) *root = rootNode;
    }

    // create nodes with values if not NULL
    if (leftValue != 'n') rootNode->left = NewNode(leftValue);
    if (rightValue != 'n') rootNode->right = NewNode(rightValue);
}

void InOrder(Node* node) {
    if (node == NULL)
        return;

    InOrder(node->left);
    printf("%c ",node->value);
    InOrder(node->right);
}

void PreOrder(Node* node) {
    if (node == NULL)
        return;
    
    printf("%c ",node->value);
    PreOrder(node->left);
    PreOrder(node->right);
}

void PostOrder(Node* node) {
    if (node == NULL)
        return;
    
    PostOrder(node->left);
    PostOrder(node->right);
    printf("%c ", node->value);
}

int main(){
    // initialize empty tree
    Node* root = NULL;

    // TODO:
    // pa handle nalang kung pano iinput to ng user nyahaha
    // also also formatting ng output
    AddNode(&root, 'A', 'B', 'E');
    AddNode(&root, 'B', 'C', 'n');
    AddNode(&root, 'C', 'n', 'D');
    AddNode(&root, 'E', 'F', 'H');
    AddNode(&root, 'F', 'n', 'G');
    AddNode(&root, 'H', 'I', 'J');

    InOrder(root);
    printf("\n");
    PreOrder(root);
    printf("\n");
    PostOrder(root);
    printf("\n");

    return 0;
}