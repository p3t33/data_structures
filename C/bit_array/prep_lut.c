/*******************************************************************************
*                               prep lut
*                       =====================
* File Name: prep_lut.c
* Related files: prep_lut.h
* #Version: V 1.0
* Writer: Kobi Medrish       
* Created: 26.11.19
* Last update: 26.11.19
*******************************************************************************/


/*============================================================================*/
/*                                  Definitions                               */
/*============================================================================*/
/*                                                      standard  directories */
/*                                                      ~~~~~~~~~~~~~~~~~~~~~ */

#include <stdio.h> /* used for fwrite, printf, FILE */
#include <stdint.h> /* uint8_t */

/*============================================================================*/
/*                                                                     Macros */
/*                                                                     ~~~~~~ */
#define FAILED_TO_OPEN_FILE NULL


/*============================================================================*/
/*                                                                      enums */
/*                                                                      ~~~~~ */
enum status {success, failed_to_open_file, failed_to_write_to_file};

/*============================================================================*/

/*                         ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~                    */
/*                         Auxiliary Functions Declaration                    */
/*                         ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~                    */


/*                                                              CreateLutFile */
/*                                                              ~~~~~~~~~~~~~ */
int CreateLutFile(void);

/*                                                             CountOnOneByte */
/*                                                             ~~~~~~~~~~~~~~ */
uint8_t CountOnOneByte(uint8_t barr);

/*                                                              MirrorOneByte */
/*                                                              ~~~~~~~~~~~~~ */
uint8_t MirrorOneByte(uint8_t barr);


int main ()
{
    CreateLutFile();
    return (0);
}

int CreateLutFile(void)
{
    int  i = 0;
    int num_of_written_bytes = 0; /* Used to make the code more readble, will
                                     be set to to number of bytes written by the
                                     fprintf function. The variable is evaluated
                                     each time fprintf is called. */
                               
    FILE *file_pointer = 0;
    
    file_pointer = fopen("prep_lut.h","w");
    if (FAILED_TO_OPEN_FILE == file_pointer)
    {
        return (failed_to_open_file);
    }

      
    num_of_written_bytes = fprintf(file_pointer, "%s\n%s\n\n%s",
    "#ifndef _PREP_LUT_",
    "#define _PREP_LUT_", "uint8_t count_array[256] = {");

    if (0 > num_of_written_bytes)
    {
        return (failed_to_write_to_file);
    }
    
    for (i = 0; i < 255; ++i)
    {
        (0 == i % 27)? (num_of_written_bytes = fprintf(file_pointer,"\n")): 0;
        if (0 > num_of_written_bytes)
        {
            return (failed_to_write_to_file);
        }
            
        num_of_written_bytes = fprintf(file_pointer, "%d, ",CountOnOneByte(i));
        if (0 > num_of_written_bytes)
        {
            return (failed_to_write_to_file);
        }       
    }
    
    num_of_written_bytes = fprintf(file_pointer, "%d };\n\n",CountOnOneByte(i));
    if (0 > num_of_written_bytes)
    {
        return (failed_to_write_to_file);
    }    
    
    num_of_written_bytes = fprintf(file_pointer, 
                                   "%s", 
                                   "uint8_t mirror_arr[256] = {");
    if (0 > num_of_written_bytes)
    {
        return (failed_to_write_to_file);
    }
    
    for (i = 0; i < 255; ++i)
    {
        (0 == i % 17)? (num_of_written_bytes = fprintf(file_pointer,"\n")): 0;
        if (0 > num_of_written_bytes)
        {
            return (failed_to_write_to_file);
        }
            
        num_of_written_bytes = fprintf(file_pointer, "%d, ",MirrorOneByte(i));
        if (0 > num_of_written_bytes)
        {
            return (failed_to_write_to_file);
        }       
    }
    
    num_of_written_bytes = fprintf(file_pointer,
                                   "\n%d };\n\n", 
                                    MirrorOneByte(i));
    if (0 > num_of_written_bytes)
    {
        return (failed_to_write_to_file);
    }
     
    num_of_written_bytes = fprintf(file_pointer, 
                                   "%s\n",
                                   "#endif /* _PREP_LUT_ */");
    if (0 > num_of_written_bytes)
    {
        return (failed_to_write_to_file);
    }
    
    fclose(file_pointer);

    return(success);
}

uint8_t  CountOnOneByte(uint8_t barr)
{ 
    uint8_t bit_counter = 0;
  
    while (barr)
    {
        bit_counter += (barr & 1);
        barr >>= 1;
    }
    
    return bit_counter;
}

uint8_t MirrorOneByte(uint8_t barr)
{
    uint8_t count = 8;
    uint8_t out_number = 0;

    /* Mirroes a number bit by bit and after the loop "pushes" it the the
       right place using what is left of count variable */
    while (barr)
    {   
        out_number <<= 1;
        
        out_number |= barr & 1;
        
        barr >>=1;
        
        --count;
    }
    
    out_number <<= count;
   
    return out_number;
}
