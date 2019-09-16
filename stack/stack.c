/****************************************************************
*                              Stack
*                     =====================
* File Name: stack.c
* Related files: stack.h stack_test.c
* #Version: V 1.0
* Writer: Kobi Medrish       
* Created: 14.9.19
* Last update: 14.9.19
****************************************************************/


/*============================================================================*/
/*                                  Definitions                               */
/*============================================================================*/
/*                                                      standard  directories */
/*                                                      ~~~~~~~~~~~~~~~~~~~~~ */
#include <stdlib.h> /* malloc, free */
#include <assert.h> /* assert */
#include <string.h> /* memcopy */

/*============================================================================*/
/*                                                          local directories */
/*                                                          ~~~~~~~~~~~~~~~~~ */
#include "stack.h" 

/*============================================================================*/
/*                                                                     Macros */
/*                                                                     ~~~~~~ */
#define MALLOC_FAIL (NULL)
#define STACK_IS_FULL (1)
#define TRUE 1
#define FALSE 0

/*============================================================================*/
/*                                                                    structs */
/*                                                                    ~~~~~~~ */
 struct stack {

	void *end; /* the last position of the stack */
	void *current; /* most recent element in the stack */
	size_t element_size; 
	char start[1]; /* start of the actual memory allocated for the elements */
};

/*============================================================================*/
/*                               API functions                                */
/*============================================================================*/
/*                                                                StackCreate */
/*                                                                ~~~~~~~~~~~ */
stack_t *StackCreate(size_t element_size, size_t capacity)
{
	/* A pointer to managing struct and stack storage is created */
	stack_t* stack_ptr = (stack_t*)malloc(sizeof(stack_t) + 
	                                     (element_size * capacity));
	if (MALLOC_FAIL == stack_ptr)
	{
		return (MALLOC_FAIL);
	}

	stack_ptr->end = stack_ptr->start + (element_size * (capacity));
	stack_ptr->current = stack_ptr->start;
	stack_ptr-> element_size = element_size;

	return (stack_ptr);
}

/*============================================================================*/
/*                                                               StackDestroy */
/*                                                               ~~~~~~~~~~~~ */
void StackDestroy(stack_t *stack_ptr)
{
	assert(stack_ptr);

	free(stack_ptr);
	stack_ptr = NULL;
}

/*============================================================================*/
/*                                                                  StackPush */
/*                                                                  ~~~~~~~~~ */
int StackPush(stack_t *stack_ptr, const void *element)
{
	assert(stack_ptr);
	assert(element);

	if (TRUE == StackIsFull(stack_ptr))
	{
		return(STACK_IS_FULL);
	}

	memcpy(stack_ptr->current, element, stack_ptr->element_size);
	stack_ptr->current = (char*)stack_ptr->current + stack_ptr->element_size;

	return (0); 
}

/*============================================================================*/
/*                                                                   StackPop */
/*                                                                   ~~~~~~~~ */
void StackPop(stack_t *stack_ptr)
{
	assert(stack_ptr);

	if (TRUE != StackIsEmpty(stack_ptr))
	{
		stack_ptr->current = (char*)stack_ptr->current - 
                             stack_ptr->element_size;
	}
}

/*============================================================================*/
/*                                                                  StackPeek */
/*                                                                  ~~~~~~~~~ */
void *StackPeek(const stack_t *stack_ptr)
{
	assert(stack_ptr);
	if (TRUE == StackIsEmpty(stack_ptr))
	{
		return(NULL);
	}

	return ((char*)stack_ptr->current - stack_ptr->element_size);
}

/*============================================================================*/
/*                                                                  StackSize */
/*                                                                  ~~~~~~~~~ */
size_t StackSize(const stack_t *stack_ptr)
{
	assert(stack_ptr);

	return(((char*)stack_ptr->current - stack_ptr->start) /
	         stack_ptr->element_size);
}

/*============================================================================*/
/*                                                               StackIsEmpty */
/*                                                               ~~~~~~~~~~~~ */
 size_t StackIsEmpty(const stack_t *stack_ptr)
 {
	assert(stack_ptr);
	return (stack_ptr->current == stack_ptr->start);
 }

/*============================================================================*/
/*                                                                StackIsFull */
/*                                                                ~~~~~~~~~~~ */
 size_t StackIsFull(const stack_t *stack_ptr)
 {
	assert(stack_ptr);
	return (stack_ptr->current == stack_ptr->end);
 }