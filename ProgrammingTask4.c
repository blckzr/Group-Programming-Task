// Group Members:
// Clarence Ignacio
// Gabriel Valderama 
// Jan Kevin Gerona
// Karl Joseph Logdat

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void printPreOrder(Node *root) {
    if (root == NULL) {
        return;
    }

    // skip leaf nodes
    if (root->left == NULL && root->right == NULL) {
        return;
    }

    // print the current node and children
    printf("%-4c ", root->value);
    if (root->left) {
        printf("%-10c", root->left->value);
    } else {
        printf("%-10s", "null");
    }
    if (root->right) {
        printf("%-10c", root->right->value);
    } else {
        printf("%-10s", "null");
    }
    printf("\n");

    printPreOrder(root->left);
    printPreOrder(root->right);
}

void getInput(Node** root) {
    char line[100]; // string buffer
    char node, left[10], right[10];

    printf("Enter lines in the format (A,B,null). Type 'exit' to stop:\n");

    while (1) {
        // read line
        if (fgets(line, 100, stdin) == NULL) {
            break;
        }

        // remove newline character at the end of the line (if present)
        line[strcspn(line, "\n")] = '\0';

        // check for termination 
        if (strcmp(line, "exit") == 0) {
            break;
        }

        // parse line, handle "null"
        if (sscanf(line, "(%c,%[^,],%[^)])", &node, left, right) == 3) {
            // convert "null" to 'n' or keep the actual character
            if (strcmp(left, "null") == 0) {
                strcpy(left, "n");
            }
            if (strcmp(right, "null") == 0) {
                strcpy(right, "n");
            }
        } else {
            printf("Invalid format. Please try again.\n");
        }

        AddNode(root, node, left[0], right[0]);
    }
}

int main(){
    // initialize empty tree
    Node* root = NULL;

    getInput(&root);

    printf("\nNode L-Subtree R-Subtree\n");
    printPreOrder(root);

    printf("\nRoot: %c\n", root->value);

    printf("\nPreorder Traversal: ");
    PreOrder(root);
    printf("\n");
    printf("Inorder Traversal: ");
    InOrder(root);
    printf("\n");
    printf("Postorder Traversal: ");
    PostOrder(root);
    printf("\n");

    return 0;
}
