/*******************************************************************************
*                             stack_test.c
*                       ========================
* File Name: stack_test.c
* Related files: stack.h stack.c
* #Version: V 1.0
* Writer: Kobi Medrish       
* Created: 25.11.19
* Last update: 25.11.19
*******************************************************************************/

/*============================================================================*/
/*                                  Definitions                               */
/*============================================================================*/
/*                                                       Standard directories */
/*                                                       ~~~~~~~~~~~~~~~~~~~~ */
#include <stdio.h> /* printf */
#include <assert.h> /* assert */

/*============================================================================*/
/*                                                          local directories */
/*                                                          ~~~~~~~~~~~~~~~~~ */
#include "stack.h"

/*============================================================================*/
/*                                                                     Macros */
/*                                                                     ~~~~~~ */
#define ELEMENT_SIZE (sizeof(int))
#define STACK_CAPACITY (5)
/*                                                                     Colors */
/*                                                                     ~~~~~~ */
#define GREEN "\033[1;32m"
#define RED "\033[0;31m"
#define YELLOW "\033[1;33m"
#define RESET "\033[0m"

/*============================================================================*/
/*                         function forward declarations                      */
/*                         ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~                      */
/*                                                                 Unit tests */
/*                                                                 ~~~~~~~~~~ */
static void UnitTestStackCreate(void);
static void UnitTestStackPush(void);
static void UnitTestStackPop(void);

/*============================================================================*/

int main()
{
    UnitTestStackCreate();
    UnitTestStackPush();
    UnitTestStackPop();

    return (0);
}

/*============================================================================*/
/*                                 UnitTests                                  */
/*============================================================================*/
/*                                                        UnitTestStackCreate */
/*                                                        ~~~~~~~~~~~~~~~~~~~ */
static void UnitTestStackCreate(void)
{
	stack_t *stack_handle = StackCreate(ELEMENT_SIZE, STACK_CAPACITY);

    printf("===================== UnitTestStackCreate ==================\n");    
  
	if (NULL != stack_handle)
	{
		printf("Stack created:" GREEN "SUCCESS\n" RESET);
	}
	else
	{
		printf("Stack created:" RED "FAILURE\n" RESET);
	}

	if (0 == StackSize(stack_handle))
	{
		printf("StackSize on empty stack :" GREEN "SUCCESS\n" RESET);
	}
	else
	{
		printf("StackSize on empty stack:" RED "FAILURE\n" RESET);
	}
	
	if (1 == StackIsEmpty(stack_handle))
	{
		printf("StackIsEmpty on empty stack :" GREEN "SUCCESS\n" RESET);
	}
	else
	{
		printf("StackIsEmpty on empty stack:" RED "FAILURE\n" RESET);
	}

	if (0 == StackIsFull(stack_handle))
	{
		printf("StackIsFull on empty stack :" GREEN "SUCCESS\n" RESET);
	}
	else
	{
		printf("StackIsFull on empty stack:" RED "FAILURE\n" RESET);
	}
	
	StackDestroy(stack_handle);

    printf("============================================================\n\n");
}

/*============================================================================*/
/*                                               UnitTestStackPush */
static void UnitTestStackPush(void)
{
	stack_t *stack_handle = StackCreate(ELEMENT_SIZE, STACK_CAPACITY);

	int source[5] = {8, 2, 3, 4, 5};
	size_t i = 0;
    printf("===================== UnitTestStackPush ====================\n");    
    
	puts("Push 5 numbers to the stack");

	for (i = 0; i < STACK_CAPACITY; ++i)
	{
		StackPush(stack_handle, &source[i]);

		printf("%d ", *(int*)StackPeek(stack_handle));
	}
	
	puts("");

	if (1 == StackPush(stack_handle, &source[0]))
	{
		printf("StackPush to full stack :" GREEN "SUCCESS\n" RESET);
	}
	else
	{
		printf("StackPush to full stack :" RED "FAILURE\n" RESET);	
	}

	if (STACK_CAPACITY == StackSize(stack_handle))
	{
		printf("StackSize on empty stack :" GREEN "SUCCESS\n" RESET);
	}
	else
	{
		printf("StackSize on empty stack:" RED "FAILURE\n" RESET);
	}
	
	if (0 == StackIsEmpty(stack_handle))
	{
		printf("StackIsEmpty on full stack :" GREEN "SUCCESS\n" RESET);
	}
	else
	{
		printf("StackIsEmpty on full stack:" RED "FAILURE\n" RESET);
	}

	if (1 == StackIsFull(stack_handle))
	{
		printf("StackIsFull on full stack :" GREEN "SUCCESS\n" RESET);
	}
	else
	{
		printf("StackIsFull on full stack:" RED "FAILURE\n" RESET);
	}

	StackDestroy(stack_handle);

    printf("============================================================\n\n");
}

/*============================================================================*/
/*                                               UnitTestStackPop */
static void UnitTestStackPop(void)
{
	stack_t *stack_handle = StackCreate(ELEMENT_SIZE, STACK_CAPACITY);
	int source[5] = {8, 2, 3, 4, 5};
	size_t i = 0;
	printf("====================== UnitTestStackPop ====================\n");    
        
	puts("Push 5 numbers to the stack");

	for (i = 0; i < STACK_CAPACITY; ++i)
	{
		StackPush(stack_handle, &source[i]);

		printf("%d ", *(int*)StackPeek(stack_handle));
	}
	
	puts("");

	/* pop some of the elements from the stack */
	puts("Pop some of the elements");
	for (i = 0; i < STACK_CAPACITY -2; ++i)
	{
		StackPop(stack_handle);
	}

	if (2 == StackSize(stack_handle))
	{
		printf("StackSize on partly full stack :" GREEN "SUCCESS\n" RESET);
	}
	else
	{
		printf("StackSize on partly full stack:" RED "FAILURE\n" RESET);
	}
	
	if (0 == StackIsEmpty(stack_handle))
	{
		printf("StackIsEmpty on partly full stack:" GREEN "SUCCESS\n" RESET);
	}
	else
	{
		printf("StackIsEmpty on partly full stack:" RED "FAILURE\n" RESET);
	}

	if (0 == StackIsFull(stack_handle))
	{
		printf("StackIsFull on partly full stack :" GREEN "SUCCESS\n" RESET);
	}
	else
	{
		printf("StackIsFull on partly full stack:" RED "FAILURE\n" RESET);
	}

	/* pop the rest of the elements and try to pop after stack is empty */
	puts("");
	puts("Pop the remaining elements and try to pop when stack is empty ");
	for (i = 0; i < STACK_CAPACITY; ++i)
	{
		StackPop(stack_handle);
	}

	if (0 == StackSize(stack_handle))
	{
		printf("StackSize on fully popped out stack :" GREEN "SUCCESS\n" RESET);
	}
	else
	{
		printf("StackSize on fully popped out stack:" RED "FAILURE\n" RESET);
	}
	
	if (1 == StackIsEmpty(stack_handle))
	{
		printf("StackIsEmpty on fully popped out stack:"
		        GREEN "SUCCESS\n" RESET);
	}
	else
	{
		printf("StackIsEmpty on fully popped out stack:" RED "FAILURE\n" RESET);
	}

	if (0 == StackIsFull(stack_handle))
	{
		printf("StackIsFull on fully popped out stack :" 
		       GREEN "SUCCESS\n" RESET);
	}
	else
	{
		printf("StackIsFull on fully popped out stack:" RED "FAILURE\n" RESET);
	}

	StackDestroy(stack_handle);

    printf("============================================================\n\n");
}
