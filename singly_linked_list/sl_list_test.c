/*******************************************************************************
*                     singly linked list
*                   =====================
* File Name: sl_list_test
* Related files: sl_list.c sl_list.h
* #Version: V 1.0
* Writer: Kobi Medrish       
* Created: 19.9.19
* Last update: 19.9.19
*******************************************************************************/

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

#include"sl_list.h"
/*============================================================================*/
/*                                                                     Macros */
/*                                                                     ~~~~~~ */


/*============================================================================*/
/*                                                                      enums */
/*                                                                      ~~~~~ */

/*                                                                     Colors */
/*                                                                     ~~~~~~ */
#define GREEN "\033[1;32m"
#define RED "\033[0;31m"
#define YELLOW "\033[1;33m"
#define RESET "\033[0m"
/*============================================================================*/
/*                                                                    structs */
/*                                                                    ~~~~~~~ */
 
/*============================================================================*/
/*                             function declarations                          */
/*                             ~~~~~~~~~~~~~~~~~~~~~                          */
/*                                                                 Unit tests */
/*                                                                 ~~~~~~~~~~ */
static void UnitTestSLLCreate(void);
static void UnitTestSLLDestroy(void);
static void UnitTestSLLInsert(void);
static void UnitTestSLLInsertAfter(void);
static void UnitTestSLLRemove(void);
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
int UserAdd(void *data, void* param);
int UserMatch(void *data, void* param);
void PrintList(sl_node_t *sl_handle);
/*============================================================================*/

