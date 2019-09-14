#include <stdlib.h>
#include <stddef.h> /* size_t */
#include <stdio.h>
#include <assert.h>
#include "stack.h"

#include <string.h> /* memcopy */

#define MALLOC_FAIL (NULL)
#define STACK_IS_FULL (1)

struct stack {

    void *end; /* the last position of the stack */
    void *current; /* most recent element in the stack */
    size_t element_size; 
	char start[1]; /* start of the actual memory allocated for the elements */
};


stack_t *StackCreate(size_t element_size, size_t capacity)
{
	/* A pointer to managing struct is created */
    stack_t* stack_ptr = (stack_t*)malloc(sizeof(stack_t) +
	                                       (element_size * capacity));
	if (MALLOC_FAIL == stack_ptr)
	{
		return (MALLOC_FAIL);
	}
	
	/* The zeroth element is taken into account  */	
	stack_ptr->end = stack_ptr->start + (element_size * (capacity));
	stack_ptr->current = stack_ptr->start;
    stack_ptr-> element_size = element_size;

    return (stack_ptr);
}


/* stack_t *StackCreate(size_t element_size, size_t capacity)
{
    stack_t *new_stack = (stack_t *)malloc(sizeof(stack_t));
    if (NULL == new_stack)
    {
        return NULL;
    }
    

    new_stack->start = (void *)calloc(capacity, element_size);
    if (NULL == new_stack->start)
    {
        return NULL;
    }
    
    new_stack->element_size = element_size;
    new_stack->end = (char *)new_stack->start + (element_size * capacity);
    new_stack->current = new_stack->start;
    
    return (new_stack);
} */





void StackDestroy(stack_t *stack_ptr)
{
	assert(stack_ptr);
	
    free(stack_ptr);
    stack_ptr = NULL;
}



int StackPush(stack_t *stack_ptr, const void *element)
{
	assert(stack_ptr);
	assert(element);

	if (stack_ptr->end == stack_ptr->current)
	{
		return(STACK_IS_FULL);
	}

	puts("write\n");

	memcpy(stack_ptr->current, element, stack_ptr->element_size);
	stack_ptr->current = (char*)stack_ptr->current + stack_ptr->element_size;

	return (0); 
}

void StackPop(stack_t *stack_ptr)
{
	assert(stack_ptr);
	
	if (stack_ptr->current > (void*)stack_ptr->start)
	{
		stack_ptr->current = (char*)stack_ptr->current - 
		                      stack_ptr->element_size;
	}
}




void *StackPeek(const stack_t *stack_ptr)
{
	assert(stack_ptr);
	if (stack_ptr->start == stack_ptr->current)
	{
		return(NULL);
	}

	return ((char*)stack_ptr->current - stack_ptr->element_size);
}

size_t StackSize(const stack_t *stack_ptr)
{
	assert(stack_ptr);
	
	return (((size_t*)stack_ptr->current - (size_t*)stack_ptr->start) /
	         stack_ptr->element_size);
	
}
