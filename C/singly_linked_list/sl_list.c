/*******************************************************************************
*                     singly linked list
*                   =====================
* File Name: sl_list.c
* Related files: sl_list.h stack_test.c
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
#include <stdlib.h> /* malloc, realloc */
#include <assert.h> /* assert */
#include <stdio.h> /* printf */

/*============================================================================*/
/*                                                          local directories */
/*                                                          ~~~~~~~~~~~~~~~~~ */
#include "sl_list.h" 

/*============================================================================*/
/*                                                                     Macros */
/*                                                                     ~~~~~~ */
#define END_OF_CHAIN (NULL) /* SLLCreate */
#define MALLOC_FAIL (NULL)
#define MATCH (1) /* SLLFind */
#define NO_MATCH (NULL) /* SLLFind */
#define NO_LOOP (NULL) /* SLLHasLoop */
#define HAS_LOOP (NULL) /* SLLOpenLoop */
 
/*============================================================================*/
/*                                                                      enums */
/*                                                                      ~~~~~ */
enum status {SUCCESS, FAILURE};


/*============================================================================*/
/*                         ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~                      */
/*                         Forward function declaration                       */
/*                         ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~                      */

/*                                                                  SLLInsert */
/*                                                                  ~~~~~~~~~ */
static void SwapData(sl_node_t *node_one, sl_node_t *node_two);
/*                                                        SLLFindIntersection */
/*                                                        ~~~~~~~~~~~~~~~~~~~ */
static const sl_node_t *AlignList(const sl_node_t *list,
                                  size_t length_difference);
/*                                                                SLLOpenLoop */
/*                                                                ~~~~~~~~~~~ */
static size_t SizeOfLoop(sl_node_t *reference);
static void OpenLoop(sl_node_t *list, size_t loop_size);

/*============================================================================*/
/*                               API functions                                */
/*============================================================================*/
/*                                                                  SLLCreate */
/*                                                                  ~~~~~~~~~ */
sl_node_t *SLLCreate(void *data, sl_node_t *next)
{
    /* node is created */
    sl_node_t *node = (sl_node_t*)malloc(sizeof(sl_node_t));
    if (MALLOC_FAIL == node)
    {
        return(MALLOC_FAIL);
    }

    /*node variables set */
    node->data = data;
    node->next = next;
       
    return (node);
}

/*============================================================================*/
/*                                                                 SLLDestroy */
/*                                                                 ~~~~~~~~~~ */
void SLLDestroy(sl_node_t *node)
{
  
    /* Entire chain of nodes is traversed and destroyed */
    while (END_OF_CHAIN != node)
    {
        sl_node_t *temp = node;
        node = node->next;
        free(temp);
    }
}

/*============================================================================*/
/*                                                                  SLLInsert */
/*                                                                  ~~~~~~~~~ */
sl_node_t *SLLInsert(sl_node_t *node_to_insert, sl_node_t *node_location)
{
    assert(node_to_insert);
    assert(node_location);

    /* insert node_to_insert after node_location*/
    SLLInsertAfter(node_to_insert, node_location); 

    /* swap data between node_to_insert and node_location*/
    SwapData(node_to_insert, node_location);
    
    return (node_location);
}

/*============================================================================*/
/*                                                             SLLInsertAfter */
/*                                                             ~~~~~~~~~~~~~~ */
sl_node_t *SLLInsertAfter(sl_node_t *node_to_insert, sl_node_t *node_location)
{
    assert(node_to_insert);
    assert(node_location);

    /* same as SLLInsert but without the data swap */
    node_to_insert->next = node_location->next;
    node_location->next = node_to_insert; 

    return(node_to_insert);
}

/*============================================================================*/
/*                                                                  SLLRemove */
/*                                                                  ~~~~~~~~~ */
sl_node_t *SLLRemove(sl_node_t *node_to_remove)
{   
    sl_node_t *adjacent_node = NULL;

    assert(node_to_remove);
    assert(node_to_remove->next);

    /* adjacent_node is detached from the list */
    adjacent_node = SLLRemoveAfter(node_to_remove);
    
    /* data is swapped between node_to_remove and the detached adjacent_node */
    SwapData(adjacent_node, node_to_remove);

    return(adjacent_node);
}

/*--------------------------------------------------------------------------- */
/*                      Auxiliary functions for FUnctionA                     */
/*--------------------------------------------------------------------------- */
/*                                                                   SwapData */
/*                                                                  ~~~~~~~~~ */
void SwapData(sl_node_t *node_one, sl_node_t *node_two)
{
    void *temp = NULL;
    assert(node_one);
    assert(node_two);

    temp = node_one->data;
    node_one->data = node_two->data;
    node_two->data = temp;
}

/*============================================================================*/
/*                                                             SLLRemoveAfter */
/*                                                             ~~~~~~~~~~~~~~ */
sl_node_t *SLLRemoveAfter(sl_node_t *location)
{
    sl_node_t *removed_node = NULL;
    assert(location);

    removed_node = location->next;
    
   
    if (END_OF_CHAIN == location->next)
    {
        return(location);
    }

    /* location node is reattached to the node after the node to be removed
       and then the node to be removed is detached from the chain */  
    location->next = removed_node->next;
    removed_node->next = NULL;

    return (removed_node);
}

/*============================================================================*/
/*                                                                 SLLForEach */
/*                                                                 ~~~~~~~~~~ */
int SLLForEach(sl_node_t *node, action_function_t func, void *param)
{
    assert(node);
    assert(func);
    assert(param);

    /* user function is called to preform  user defined action upon the chian
       of nodes entire */
    while(END_OF_CHAIN != node)
    {
        if (FAILURE == func(node->data, param))
        {
            return (FAILURE); 
        }
        node = node->next;    
    }

    return (SUCCESS);
}

