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
* Last update: 29.10.19
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


void AllOn(uint64_t *bit_array);
/*
 * Turn on all bits in  bit_array 
 */


void AllOff(uint64_t *bit_array);
/*
 * Turn off all bits in  bit_array  
 */


void SetOn(uint64_t *bit_array, size_t index);
/*
 * Set on a specific bit in bit_array 
 */


void SetOff(uint64_t *bit_array, size_t index);
/*
 * Set off a specific bit in bit_array 
 */


void SetBit(uint64_t *bit_array, size_t index, char value);
/*
 * Set bit at specifed index to be on or off
 */


bool_t IsOn(uint64_t *bit_array, size_t index);
/*
 * Return TRUE if bit at specifed index is set and FALSE if not. 
 */


bool_t IsOff(uint64_t *bit_array, size_t index);
/*
 * Return TRUE if bit at specifed index is not set and FALSE if it is.
 */


void FlipBit(uint64_t *bit_array, size_t index);
/*
 * Switch status of a bit (1 -> 0 amd 0 -> 1) at specifed index  
 */
 

void RotateLeft(uint64_t *bit_array, size_t offset);
/*
 * Rotate bit_array  left, n times
 */


void RotateRight(uint64_t *bit_array, size_t offset);
/*
 * Rotate bit_array right, n times
 */


void Mirror(uint64_t *bit_array);
/*
 * Mirror bit_array
 */


size_t CountOn(uint64_t bit_array);
/*
 * Return number of set bits in bit_array
 */


size_t CountOff(uint64_t bit_array);
/*
 * Return number of unset bits in bit_array
 */

#endif /* _BIT_ARRAY_ */
