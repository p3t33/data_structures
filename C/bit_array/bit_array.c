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
#include "prep_lut.h" /* Used to include improved Nirror and count functions */

/*============================================================================*/
/*                                                                     Macros */
/*                                                                     ~~~~~~ */
#define WORDSIZE 64
 
/*============================================================================*/
/*                               API functions                                */
/*============================================================================*/
/*                                                                      AllOn */
/*                                                                      ~~~~~ */
uint64_t AllOn(uint64_t bit_array)
{
    uint64_t all_bits_on = ~ 0;
    
    bit_array = bit_array | all_bits_on;
    
    return bit_array;   
}

/*============================================================================*/
/*                                                                     AllOff */
/*                                                                     ~~~~~~ */
uint64_t AllOff(uint64_t bit_array)
{
    uint64_t all_bits_off = 0;
    
    bit_array = bit_array & all_bits_off;
    
    return bit_array;
}

/*============================================================================*/
/*                                                                      SetOn */
/*                                                                      ~~~~~ */
uint64_t SetOn(uint64_t bit_array, size_t index)
{
    uint64_t temp_bit_index = 1;
    
    temp_bit_index <<= index;
    
    bit_array = bit_array | temp_bit_index;
    
    return bit_array;        
}

/*============================================================================*/
/*                                                                     SetOff */
/*                                                                     ~~~~~~ */
uint64_t SetOff(uint64_t bit_array, size_t index)
{
    uint64_t temp_bit_index = 1;
    
    temp_bit_index <<= index;
    temp_bit_index = ~temp_bit_index;
    
    bit_array = bit_array & temp_bit_index;  
    
    return bit_array;     
}

/*============================================================================*/
/*                                                                     SetBit */
/*                                                                     ~~~~~~ */
uint64_t SetBit(uint64_t bit_array, size_t index, char value)
{
    return((value) ? SetOn(bit_array,index) : SetOff(bit_array,index)); 
}

/*============================================================================*/
/*                                                                       IsOn */
/*                                                                       ~~~~ */
bool_t IsOn(uint64_t bit_array, size_t index)
{
    uint64_t temp_bit_index = 1;
    
    temp_bit_index <<= index;
    
    return((bit_array & temp_bit_index) ? TRUE : FALSE);
}

/*============================================================================*/
/*                                                                      IsOff */
/*                                                                      ~~~~~ */
bool_t IsOff(uint64_t bit_array, size_t index)
{
    uint64_t temp_bit_index = 1;
    
    temp_bit_index <<= index;
    
    return((bit_array & temp_bit_index) ? FALSE : TRUE); 
        
}

/*============================================================================*/
/*                                                                    FlipBit */
/*                                                                    ~~~~~~~ */
uint64_t FlipBit(uint64_t bit_array, size_t index)
{
    uint64_t temp_bit_index = 1;
    
    temp_bit_index <<= index;
    
    bit_array = bit_array ^ temp_bit_index;
    
    return (bit_array);
}

/*============================================================================*/
/*                                                                 RotateLeft */
/*                                                                 ~~~~~~~~~~ */
uint64_t RotateLeft(uint64_t bit_array, size_t offset)
{
    return((bit_array << offset)|(bit_array >> ((WORDSIZE - offset))));
}

/*============================================================================*/
/*                                                                RotateRight */
/*                                                                ~~~~~~~~~~~ */
uint64_t RotateRight(uint64_t bit_array, size_t offset)
{
    return((bit_array >> offset)|(bit_array << ((WORDSIZE - offset)))); 
}

/*============================================================================*/
/*                                                                     Mirror */
/*                                                                     ~~~~~~ */
uint64_t Mirror(uint64_t bit_array)
{
    unsigned int count = WORDSIZE;
    uint64_t out_number = 0;

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
size_t CountOn(uint64_t bit_array)
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
size_t CountOff(uint64_t bit_array)
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
size_t CountBitLut(uint64_t bit_array)
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
uint64_t MirrorBitLut(uint64_t bit_array)
{
    unsigned char temp_one_byte = 0;
    uint64_t mirrored_number = 0;
    size_t i = 0;
    
    for (i = 0; i < 8; ++i)
    {
        temp_one_byte = (unsigned char)bit_array;
        temp_one_byte = mirror_arr[temp_one_byte];
        
        mirrored_number <<= 8; 
        mirrored_number = mirrored_number | (uint64_t)temp_one_byte;
        bit_array >>= 8;                 
    }
    
    return(mirrored_number);       
}
