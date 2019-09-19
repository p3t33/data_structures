#ifndef _SL_LIST_
#define _SL_LIST_
/*******************************************************************************
*                     singly linked list
*                   =====================
* File Name: sl_list.h
* Related files: sl_list.c sl_list_test.c
* #Version: V 1.0
* Writer: Kobi Medrish       
* Created: 19.9.19
* Last update: 19.9.19
*******************************************************************************/

#include <stddef.h> /* size_t */

/*
 * A singly linked list is a data structure consisting of a group of nodes,
 * linked together. Each node consists of data elements and a link
 * to the next node. The main advantage of linked lists over simple arrays 
 * is that the nodes can be inserted anywhere in the list without reallocating
 * the entire array because the nodes in a linked list do not need to be stored
 * contiguously in memory. However, nodes in the list cannot be accessed by 
 * index and instead must be accessed by traversing the list.
 * 
 * note that last node of the list cannot be removed
*/  

/* forward declarations */
typedef int (action_function_t)(void *data, void* param);
typedef int (is_match_function_t)(void *data, void* param);

typedef struct sl_node
{
	void *data;
	struct sl_node *next; 
}sl_node_t;


sl_node_t *SLLCreate(void *data, sl_node_t *next);
/* Create a node. May connect new node to other existing nodes.
 *
 * Params:
 *		  next - Pointer to the node that will be pointed by the created node.
 *				 (NULL if node does not point to any other node).
 *		  data - Pointer to the data that will be inserted to the node.
 * Return Value: 
 *		  pointer to the created node. 
 */


void SLLDestroy(sl_node_t *node);	  
/*
 * Destroy linked list by frying allocated memory 
 * Params: 
 *		  node - Reference node to the list to destory
 *
 * Time complexity: O(n).
 */


sl_node_t *SLLInsert(sl_node_t *node_to_insert, sl_node_t *node_location);
/* Insert a node before a given location.
 * Params: 
 *		  node_to_insert - Pointer to desired node to be inserted. 
 *		  node_location - Pointer to a node which will be pointed by the node to
 *                        be inserted.
 * Return value : 
 *        Pointer to inserted node
 * Time complexity: O(1)
 */


sl_node_t *SLLInsertAfter(sl_node_t *node_to_insert, sl_node_t *node_location);
/* Insert a node after a given location.
 * Params: 
 *		  node_to_insert - Pointer to desired node to be inserted.
 *		  node_location - Pointer to a node which will be pointing to the node
 *                        to be inserted 
 * Return value : 
 *        pointer to inserted node. 
 * Time complexity: O(1)
 */


sl_node_t *SLLRemove(sl_node_t *node_to_remove);
/* Remove a node from a given location. Cannot remove the last node from a list.
 * Params: 
 *		  node_to_remove - the node to be removed from the list.
 * Return value : A pointer to the removed node.
 * Time complexity: O(1)
 */


sl_node_t *SLLRemoveAfter(sl_node_t *location);
/* Remove a node from the list after a given location.
 * Params: 
 *		  location - Pointer to a nodes which points to the node to be removed.
 * Return value : 
 *		  A pointer to the removed node. 
 * Time complexity: O(1)
 */


int SLLForEach(sl_node_t *node, action_function_t func, void *param);
/* Apply <action_func> for all nodes starting from <node>.
 * Params: 
 *		  node - reference node.
 *
 * Return value : 
 *       0-(success), 1-(failure).
 * Time complexity: O(n)
 */

/*TODO: params */
sl_node_t *SLLFind(sl_node_t *node, is_match_function_t func, void *param);
/* checks if a certain data matches a data on the list.
 * Params: 
 *		  node - data to be evaluated.
 *		  data - the data to be matched.	
 * Return value : 
 *		  pointer to node that holds relevant data.
 * Time complexity: O(n)
 */


size_t SLLCount(const sl_node_t *node);
/* Count the number of nodes on the list, from a reference node.
 * Params: 
 *		  node - reference node.
 * Return value : 
 *		  number of nodes on the list.
 * Time complexity: O(n)
 */


sl_node_t *SLLFlip(sl_node_t *node);
/* Reverse the direction of the singly linked list.
 * Params: 
 *		  node - reference node.
 * Return value : 
 *		  a pointer to the new first node of the list.
 * Time complexity: O(n)
 */


sl_node_t *SLLFindIntersection(const sl_node_t *list_1, 
       						   const sl_node_t *list_2);
/* Find intersections - a shared node between two lists.
 * Params: 
 *		  node_1 - reference node of first list.
 * 		  node_2 - reference node of second list.
 * Time complexity: O(n).
 * Return value : a pointer to the shared node.
 * Time complexity: O(n)
 */


sl_node_t *SLLIsListHasLoop(sl_node_t *node);
/* Finds if a loop exists within the list.
 * Params: 
 *		  node  - pointer to the list.
 * Return value : Pointer to a node in the loop if loop is found, NULL if no 
 *                loop is found
 * Time complexity: O(n)
 */

void SLLRemoveLoop(sl_node_t *node);
/* If loop exists within the list it will be opened.
 * Params: 
 *		  node - pointer to the list.
 * Time complexity: O(n)
 */

#endif /* _SL_LIST_ */