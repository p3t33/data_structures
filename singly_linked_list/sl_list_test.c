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

#include <stdio.h> /* Used for printf , scanf */
#include <stdlib.h> /* For system function */
#include <assert.h> /* Used for assert */
#include "sl_list.h" /* Used to include custom functions */



/*User functions */
int UserAdd(void *data, void* param);
int UserMatch(void *data, void* param);

int main()
{
    return 0;
}




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