int main()
{
    UnitTestSLLCreate();
    UnitTestSLLDestroy();
    UnitTestSLLInsert();
    UnitTestSLLInsertAfter();
    UnitTestSLLRemove();
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
/*                                               UnitTestSLLCreate                    */

static void UnitTestSLLCreate(void)
{
    size_t src_data = 5;
    sl_node_t *sl_handle = NULL;

    printf("======================== UnitTestSLLCreate ======================\n");    

    
    /* node is created and data is passed to it*/
    sl_handle = SLLCreate(&src_data, NULL);
    
    /* src data is evaluated to match the data at the node */ 
    if (*(size_t*)sl_handle->data == src_data)
    {
        printf("SLLCreate created node with data " GREEN "SUCCESS\n" RESET);
    }
    else
    {
        printf("node SLLCreate with data " RED "FAILURE\n" RESET);
    }

    if (1 == SLLCount(sl_handle))
    {
        printf("SLLCount with one node " GREEN "SUCCESS\n" RESET);        
    }
    else
    {
        printf("SLLCount with one node " RED "FAILURE\n" RESET);    
    }
    
    SLLDestroy(sl_handle); 

    printf("=============================================================\n\n");
}

/*============================================================================*/
/*                                               UnitTestSLLDestroy */
static void UnitTestSLLDestroy(void)
{
    size_t src_data[3] ={1,2,3}, i = 0;
    sl_node_t *sl_handle[3] = {NULL};

    printf("======================== UnitTestSLLDestroy ======================\n");    

    /* One node created and destroyed it - tested with valgrind */
    sl_handle[0] = SLLCreate(&src_data[0], NULL);

    /*printf("%lu\n",*(size_t*)sl_handle[0]->data);*/
    SLLDestroy(sl_handle[0]);

    /* Multiple nodes created and destroyed - tested with valgrind */
    sl_handle[0] = SLLCreate(&src_data[0], NULL); 
    for (i = 1; i < 3; ++i)
    {
        sl_handle[i] = SLLCreate(&src_data[i], sl_handle[i-1]); 
    }

    PrintList(sl_handle[2]);

    if (3 == SLLCount(sl_handle[2]))
    {
        printf("SLLCount with 3 node " GREEN "SUCCESS\n" RESET);        
    }
    else
    {
        printf("SLLCount with 3 node " RED "FAILURE\n" RESET);    
    }

    SLLDestroy(sl_handle[2]);

    printf("=============================================================\n\n");
}

/*============================================================================*/
/*                                               UnitTestSLLInsert */
static void UnitTestSLLInsert(void)
{
    size_t src_data[3] = {1,2,8}, i = 0;
    sl_node_t *sl_handle[2] = {NULL}, *insert_node = NULL;

    printf("======================== UnitTestSLLInsert ======================\n");    
    

    /* Node to be inserted created with <8> as data*/
    insert_node = SLLCreate(&src_data[2], NULL);
    

    /* Chain of 2 nodes is created  <1-2> */
    sl_handle[0] = SLLCreate(&src_data[0], NULL); 
    for (i = 1; i < 2; ++i)
    {
        sl_handle[i] = SLLCreate(&src_data[i], sl_handle[i-1]); 
    }
    PrintList(sl_handle[1]);

 
    /* node inserted  between <1-2> and new list should be <1-8-2> */
    SLLInsert(insert_node, sl_handle[0]);
    puts("After the insert");
    PrintList(sl_handle[1]);


    /* malloc freed */
    SLLDestroy(sl_handle[1]);

    printf("=============================================================\n\n");
}

/*============================================================================*/
/*                                               UnitTestSLLInsertAfter */
static void UnitTestSLLInsertAfter(void)
{
    size_t src_data[3] = {1,2,8}, i = 0;

    sl_node_t *sl_handle[2] = {NULL}, *insert_node = NULL;
    printf("======================== UnitTestSLLInsertAfter ======================\n");    
  

    /* Node to be inserted created */
    insert_node = SLLCreate(&src_data[2],NULL);

    /* Chain of nodes created */
    sl_handle[0] = SLLCreate(&src_data[0],NULL); 
    for (i = 1; i < 2; ++i)
    {
        sl_handle[i] = SLLCreate(&src_data[i],sl_handle[i-1]); 
    }

    PrintList(sl_handle[1]);

    SLLInsertAfter(insert_node, sl_handle[0]);

    PrintList(sl_handle[1]);
    
    SLLDestroy(sl_handle[1]);

    printf("=============================================================\n\n");
}

/*============================================================================*/
/*                                               UnitTestSLLRemove */
static void UnitTestSLLRemove(void)
{
    size_t src_data[3] = {1,2,3}, i = 0;


    sl_node_t *sl_handle[3] = {NULL}, *runner = NULL, *temp = NULL;
    printf("======================== UnitTestSLLRemove ======================\n");    


    sl_handle[0] = SLLCreate(&src_data[0],NULL); 
    for (i = 1; i < 3; ++i)
    {
        sl_handle[i] = SLLCreate(&src_data[i],sl_handle[i-1]); 
    } 

    PrintList(sl_handle[2]);

    temp = SLLRemove(sl_handle[1]); /* temp is used to free the removed node */
    PrintList(sl_handle[1]);


/*     if (2 == *(size_t*)(temp->data))
    {
        printf("SLLRemove " GREEN "SUCCESS\n" RESET);        
    }
    else
    {
        printf("SLLRemove " RED "FAILURE\n" RESET);    
    } */

    SLLDestroy(sl_handle[2]);

    SLLDestroy(sl_handle[2]);
    SLLDestroy(temp);

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
int UserAdd(void *data, void* param)
{
    if (data == NULL || param == NULL)
    {
        return (1);
    }
    *(size_t*)data += *(size_t*)param;

    return(0);
}


int UserMatch(void *data, void* param)
{

	assert(data);
	assert(param);
	return(*(size_t*)data == *(size_t*)param);
}

void PrintList(sl_node_t *sl_handle)
{
    puts("printout of the list, from last to first");

    while (NULL != sl_handle)
    {
        printf("%lu", *(size_t*)(sl_handle->data));
        sl_handle = sl_handle->next;

    }

    puts("");
}
