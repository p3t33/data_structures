#ifndef _STACK_H_
#define _STACK_H_
/****************************************************************
*                     Stack
*              =====================
* File Name: stack.h
* Related files: stack.c stack_test.c
* #Version: V 1.0
* Writer: Kobi Medrish       
* Created: 14.9.19
* Last update: 14.9.19
****************************************************************/

#include <stddef.h> /* size_t */
typedef struct stack stack_t;

/* 
 * Stack is an abstract data type that serves as a collection of elements, with
 * two principal operations: push, which adds an element to the collection, and
 * pop, which removes the most recently added element that was not yet removed.
 * The order in which elements come off a stack gives rise to its alternative
 * name, LIFO (last in, first out).
 */


stack_t *StackCreate(size_t element_size, size_t capacity);
 /* 
  * Creates a generic stack with specified capacity and element size
  *  
  * Params: 
  *		  element_size - char, int, size_t...
  *		  capacity - number of elements.
  * Return value : 
  *        a pointer to the stack or a NULL if failed to allocate memory for it.
  */


void StackDestroy(stack_t *stack_ptr);
 /* 
  * Destroy the stack by frying the allocated memory.
  *  
  * Params: 
  *		  stack_ptr - pointer to the stack. 
  *		  data  - the data to be inserted.
  */


int StackPush(stack_t *stack_ptr, const void *element);
 /* 
  * pushes an element to the top of the stack
  *  
  * Params: 
  *		  stack_ptr - pointer to the stack. 
  *		  element  - the data to push.
  * Return value : 
  *        0-(success), 1-(stack is full).
  * Complexity: O(1)
  */


void StackPop(stack_t *stack_ptr);
 /* 
  * removes a element from the top of the stack
  *  
  * Params: 
  *		  stack_ptr - pointer to the stack. 
  * Complexity: O(1)
  */


void *StackPeek(const stack_t *stack_ptr);
 /* 
  * Returns a pointer to the top element of the stack.
  *  
  * Params: 
  *		  stack_ptr - pointer to the stack. 
  *		  data  - the data to be inserted.
  * Return value: pointer to the top element or NULL if stack is empty.
  * 
  * Complexity: O(1) 
  */


size_t StackSize(const stack_t *stack_ptr);
 /* 
  * Returns the number of inserted elemnts to the stack.
  *  
  * Params: 
  *		  stack_ptr - pointer to the stack. 
  * Return value : 
  *        size of the stack
  * Complexity: O(1)
  */


 size_t StackIsEmpty(const stack_t *stack_ptr);
  /* 
   * Checks if the stack is empty
   *  
   * Params: 
   *		  stack_ptr - pointer to the stack. 
   * Return value : 
   *        0 -(stack is not empty), 1-(stack is empty).
   * Complexity: O(1)
   */


 size_t StackIsFull(const stack_t *stack_ptr);
  /* 
   * Checks if the stack is full.
   *  
   * Params: 
   *		  stack_ptr - pointer to the stack. 
   * Return value : 
   *        0 -(stack is not full), 1-(stack is full).
   * Complexity: O(1)
   */

#endif /* _STACK_H_ */
