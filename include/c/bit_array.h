

#ifndef _BIT_ARRAY_
#define _BIT_ARRAY_
/*******************************************************************************
*                     bit array
*              =====================
* File Name: bit_array.h
* Related files: bit_array_test.h stack_test.c
* #Version: V 1.0
* Writer: Kobi Medrish       
* Created: 26.10.19
* Last update: 26.11.19
*******************************************************************************/

/*
 * A bit array (also known as bit map, bit set, bit string, or bit vector) is
 * an array data structure that compactly stores bits. In this implementation
 * I used a single size_t variable which represents an array of 64 bits.
 * 
 * As an extention, API functions CountBitLut and MirrorBitLut use a lut to
 * do the same calculations done by API functions CountOn and Mirror. the LUT
 * is prepared by running the binary compiled from auxiliary file
 * prep_lut.c 
 */

/*============================================================================*/
/*                                  Definitions                               */
/*============================================================================*/
/*                                                      standard  directories */
/*                                                      ~~~~~~~~~~~~~~~~~~~~~ */
#include <stddef.h> /* size_t */
#include <stdint.h> /* size_t */

#ifdef __cplusplus
extern "C"
{
#endif
/*============================================================================*/
/*                                                                      enums */
/*                                                                      ~~~~~ */
typedef enum BOOL {FALSE, TRUE} bool_t; /* std=98 compliant */

/*============================================================================*/


size_t AllOn(size_t bit_array);
/*
 * Turn on all bits in  bit_array 
 */


size_t AllOff(size_t bit_array);
/*
 * Turn off all bits in  bit_array  
 */


size_t SetOn(size_t bit_array, size_t index);
/*
 * Set on a specific bit in bit_array 
 */


size_t SetOff(size_t bit_array, size_t index);
/*
 * Set off a specific bit in bit_array 
 */


size_t SetBit(size_t bit_array, size_t index, char value);
/*
 * Set bit at specifed index to be on or off
 */


bool_t IsOn(size_t bit_array, size_t index);
/*
 * Return TRUE if bit at specifed index is set and FALSE if not. 
 */


bool_t IsOff(size_t bit_array, size_t index);
/*
 * Return TRUE if bit at specifed index is not set and FALSE if it is.
 */


size_t FlipBit(size_t bit_array, size_t index);
/*
 * Switch status of a bit (1 -> 0 amd 0 -> 1) at specifed index  
 */
 

size_t RotateLeft(size_t bit_array, size_t offset);
/*
 * Rotate bit_array  left, n times
 */


size_t RotateRight(size_t bit_array, size_t offset);
/*
 * Rotate bit_array right, n times
 */


size_t Mirror(size_t bit_array);
/*
 * Mirror bit_array
 */


size_t CountOn(size_t bit_array);
/*
 * Return number of set bits in bit_array
 */


size_t CountOff(size_t bit_array);
/*
 * Return number of unset bits in bit_array
 */


size_t CountBitLut(size_t bit_array);
/*
 * Return number of set bits in bit_array using a lut
 */

size_t MirrorBitLut(size_t bit_array);
/*
 * Mirror bit_array using a lut
 */
#ifdef __cplusplus
}
#endif

#endif /* _BIT_ARRAY_ */


