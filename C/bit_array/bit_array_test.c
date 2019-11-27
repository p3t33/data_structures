/*******************************************************************************
*                                 bit array
*                           =====================
* File Name: bit_array_Unittest.c
* Related files: bit_array.c stack_Unittest.h
* #Version: V 1.1
* Writer: Kobi Medrish       
* Created: 26.10.19
* Last update: 27.11.19
*******************************************************************************/

/*============================================================================*/
/*                                  Definitions                               */
/*============================================================================*/
/*                                                      standard  directories */
/*                                                      ~~~~~~~~~~~~~~~~~~~~~ */

#include <stdio.h> /* printf */
#include <stdint.h> /* uint64_t */
#include <stdlib.h> /* Used for exit function */
/*============================================================================*/
/*                                                          local directories */
/*                                                          ~~~~~~~~~~~~~~~~~ */

#include "bit_array.h" 
/*============================================================================*/
/*                                                                     Macros */
/*                                                                     ~~~~~~ */


/*============================================================================*/
/*                                                                      enums */
/*                                                                      ~~~~~ */


/*============================================================================*/
/*                                                                    structs */
/*                                                                    ~~~~~~~ */

/*============================================================================*/
/*                             function declarations                          */
/*                             ~~~~~~~~~~~~~~~~~~~~~                          */
/*                                                                 Unit tests */
/*                                                                 ~~~~~~~~~~ */
static void UnitTestAllOn(void);
static void UnitTestAllOff(void);

static void UnitTestSetOn(void);
static void UnitTestSetOff(void);

static void UnitTestSetBit(void);

static void UnitTestIsOn(void);
static void UnitTestIsOff(void);

static void UnitTestFlipBit(void);

static void UnitTestRotateLeft(void);
static void UnitTestRotateRight(void);

static void UnitTestMirrorBitLut(void);
static void UnitTestMirror(void);

static void UnitTestCountBitLut(void);
static void UnitTestCountOn(void);
static void UnitTestCountOff(void);
   
/*============================================================================*/
/*                                                              User function */
/*                                                              ~~~~~~~~~~~~~ */
static void Print64BitRepresentation(uint64_t number);

/*============================================================================*/


int main()
{
    UnitTestAllOn();
    UnitTestAllOff();
    
    UnitTestSetOn();
    UnitTestSetOff();
    
    UnitTestSetBit();
    
    UnitTestIsOn();
    UnitTestIsOff();
    
    UnitTestFlipBit();
    
    UnitTestRotateLeft();
    UnitTestRotateRight();
    
    UnitTestMirrorBitLut();
    UnitTestMirror();
    
    UnitTestCountBitLut();
    UnitTestCountOn();
    UnitTestCountOff();
    
    return (0);
}

static void UnitTestCountOff(void)
{
    uint64_t number = 3;
    printf("======================= UnitTestCountOff ====================\n");
    printf("64 bit representation of number %lu\n", number);
    Print64BitRepresentation(number);
    
    printf("number of not set bits is %lu\n", CountOff(number));
    printf("=============================================================\n\n");
}

static void UnitTestCountBitLut(void)
{
    uint64_t number = 3;
    
    printf("==================== UnitTestCountBitLut ====================\n");
    printf("64 bit representation of number %lu\n", number);
    Print64BitRepresentation(number); 
  
    printf("number of set bits %lu\n", CountBitLut(number));  
    printf("=============================================================\n\n");

}

static void UnitTestCountOn(void)
{
    uint64_t number = 3;
    
    printf("======================= UnitTestCountOn =====================\n");
    printf("64 bit representation of number %lu\n", number);
    Print64BitRepresentation(number);    
    
    printf("number of set bits %lu\n", CountOn(number));  
    printf("=============================================================\n\n");
   
}

static void UnitTestMirrorBitLut(void)
{
    uint64_t number = 3;
    
    printf("=================== UnitTestMirrorBitLut ====================\n");
    printf("64 bit representation of number %lu\n", number);
    Print64BitRepresentation(number);
    
    printf("64 bit representation of the mirror number is %lu\n", number);
    Print64BitRepresentation(MirrorBitLut(number));   
    printf("=============================================================\n\n");

}

static void UnitTestMirror(void)
{
    uint64_t number = 3;
    
    printf("======================== UnitTestMirror =====================\n");
    printf("64 bit representation of number %lu\n", number);
    Print64BitRepresentation(number);    
    
    printf("64 bit representation of the mirror number is %lu\n", number);
    Print64BitRepresentation(Mirror(number));   
    printf("=============================================================\n\n");
   
}

static void UnitTestRotateRight(void)
{
    uint64_t number = 7;    
    size_t rotate_by_n_bits = 10;
    
    printf("====================== UnitTestRotateRight ==================\n");
    printf("64 bit representation of number %lu\n", number);
    Print64BitRepresentation(number);
    printf("Rotate to right by %lu\n", rotate_by_n_bits);
     
    printf("64 bit representation after the rotation\n");
    Print64BitRepresentation(RotateRight(number, rotate_by_n_bits)); 
    printf("=============================================================\n\n");
   
}