/*============================================================================*/
/*                                                                    SLLFind */
/*                                                                    ~~~~~~~ */

sl_node_t *SLLFind(sl_node_t *node, is_match_function_t func, void *param)
{
    assert(node);
    assert(func);
    assert(param);
    
   /* user function is called to preform user defined action upon the chian
      of nodes entire */
    while(END_OF_CHAIN != node)
    {
        if (MATCH == func(node->data, param))
        {
            return (node);
        } 

        node = node->next;   
    }

    return(NO_MATCH);
}

/*============================================================================*/
/*                                                                   SLLCount */
/*                                                                   ~~~~~~~~ */
size_t SLLCount(const sl_node_t *node)
{
    /* Entire chain is traversed and each node is counted */
    size_t node_counter = 0;
    assert(node);

    while (END_OF_CHAIN != node)
    {
        ++node_counter;
        node = node->next;
    }

    return(node_counter);
}

/*============================================================================*/
/*                                                                    SLLFlip */
/*                                                                    ~~~~~~~ */
sl_node_t *SLLFlip(sl_node_t *node)
{
    sl_node_t *prevues_node = NULL, *next_node = NULL, *current_node = NULL; 
    assert(node);

    current_node = node;

    /* The direction of the chain is flipped */
    while (END_OF_CHAIN != current_node)
    {
        next_node = current_node->next;
        current_node->next = prevues_node;

        prevues_node = current_node;
        current_node = next_node;
    }

    node = prevues_node;

    return (node);
}

/*============================================================================*/
/*                                                        SLLFindIntersection */
/*                                                        ~~~~~~~~~~~~~~~~~~~ */
sl_node_t *SLLFindIntersection(const sl_node_t *list_1, const sl_node_t *list_2)
{
    /* each cain length is counted */
    size_t list_length_1 = 0, list_length_2 = 0; 
    assert(list_1);
    assert(list_2);

    list_length_1 = SLLCount(list_1);
    list_length_2 = SLLCount(list_2);

    /* if list_1 is longer then list_2, it is traversed until they are the same
       length*/ 
    if (list_length_1 > list_length_2)
    {
        list_1 = AlignList(list_1, list_length_1 - list_length_2);
    }

    /* if list_2 is longer then list_1, it is traversed until they are the same
    length */ 
    else if (list_length_1 < list_length_2)
    {
        list_2 = AlignList(list_2, list_length_2 - list_length_1); 
    }

    /* Both chains are traversed for search of an intersection */ 
    while (END_OF_CHAIN != list_1 ||END_OF_CHAIN != list_2)
    {
        if (list_1->next == list_2->next)
        {
            return((sl_node_t*) list_1->next);
        }
        list_1 = list_1->next;
        list_2 = list_2->next;
    }

    return (NULL); 
}
/*--------------------------------------------------------------------------- */
/*                      Auxiliary functions for FUnctionA                     */
/*--------------------------------------------------------------------------- */
/*                                                                  AlignList */
/*                                                                  ~~~~~~~~~ */
static const sl_node_t *AlignList(const sl_node_t *list,
                                  size_t length_difference)
{
    while(length_difference)
    {
        list = list->next;
        --length_difference;
    } 

    return (list); 
}
/*============================================================================*/
/*                                                           SLLIsListHasLoop */
/*                                                           ~~~~~~~~~~~~~~~~ */
sl_node_t *SLLIsListHasLoop(sl_node_t *node)
{
    /*hare "moves" twice as fast as the tortoise and if there is a loop he will
     pass the tortoise */
	sl_node_t *tortoise = NULL, *hare = NULL;
    assert(node);

	if(node->next != NULL)
	{
		tortoise = node;
		hare = node->next;
	}
	else
	{
		return NO_LOOP;
	}

	while (END_OF_CHAIN != hare->next)
	{
		if(tortoise == hare)
		{
			return (tortoise);
		}

		tortoise = tortoise->next;
		hare = hare->next->next;
	}

	return NO_LOOP;
}

/*============================================================================*/
/*                                                              SLLRemoveLoop */
/*                                                              ~~~~~~~~~~~~~ */
void SLLRemoveLoop(sl_node_t *node)
{
    sl_node_t *reference = SLLIsListHasLoop(node);
    size_t size_of_loop = 0;
    
    assert(node);
    
    if (NO_LOOP == reference)
    {
        return;
    }

    size_of_loop = SizeOfLoop(reference);

    OpenLoop(node, size_of_loop);
}

/*--------------------------------------------------------------------------- */
/*                      Auxiliary functions for FUnctionA                     */
/*--------------------------------------------------------------------------- */
/*                                                                 SizeOfLoop */
/*                                                                 ~~~~~~~~~~ */
static size_t SizeOfLoop(sl_node_t *reference)
{
    sl_node_t *runner = reference->next;
    size_t loop_size = 0;

    assert(reference);
    
    while (runner->next != reference)
    {
        runner = runner->next;
        ++loop_size;
    }

    return (loop_size);
}

/*--------------------------------------------------------------------------- */
/*                                                                   OpenLoop */
/*                                                                   ~~~~~~~~ */
static void OpenLoop(sl_node_t *list, size_t loop_size)
{
    sl_node_t *runner_1 = list;
    sl_node_t *runner_2 = list;
    size_t i = 0;

    assert(list);

    for (i = 0; i < loop_size; ++i)
    {
        runner_1 = runner_1->next;
    }

    while (runner_1->next != runner_2)
    {
        runner_1 = runner_1->next;
        runner_2 = runner_2->next;
    }

    runner_1->next = NULL;
}
