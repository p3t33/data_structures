#ifndef _BIT_ARRAY_
#define _BIT_ARRAY_
/*******************************************************************************
*                     bit array
*              =====================
* File Name: bit_array.h
* Related files: bit_array_test.h stack_test.c
* #Version: V 1.0
* Writer: Kobi Medrish       
* Created: 24.10.19
* Last update: 24.10.19
*******************************************************************************/


/*============================================================================*/
/*                                  Definitions                               */
/*============================================================================*/
/*                                                      standard  directories */
/*                                                      ~~~~~~~~~~~~~~~~~~~~~ */
#include <stddef.h> /* size_t */
#include <stdint.h> /* uint64_t */

/*============================================================================*/
/*                                                                      enums */
/*                                                                      ~~~~~ */
typedef enum BOOL {FALSE, TRUE} bool_t; /* std=98 compliant */

/*============================================================================*/


uint64_t AllOn(uint64_t *bit_array);
/*
 * turn on all bits in  bit_array 
 */

uint64_t AllOff(uint64_t *bit_array);
/*
 * turn off all bits in  bit_array  
 */

/* set on/off a specific bit <index> in bit array */
uint64_t SetOn(uint64_t *bit_array, size_t index);
/*
 * set on a specific bit in bit_array 
 */

uint64_t SetOff(uint64_t *bit_array, size_t index);
/*
 * set off a specific bit in bit_array 
 */

/* set bit <#index> to status <value> */
uint64_t SetBit(uint64_t *bit_array, size_t index, char value);

/* return TRUE / FALSE according to bit <#index> status */
bool_t IsOn(uint64_t *bit_array, size_t index);
bool_t IsOff(uint64_t *bit_array, size_t index);

/* switch status of bit <#index> */
uint64_t FlipBit(uint64_t *bit_array, size_t index);

/* rotate <bit_array> left/right, n times */ 
uint64_t RotateLeft(uint64_t *bit_array, size_t offset);
uint64_t RotateRight(uint64_t *bit_array, size_t offset);

/* mirror <bit_array> */
uint64_t Mirror(uint64_t *bit_array);

/* return number of bit on/off in <bit_array> */
size_t CountOn(uint64_t *bit_array);
size_t CountOff(uint64_t *bit_array);

#endif /* _BIT_ARRAY_ */

