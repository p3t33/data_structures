/*******************************************************************************
*                       
* 						=====================
* File Name: template_test_cpp_cpp
* #Version: V 1.0.4
* Writer: Kobi Medrish       
* Reviewer: 
* Created: 16.5.19
* Last update: 22.7.19
*******************************************************************************/

/*============================================================================*/
/*                                  Definitions                               */
/*============================================================================*/
/*                                                      standard  directories */
/*                                                      ~~~~~~~~~~~~~~~~~~~~~ */
#include <iostream>
#include <stdio.h> /* printf */
#include <assert.h> /* assert */
/*============================================================================*/
/*                                                          local directories */
/*                                                          ~~~~~~~~~~~~~~~~~ */
#include "avl_tree.hpp"
/*============================================================================*/
/*                                                                     Macros */
/*                                                                     ~~~~~~ */


using namespace hrd9;
/*============================================================================*/
/*                             function declarations                          */
/*----------------------------------------------------------------------------*/
/*                                                                 Unit tests */



/*                                                           Integration Test */      
/*============================================================================*/
/*                                                              User function */
int IntDataCompare(const int data1, const int data2);
int ActionPrintInt(void *data);
int IsMatch(void *data, void *arg);
/*============================================================================*/
/*                                                                      enums */
/*                                                                      ~~~~~ */


/*============================================================================*/
/*                                                                    structs */
/*                                                                    ~~~~~~~ */
 
/*============================================================================*/
/*                                                                     Colors */
/*                                                                     ~~~~~~ */
const char* const green = "\033[1;32m";
const char* const red = "\033[1;32m";
const char* const reset = "\033[0m"; 
/*============================================================================*/
/*                             ~~~~~~~~~~~~~~~~~~~                            */
/*                             Forward declaration                            */
/*                             ~~~~~~~~~~~~~~~~~~~                            */
/*                                                                 Unit tests */
/*                                                                 ~~~~~~~~~~ */
static void unit_test_AVL_create(void);
static void Unit_test_y(void);
static void unit_test_z(void);
static void unit_test_k(void);
static void unit_test_m(void);
static void unit_test_a(void);
static void unit_test_b(void);
static void unit_test_c(void);
static void unit_test_d(void);
static void unit_test_e(void);

/*                                                           Integration Test */ 
/*                                                           ~~~~~~~~~~~~~~~~ */  
   
/*============================================================================*/
/*                                                              User function */
/*                                                              ~~~~~~~~~~~~~ */

/*============================================================================*/

int main()
{
    unit_test_AVL_create();
/*     Unit_test_y();
    unit_test_z();
    unit_test_k();
    unit_test_m();
    unit_test_a();
    unit_test_b();
    unit_test_c();
    unit_test_d();
    unit_test_e(); */
  
    return (0);
}

/*============================================================================*/
/*                                 unit_test_s                                */
/*============================================================================*/
/*                                                                  unit_test_AVL_create */
/*                                                                  ~~~~~~~~~ */

static void unit_test_AVL_create(void)
{  
    std::cout << "=================== unit_test_AVL_create ================"<< std::endl;

    AVL<int> tree(IntDataCompare);


    if (0 != (tree.count()))
    {
        printf("Empty tree counted currently #FAIL#\n");
    }
    else
    {
        printf("Empty tree counted currently #SUCCESS#\n");
    }

    if (1 != tree.is_empty())
    {
        printf("Tree is empty as it should according to AVLIsEmpty #FAIL\n");
    }
    else
    {
        printf("Tree is empty as it should according to AVLIsEmpty #SUCCESS\n");
    }

    std::cout << "================================================"<< std::endl;
    
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                                                                  Unit_test_y */
/*                                                                  ~~~~~~~~~ */
static void Unit_test_y(void)
{
    std::cout << "=================== Unit_test_y ================"<< std::endl;    
    

    std::cout << "================================================"<< std::endl;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                                                                  unit_test_z */
/*                                                                  ~~~~~~~~~ */
static void unit_test_z(void)
{
    std::cout << "=================== unit_test_z ================"<< std::endl;    
   

    std::cout << "================================================"<< std::endl;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                                                                  unit_test_k */
/*                                                                  ~~~~~~~~~ */
static void unit_test_k(void)
{
    std::cout << "=================== unit_test_k ================"<< std::endl;    
   

    std::cout << "================================================"<< std::endl;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                                                                  unit_test_m */
/*                                                                  ~~~~~~~~~ */
static void unit_test_m(void)
{
    std::cout << "=================== unit_test_m ================"<< std::endl;    
   

    std::cout << "================================================"<< std::endl;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                                                                  unit_test_a */
/*                                                                  ~~~~~~~~~ */
static void unit_test_a(void)
{
    std::cout << "=================== unit_test_a ================"<< std::endl;    
    

    std::cout << "================================================"<< std::endl;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                                                                  unit_test_b */
/*                                                                  ~~~~~~~~~ */
static void unit_test_b(void)
{
    std::cout << "=================== unit_test_b ================"<< std::endl;    
    

    std::cout << "================================================"<< std::endl;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                                                                  unit_test_c */
/*                                                                  ~~~~~~~~~ */
static void unit_test_c(void)
{
    std::cout << "=================== unit_test_c ================"<< std::endl;   

    std::cout << "================================================"<< std::endl;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                                                                  unit_test_d */
/*                                                                  ~~~~~~~~~ */
static void unit_test_d(void)
{
    std::cout << "=================== unit_test_d ================"<< std::endl;    
   

    std::cout << "================================================"<< std::endl;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                                                                  unit_test_e */
/*                                                                  ~~~~~~~~~ */
static void unit_test_e(void)
{
    std::cout << "=================== unit_test_e ================"<< std::endl;    
    

    std::cout << "================================================"<< std::endl;
}



/*============================================================================*/
/*                                   User function                            */             
/*============================================================================*/
/*                                                             IntDataCompare */
int IntDataCompare(const int data1, const  int data2)
{

	return (data1 - data2);
}

/*============================================================================*/
/*                                                           action print int */
int ActionPrintInt(void *data)
{

    printf("%d ", *(int*)data);

    return 0;    
}

/*============================================================================*/
int IsMatch(void *data, void *arg)
{
    return (*(int*)data < *(int*)arg);
}
