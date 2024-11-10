// Programming Task 3

// Group Members:
// Clarence Ignacio
// Gabriel Valderama
// Jan Kevin Gerona
// Karl Joseph Logdat


#include <stdio.h>
#include <stdlib.h>

// circular linked list implementation
typedef struct Node {
    int value;
    struct Node* next;
} Node;

// when creating a node, point to itself initially instead of NULL
Node* NewNode(int key) {
    Node* node = (Node*) malloc(sizeof(Node));
    node->value = key;
    node->next = node;

    return node;
}

// this function assumes that head EXISTS and is not a nullptr
void Push(Node* head, Node* new) {
    Node* temp = head;
    while (temp->next != head) {
        temp = temp->next;
    }

    temp->next = new;
    new->next = head;
}

// problem related functions
// create adviser circular list using loops
Node* CreateAdviserCircle(int total_count) {
    Node* advisers = NewNode(1);
    for (int i = 2; i <= total_count; i++) {
        Push(advisers, NewNode(i));
    }

    return advisers;
}

void SelectAdvisers(Node* adviser_list_head, int start, int interval) {
    Node* temp = adviser_list_head;
    Node* prev = NULL;

    // move temporary to start
    while (temp->value != start) {
        prev = temp;
        temp = temp->next;
    }

    printf("\nChosen Advisers     : ");

    // track the number of advisers selected (MAX 5)
    int adviser_count = 0;
    while (adviser_count < 5) {
        for (int i = 1; i < interval; i++) {
            prev = temp;
            temp = temp->next;
        }

        printf("%d", temp->value);
        adviser_count++;
        if (adviser_count < 5) printf(", "); // formatting

        // remove node by linking prev to temp's next
        prev->next = temp->next; 
        free(temp);
        // this is the reason why our for loop starts at 1
        temp = prev->next;
    }
    printf("\n\n");

    // free remaining advisers after use
    // if we dont free, we leave 8 pointers per loop
    Node* current = temp;
    Node* next;
    do {
        next = current->next;
        free(current);
        current = next;
    } while (current != temp);
}

int main() {
    int start, interval;
    const int TOTAL_ADVISER_COUNT = 13;

    while(1) {
        printf("Start     : ");
        scanf(" %d", &start);
        // terminate program if user input is 0
        if (start == 0) break;

        printf("Interval  : ");
        scanf(" %d", &interval);

        // validate input
        if (start < 1 || start > 13 || interval < 1 || interval > 100) {
            printf("\nInvalid input.\n\n");
            continue;
        }

        // create new adviser circle every loop 
        Node* advisers = CreateAdviserCircle(TOTAL_ADVISER_COUNT);

        // actual program logic found in function
        SelectAdvisers(advisers, start, interval);
    }

    return 0;
}