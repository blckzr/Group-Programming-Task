#ifndef LINKED_LIST
#define LINKED_LIST

typedef struct LLNodeInt {
    int value;
    struct LLNodeInt* next;
} LLNodeInt;


/** 
 * @brief Create new integer linked list node.
 * 
 * @param value Value of the node
 * 
 * @return Node pointer with the value. 
 */
LLNodeInt* NewLLNodeInt(int value);

/**
 * @brief Add integer linked list node to head of linked list
 * 
 * @param head Memory address of linked list head pointer
 * @param new New node to be inserted to list
 */
void InsertAtHead_LLNodeInt(LLNodeInt** head, LLNodeInt* newNode);

/**
 * @brief Add integer linked list node to tail of linked list
 * 
 * @param head Memory address of linked list head pointer
 * @param new New node to be inserted to list
 */
void InsertAtTail_LLNodeInt(LLNodeInt** head, LLNodeInt* newNode);

/**
 * @brief Delete a node from integer linked list by value
 * 
 * @param head Memory address of linked list head pointer
 * @param value Value of node to delete 
 */
void Delete_LLNodeInt(LLNodeInt** head, int value);

#endif