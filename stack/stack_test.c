/****************************************************************
*                       Template for C test code
* 						========================
* File Name: template_test.c
* #Version: V 1.0.4
* Writer: Kobi Medrish       
* Created: 14.9.19
* Last update: 14.9.19
****************************************************************/


/*============================================================================*/
/*                                  Definitions                               */
/*============================================================================*/
/*                                                      standard  directories */
/*                                                      ~~~~~~~~~~~~~~~~~~~~~ */

#include <stdio.h> /* printf */
#include <assert.h> /* assert */

/*============================================================================*/
/*                                                          local directories */
/*                                                          ~~~~~~~~~~~~~~~~~ */

#include "stack.h"
/*============================================================================*/
/*                                                                     Macros */
/*                                                                     ~~~~~~ */
#define ELEMENT_SIZE sizeof(int)
#define STACK_CAPACITY (5)

#define GREEN "\033[1;32m"
#define RED "\033[1;32m"
#define YELLOW "\033[1;33m"
#define RESET "\033[0m"
/*============================================================================*/
/*                                                                      enums */
/*                                                                      ~~~~~ */


/*============================================================================*/
/*                                                                    structs */
/*                                                                    ~~~~~~~ */
 
/*============================================================================*/
/*                             function declarations                          */
/*                             ~~~~~~~~~~~~~~~~~~~~~                          */
/*                                                                 Unit tests */
/*                                                                 ~~~~~~~~~~ */
static void UnitTestStackCreate(void);
static void UnitTestStackPush(void);
static void UnitTestZ(void);
static void UnitTestK(void);
static void UnitTestM(void);
static void UnitTestA(void);
static void UnitTestB(void);
static void UnitTestC(void);
static void UnitTestD(void);
static void UnitTestE(void);

/*                                                           Integration Test */ 
/*                                                           ~~~~~~~~~~~~~~~~ */  
   
/*============================================================================*/
/*                                                              User function */
/*                                                              ~~~~~~~~~~~~~ */

/*============================================================================*/

int main()
{
    UnitTestStackCreate();
    UnitTestStackPush();
    UnitTestZ();
    UnitTestK();
    UnitTestM();
    UnitTestA();
    UnitTestB();
    UnitTestC();
    UnitTestD();
    UnitTestE();
  
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
	size_t size_of_Stack = 0;

    printf("===================== UnitTestStackCreate ==================\n");    
  
	if (NULL != stack_handle)
	{
		printf("Stack created:" GREEN "SUCCESS\n" RESET);
	}
	else
	{
		printf("Stack created:" RED "FAILURE\n" RESET);
	}

	size_of_Stack = StackSize(stack_handle);
	if (0 == size_of_Stack)
	{
		printf("Stack is empty:" GREEN "SUCCESS\n" RESET);
	}
	else
	{
		printf("Stack is empty:" RED "FAILURE\n" RESET);
	}
	

	StackDestroy(stack_handle);

    printf("=============================================================\n\n");
}

/*============================================================================*/
/*                                               UnitTestStackPush */
static void UnitTestStackPush(void)
{
	stack_t *stack_handle = StackCreate(ELEMENT_SIZE, STACK_CAPACITY);
	size_t size_of_Stack = 0;

	int source[5] = {8, 2, 3, 4, 5};
	size_t i = 0;
    printf("======================== UnitTestStackPush ======================\n");    
    
	for (i = 0; i < STACK_CAPACITY; ++i)
	{
		StackPush(stack_handle, &source[i]);

		printf("%d", *(int*)StackPeek(stack_handle));

		printf("\n");
	
	}
	

	if (1 == StackPush(stack_handle, &source[0]))
	{
		printf("stack is full\n");
	}








	StackDestroy(stack_handle);

    printf("=============================================================\n\n");
}

/*============================================================================*/
/*                                               UnitTestZ */
static void UnitTestZ(void)
{
    printf("======================== UnitTestZ ======================\n");    
   

    printf("=============================================================\n\n");
}

/*============================================================================*/
/*                                               UnitTestK */
static void UnitTestK(void)
{
    printf("======================== UnitTestK ======================\n");    
   

    printf("=============================================================\n\n");
}

/*============================================================================*/
/*                                               UnitTestM */
static void UnitTestM(void)
{
    printf("======================== UnitTestM ======================\n");    
   

    printf("=============================================================\n\n");
}

/*============================================================================*/
/*                                               UnitTestA */
static void UnitTestA(void)
{
    printf("======================== UnitTestA ======================\n");    
    

    printf("=============================================================\n\n");
}

/*============================================================================*/
/*                                               UnitTestB */
static void UnitTestB(void)
{
    printf("======================== UnitTestB ======================\n");    
    

    printf("=============================================================\n\n");
}

/*============================================================================*/
/*                                               UnitTestC */
static void UnitTestC(void)
{
    printf("======================== UnitTestC ======================\n");    
   

    printf("=============================================================\n\n");
}

/*============================================================================*/
/*                                               UnitTestD */
static void UnitTestD(void)
{
    printf("======================== UnitTestD ======================\n");    
   

    printf("=============================================================\n\n");
}

/*============================================================================*/
/*                                               UnitTestE */
static void UnitTestE(void)
{
    printf("======================== UnitTestE ======================\n");    
    

    printf("=============================================================\n\n");
}


/*============================================================================*/
/*                                   User function                            */             
/*============================================================================*/
/*                                                                            */


