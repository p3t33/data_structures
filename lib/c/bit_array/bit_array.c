/*******************************************************************************
*                                 bit array
*                           =====================
* File Name: bit_array.c
* Related files: bit_array_test.h stack_test.h prep_lut.h
* #Version: V 1.1
* Writer: Kobi Medrish       
* Created: 26.10.19
* Last update: 26.11.19
*******************************************************************************/


/*============================================================================*/
/*                                  Definitions                               */
/*============================================================================*/
/*                                                      standard  directories */
/*                                                      ~~~~~~~~~~~~~~~~~~~~~ */
#include <stdio.h> /* used for printf */

/*============================================================================*/
/*                                                          local directories */
/*                                                          ~~~~~~~~~~~~~~~~~ */
#include "bit_array.h"
#include "lut.h" /* Used by MirrorBitLut and CountBitLut functions */


/*============================================================================*/
/*                                                                     Macros */
/*                                                                     ~~~~~~ */
#define WORDSIZE 64
 
/*============================================================================*/
/*                               API functions                                */
/*============================================================================*/
/*                                                                      AllOn */
/*                                                                      ~~~~~ */
size_t AllOn(size_t bit_array)
{
    size_t all_bits_on = ~ 0;
    
    bit_array = bit_array | all_bits_on;
    
    return bit_array;   
}

/*============================================================================*/
/*                                                                     AllOff */
/*                                                                     ~~~~~~ */
size_t AllOff(size_t bit_array)
{
    size_t all_bits_off = 0;
    
    bit_array = bit_array & all_bits_off;
    
    return bit_array;
}

/*============================================================================*/
/*                                                                      SetOn */
/*                                                                      ~~~~~ */
size_t SetOn(size_t bit_array, size_t index)
{
    size_t temp_bit_index = 1;
    
    temp_bit_index <<= index;
    
    bit_array = bit_array | temp_bit_index;
    
    return bit_array;        
}

/*============================================================================*/
/*                                                                     SetOff */
/*                                                                     ~~~~~~ */
size_t SetOff(size_t bit_array, size_t index)
{
    size_t temp_bit_index = 1;
    
    temp_bit_index <<= index;
    temp_bit_index = ~temp_bit_index;
    
    bit_array = bit_array & temp_bit_index;  
    
    return bit_array;     
}

/*============================================================================*/
/*                                                                     SetBit */
/*                                                                     ~~~~~~ */
size_t SetBit(size_t bit_array, size_t index, char value)
{
    return((value) ? SetOn(bit_array,index) : SetOff(bit_array,index)); 
}

/*============================================================================*/
/*                                                                       IsOn */
/*                                                                       ~~~~ */
bool_t IsOn(size_t bit_array, size_t index)
{
    size_t temp_bit_index = 1;
    
    temp_bit_index <<= index;
    
    return((bit_array & temp_bit_index) ? TRUE : FALSE);
}

/*============================================================================*/
/*                                                                      IsOff */
/*                                                                      ~~~~~ */
bool_t IsOff(size_t bit_array, size_t index)
{
    size_t temp_bit_index = 1;
    
    temp_bit_index <<= index;
    
    return((bit_array & temp_bit_index) ? FALSE : TRUE); 
}

/*============================================================================*/
/*                                                                    FlipBit */
/*                                                                    ~~~~~~~ */
size_t FlipBit(size_t bit_array, size_t index)
{
    size_t temp_bit_index = 1;
    
    temp_bit_index <<= index;
    
    bit_array = bit_array ^ temp_bit_index;
    
    return (bit_array);
}

/*============================================================================*/
/*                                                                 RotateLeft */
/*                                                                 ~~~~~~~~~~ */
size_t RotateLeft(size_t bit_array, size_t offset)
{
    return((bit_array << offset)|(bit_array >> ((WORDSIZE - offset))));
}

/*============================================================================*/
/*                                                                RotateRight */
/*                                                                ~~~~~~~~~~~ */
size_t RotateRight(size_t bit_array, size_t offset)
{
    return((bit_array >> offset)|(bit_array << ((WORDSIZE - offset)))); 
}

/*============================================================================*/
/*                                                                     Mirror */
/*                                                                     ~~~~~~ */
size_t Mirror(size_t bit_array)
{
    unsigned int count = WORDSIZE;
    size_t out_number = 0;

    /* Mirroes a number bit by bit and after the loop "pushes" it the the
       right place using what is left of count variable */
    while (bit_array)
    {   
        out_number <<= 1;
        
        out_number |= bit_array & 1;
        
        bit_array >>=1;
        
        --count;
    }
    
    out_number <<= count;
   
    return out_number;
}

/*============================================================================*/
/*                                                                    CountOn */
/*                                                                    ~~~~~~~ */
size_t CountOn(size_t bit_array)
{ 
    unsigned int bit_counter = 0;
  
    while (bit_array)
    {
        bit_counter += (bit_array & 1);
        bit_array >>= 1;
    }
    
    return bit_counter;
}

/*============================================================================*/
/*                                                                   CountOff */
/*                                                                   ~~~~~~~~ */
size_t CountOff(size_t bit_array)
{
    unsigned int bit_counter = 0;
    bit_array = ~bit_array;
  
    while (bit_array)
    {
        bit_counter += (bit_array & 1);
        bit_array >>= 1;
    }
    
    return bit_counter;
}


/*============================================================================*/
/*                                                                CountBitLut */
/*                                                                ~~~~~~~~~~~ */
size_t CountBitLut(size_t bit_array)
{
    unsigned char temp_one_byte = 0;
    size_t i = 0;
    size_t set_bit_counter = 0;
    
    for (i = 0; i < 8; ++i)
    {
        temp_one_byte = (unsigned char)bit_array;
        set_bit_counter += count_array[temp_one_byte];
        
        bit_array >>= 8;   
    }
    
    return (set_bit_counter); 
}

/*============================================================================*/
/*                                                               MirrorBitLut */
/*                                                               ~~~~~~~~~~~~ */
size_t MirrorBitLut(size_t bit_array)
{
    unsigned char temp_one_byte = 0;
    size_t mirrored_number = 0;
    size_t i = 0;
    
    for (i = 0; i < 8; ++i)
    {
        temp_one_byte = (unsigned char)bit_array;
        temp_one_byte = mirror_arr[temp_one_byte];
        
        mirrored_number <<= 8; 
        mirrored_number = mirrored_number | (size_t)temp_one_byte;
        bit_array >>= 8;                 
    }
    
    return(mirrored_number);       
}
