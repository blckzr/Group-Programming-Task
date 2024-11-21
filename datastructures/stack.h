#ifndef STACK_H
#define STACK_H

typedef struct SNodeInt {
    int value;
    struct SNodeInt* next;
} SNodeInt;

typedef struct StackInt {
  SNodeInt* head;
} StackInt;

/**
 * @brief Create new stack node of type integer
 *
 * @param value Desired integer value
 *
 * @return Pointer to stack node of type integer
 */
SNodeInt* NewSNodeInt(int value);


/**
 * @brief Create empty integer stack
 * 
 * @return Pointer to empty integer stack
 */
StackInt* NewStackInt();

/**
 * @brief Push an integer value to an existing stack 
 * 
 * @param stk Address of pointer to integer stack
 * @param value Integer value to push
 */
void PushToStackInt(StackInt** stk, int value);

/**
 * @brief Remove top integer value from stack 
 * 
 * @param stk Address of pointer to integer stack
 * 
 * @return Integer value of stack head (after removing)
 */
int PopFromStackInt(StackInt** stk);

/**
 * @brief Return top integer value in integer stack without removal
 * 
 * @param stk Address of pointer to integer stack
 * 
 * @return Integer value of stack head (not removed)
 */
int PeekInStackInt(StackInt** stk);

#endif