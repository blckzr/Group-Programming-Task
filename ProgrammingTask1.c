// Group Members:
// Clarence Ignacio
// Gabriel Valderama 
// Jan Kevin Gerona
// Karl Joseph Logdat

#include <stdio.h>
#include <stdlib.h>

// Define Node as a struct
struct Node {
    int data;
    struct Node* next;
};

// Function that creates a node
struct Node* createNode(int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->next = NULL;
    return newNode;
}

// Function that adds a node at the beginning
struct Node* addNode(struct Node *head, int value) {
    struct Node* newNode = malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->next = NULL;

    newNode->next = head;
    head = newNode;
    return head;
}

// Function that separates digits and creates a linked list
struct Node* createListNumber(struct Node *head, int n){
    while (n != 0){
        head = addNode(head, n%10);
        n /= 10;
    }
    return head;
}

// Function that reverses the linked list
struct Node* reverseList(struct Node *head){
    struct Node *current = NULL;
    struct Node *forward = head->next;
    head->next = NULL;

    while(forward != NULL){
        current = forward;
        forward = forward->next;
        current->next = head;
        head = current;
    }

    return head;
}

// Function that pushes a node to the beginning of the list
struct Node* push(struct Node *head, int value){
    struct Node* newNode = malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->next = head;
    return newNode;
}

// Function that adds two linked lists and returns the sum
struct Node* addLinkedLists(struct Node* head1, struct Node* head2) {
    struct Node* result = NULL;
    struct Node* temp1 = head1;
    struct Node* temp2 = head2;
    int carry = 0, sum = 0;

    while (temp1 != NULL || temp2 != NULL) {
        sum = 0;
        if(temp1){
            sum += temp1->data;
            temp1 = temp1->next;
        }
        if(temp2){
            sum += temp2->data;
            temp2 = temp2->next;
        }
        sum += carry;
        carry = sum/10;
        sum %= 10;

        result = push(result, sum);
    }

    if(carry){
        result = push(result, carry);
    }

    return result;
}

// Function that prints the linked list
void printList(struct Node* head) {
    struct Node* temp = head;
    while (temp != NULL) {
        printf("%d", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

int main() {
    int x, y;

    // Input two numbers
    printf("Enter the first number: ");
    scanf("%d", &x);
    printf("Enter the second number: ");
    scanf("%d", &y);

    // Initialize empty linked lists
    struct Node* l1 = NULL; 
    struct Node* l2 = NULL;  

    // Add digits of x and y to linked lists
    l1 = createListNumber(l1, x);
    l2 = createListNumber(l2, y);
    
    // Reverse both linked lists for addition
    l1 = reverseList(l1);
    l2 = reverseList(l2);

    // Get the sum of two linked lists
    struct Node *result = addLinkedLists(l1, l2);
    printf("Sum of Linked List: ");
    printList(result);

    return 0;
}
