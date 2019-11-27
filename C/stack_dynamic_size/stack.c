/*******************************************************************************
*                              Stack
*                     =====================
* File Name: stack.c
* Related files: stack.h stack_test.c
* #Version: V 1.1
* Writer: Kobi Medrish       
* Created: 25.11.19
* Last update: 27.11.19
*******************************************************************************/


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
#define MALLOC_FAIL NULL
#define STACK_IS_FULL 1
#define TRUE 1
#define FALSE 0
#define BEGINNING_OF_STACK NULL

/*============================================================================*/
/*                                                                    structs */
/*                                                                    ~~~~~~~ */
typedef struct node
{
	void *data;
	struct node *prev;
}node_t;

struct stack
{
	node_t *head; /* head of the actual memory allocated for the elements */
};


/*============================================================================*/
/*                               API functions                                */
/*============================================================================*/
/*                                                                StackCreate */
/*                                                                ~~~~~~~~~~~ */
stack_t *StackCreate()
{
    /* A pointer to managing struct and stack storage is created */
	stack_t* stack_ptr = (stack_t*)malloc(sizeof(stack_t));
	if (MALLOC_FAIL == stack_ptr)
	{
		return (MALLOC_FAIL);
	}

	stack_ptr->head = NULL;

	return (stack_ptr);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                                                               StackDestroy */
/*                                                               ~~~~~~~~~~~~ */
void StackDestroy(stack_t *stack_ptr)
{
	assert (stack_ptr);
	
	while(BEGINNING_OF_STACK != stack_ptr->head)
	{
		node_t * temp = stack_ptr->head;
		stack_ptr->head = stack_ptr->head->prev;
		free(temp);
		temp = NULL;
	}

	free (stack_ptr);
	stack_ptr = NULL;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                                                                  StackPush */
/*                                                                  ~~~~~~~~~ */
int StackPush(stack_t *stack_ptr, const void *element)
{
	assert(stack_ptr);
	assert(element);

	if (TRUE == StackIsEmpty(stack_ptr))
	{
		stack_ptr->head = (node_t*)malloc(sizeof(node_t));
		stack_ptr->head->prev = NULL;
		stack_ptr->head->data = (void*)element;

		return (0);
	}

	node_t *temp = (node_t*)malloc(sizeof(node_t));
	temp->prev = stack_ptr->head;
	temp->data = (void*)element;
	stack_ptr->head = temp;

	return (0);	
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                                                                   StackPop */
/*                                                                   ~~~~~~~~ */
void StackPop(stack_t *stack_ptr)
{
	assert(stack_ptr);

	if (TRUE == StackIsEmpty(stack_ptr))
	{
		return;
	}

	node_t *temp = stack_ptr->head;
	stack_ptr->head = stack_ptr->head->prev;
	free(temp);
	temp = NULL;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                                                                  StackPeek */
/*                                                                  ~~~~~~~~~ */
void *StackPeek(const stack_t *stack_ptr)
{
	assert(stack_ptr);
	if (TRUE == StackIsEmpty(stack_ptr))
	{
		return(NULL);
	}

	return (stack_ptr->head->data);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                                                                  StackSize */
/*                                                                  ~~~~~~~~~ */
size_t StackSize(const stack_t *stack_ptr)
{
	assert(stack_ptr);

	size_t counter = 0;
	node_t *runner = stack_ptr->head;

	while(NULL != runner)
	{
		++counter;
		runner = runner->prev;
	}

	return (counter);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                                                               StackIsEmpty */
/*                                                               ~~~~~~~~~~~~ */
 size_t StackIsEmpty(const stack_t *stack_ptr)
 {
	assert(stack_ptr);
	return (NULL == stack_ptr->head);
 }
