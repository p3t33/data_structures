#include <stddef.h> /* size_t */
#include <stdint.h> /* uint64_t */
#include <assert.h>

#include "bit_array.h" /* Used to include custom functions */
#include "prep_lut.h" /* Used to include improved Nirror and count functions */

#define WORDSIZE 64

/*###################### turn on/ off all bits in <bit_array> #####################*/
void AllOn(uint64_t *bit_array)
{
    uint64_t all_bits_on = ~ 0;

    assert(bit_array);
    
    *bit_array |= all_bits_on;
}

void AllOff(uint64_t *bit_array)
{
    uint64_t all_bits_off = 0;

    assert (bit_array);

    *bit_array &= all_bits_off;
}

/*##################### set on/off bit <#index> in <bit_array> ####################*/
void SetOn(uint64_t *bit_array, size_t index)
{
    uint64_t bit_index = 1;
    
    assert (bit_array);

    bit_index <<= index;

    *bit_array |= bit_index;       
}

void SetOff(uint64_t *bit_array, size_t index)
{
    uint64_t bit_index = 1;
    
    assert (bit_array);

    bit_index <<= index;
    bit_index = ~bit_index;
    
    *bit_array &= bit_index;  
}

void SetBit(uint64_t *bit_array, size_t index, char value)
{
    (value) ? SetOn(bit_array, index) : SetOff(bit_array,index);
}

bool_t IsOn(uint64_t *bit_array, size_t index)
{
    uint64_t bit_index = 1;
    
    bit_index <<= index;
    
    return((*bit_array & bit_index) ? TRUE : FALSE);
}

bool_t IsOff(uint64_t *bit_array, size_t index)
{
    uint64_t bit_index = 1;
    
    bit_index <<= index;
    
    return((*bit_array & bit_index) ? FALSE : TRUE); 
        
}

void FlipBit(uint64_t *bit_array, size_t index)
{
    uint64_t bit_index = 1;
    
    bit_index <<= index;
    
    *bit_array ^= bit_index;
}

void RotateLeft(uint64_t *bit_array, size_t offset)
{
    *bit_array <<= offset;

    (bit_array << offset)|(bit_array >> ((WORDSIZE - offset)));
}

void RotateRight(uint64_t *bit_array, size_t offset)
{
    return((bit_array >> offset)|(bit_array << ((WORDSIZE - offset)))); 
}

void Mirror(uint64_t *bit_array)
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

size_t CountOn(uint64_t bit_array)
{ 
    size_t bit_counter = 0;
  
    while (bit_array)
    {
        bit_counter += (bit_array & 1);
        bit_array >>= 1;
    }
    
    return bit_counter;
}

size_t CountOff(uint64_t bit_array)
{
    size_t int bit_counter = 0;
    bit_array = ~bit_array;
  
    while (bit_array)
    {
        bit_counter += (bit_array & 1);
        bit_array >>= 1;
    }
    
    return bit_counter;
}

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



