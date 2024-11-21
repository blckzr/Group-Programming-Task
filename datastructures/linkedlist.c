#include "linkedlist.h"
#include <stdio.h>

LLNodeInt* NewLLNodeInt(int value) {
    LLNodeInt* node = (LLNodeInt*) malloc(sizeof(LLNodeInt));

    node->value = value;
    node->next = NULL;

    return node;
}

void InsertAtHead_LLNodeInt(LLNodeInt** head, LLNodeInt* newNode) {
    newNode->next = *head;
    *head = newNode;
}

void InsertAtTail_LLNodeInt(LLNodeInt** head, LLNodeInt* newNode) {
    if (*head == NULL) {
        *head = newNode;
        return;
    }

    LLNodeInt* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
}

void Delete_LLNodeInt(LLNodeInt** head, int value) {
    if (*head == NULL) {
        printf("Error, trying to delete from empty integer list.\n");
        return;
    }

    LLNodeInt* temp = *head;

    // handle if head holds the value
    if (temp->value == value) {
        *head = temp->next;
        free(temp);
        return;
    }

    // search for node
    LLNodeInt* prev = NULL;
    while (temp != NULL && temp->value != value)
    {
        prev = temp;
        temp = temp->next;
    }

    // if no node is found
    if (temp == NULL) {
        printf("Error, target value not found in integer list.\n");
        return;
    }

    prev->next = temp->next;
    free(temp);
}