static void UnitTestRotateLeft(void)
{
    uint64_t number = 3;
    size_t rotate_by_n_bits = 4;
    
    number <<= 62;
    
    printf("====================== UnitTestRotateLeft ===================\n");
    printf("64 bit representation of number %lu\n", number);
    Print64BitRepresentation(number);
    printf("Rotate to left by %lu\n", rotate_by_n_bits);
    
    printf("64 bit representation after the rotation\n"); 
    Print64BitRepresentation(RotateLeft(number, rotate_by_n_bits));    
    printf("=============================================================\n\n");
   
}

static void UnitTestFlipBit(void)
{
    uint64_t number = 0;
    size_t bit_index_to_flip = 0;
    
    printf("======================== UnitTestFlipBit ====================\n");  
    printf("64 bit representation of number %lu\n", number);
    Print64BitRepresentation(number);
    printf("Bit index to be flipped %lu\n",bit_index_to_flip);
    
    printf("64 bit representation after the flip\n");
    Print64BitRepresentation(FlipBit(number, bit_index_to_flip));
    printf("=============================================================\n\n");
   
}

static void UnitTestIsOff(void)
{
    uint64_t number = 2;
    size_t is_bit_index_set = 0;
    
    printf("======================== UnitTestIsOff ======================\n");
    printf("64 bit representation of number %lu\n", number);
    Print64BitRepresentation(number);
     
    printf("bit to be Unittested to not be set: %lu\n",is_bit_index_set);    
    if (0 == IsOn(number, is_bit_index_set))
    {
        printf("Bit number %ld is off\n", is_bit_index_set);
    }
    
    printf("=============================================================\n\n");
   
}

static void UnitTestIsOn(void)
{
    uint64_t number = 1;
    size_t is_bit_index_set = 1;
    
    printf("======================= UnitTestIsOn ========================\n");
    printf("64 bit representation of number %lu\n", number);
    Print64BitRepresentation(number);
    
    if (0 == IsOn(number, is_bit_index_set))
    {
        printf("Bit number %ld is on\n", is_bit_index_set);
    }
    printf("=============================================================\n\n");
   
}

static void UnitTestSetBit(void)
{
    uint64_t number = 1;
    size_t bit_index_to_set = 1;
    char value_to_set = 1;
    printf("======================= UnitTestSetBit ======================\n");
    printf("64 bit representation of number %lu\n", number);
    Print64BitRepresentation(number); 
    
    printf("Bit index %lu to be set to bit value of %u\n"
    ,bit_index_to_set, value_to_set);
    printf("64 bit representation of number %lu after the set\n", number); 
    Print64BitRepresentation(SetBit(number, bit_index_to_set, value_to_set)); 
    printf("=============================================================\n\n");
   
}

static void UnitTestSetOff(void)
{
    uint64_t number = 1;
    size_t bit_index_to_set = 0;
    
    printf("======================== UnitTestSetOff =====================\n");
    printf("64 bit representation of number %lu\n", number);
    Print64BitRepresentation(number); 
    
    printf("Bit index %lu to be set to 0\n"
    ,bit_index_to_set);
    printf("64 bit representation of number %lu\n after the set\n", number);
    Print64BitRepresentation(SetOff(number,bit_index_to_set));
    printf("=============================================================\n\n");
   
}

static void UnitTestSetOn(void)
{
    uint64_t number = 0;
    size_t bit_index_to_set = 0;
    
    printf("======================== UnitTestSetOn ======================\n");
    printf("64 bit representation of number %lu\n", number);
    Print64BitRepresentation(number);     
    
    printf("Bit index %lu to be set to 1\n", bit_index_to_set);
    printf("64 bit representation of number %lu after the set\n", number);
    Print64BitRepresentation(SetOn(number,bit_index_to_set));
    printf("=============================================================\n\n");
}

static void UnitTestAllOn(void)
{
    uint64_t number = 1;
    printf("======================== UnitTestAllOn ======================\n");
    printf("64 bit representation of number %lu\n", number);
    Print64BitRepresentation(number);
    
    printf("64 bit representation after all bits set\n");
    Print64BitRepresentation(AllOn(number));
    printf("=============================================================\n\n");
   
}

static void UnitTestAllOff(void)
{
    uint64_t number = 1;
    printf("======================= UnitTestAllOff ======================\n");
    printf("64 bit representation of number %lu\n", number);
    Print64BitRepresentation(number);
    
    printf("64 bit representation after all bits set\n");
    Print64BitRepresentation(AllOff(number));
    printf("=============================================================\n\n");
         
}

/*============================================================================*/
/*                                   User function                            */             
/*============================================================================*/
/*                                                   Print64BitRepresentation */
/*                                                   ~~~~~~~~~~~~~~~~~~~~~~~~~*/
static void Print64BitRepresentation(uint64_t number)
{
    uint64_t bit_index = 1;
    int counter = 0;
    
    /*binary representation by 64 bits*/
    for (bit_index <<= 63; bit_index > 0; bit_index >>= 1)
    {
        if (0 == counter % 8 && counter != 0)
        {
            printf(" ");
        }
        
        (number & bit_index)? printf("1"): printf("0");
        ++counter;
    }
    printf("\n"); 
}
