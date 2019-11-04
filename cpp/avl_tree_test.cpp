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
int int_data_compare(const int data1, const int data2);
int action_print_int(int data);
int is_match(int data, int arg);
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
static void unit_test_remove_allVL_create(void);
static void Unit_test_insert(void);
static void unit_test_remove(void);
static void unit_test_balancing(void);
static void unit_test_find_all(void);
static void unit_test_remove_all(void);


/*                                                           Integration Test */ 
/*                                                           ~~~~~~~~~~~~~~~~ */  
   
/*============================================================================*/
/*                                                              User function */
/*                                                              ~~~~~~~~~~~~~ */

/*============================================================================*/

int main()
{
    unit_test_remove_allVL_create();
    Unit_test_insert();

    
    unit_test_remove();
  
    unit_test_balancing();
  
    unit_test_find_all();
     
    unit_test_remove_all();

    /* 
    unit_test_b();
    unit_test_c();
    unit_test_d();
    unit_test_e(); */
  
    return (0);
}

/*============================================================================*/
/*                                 unit_test_s                                */
/*============================================================================*/
/*                                                                  unit_test_remove_allVL_create */
/*                                                                  ~~~~~~~~~ */

static void unit_test_remove_allVL_create(void)
{  
    std::cout << "=================== unit_test_remove_allVL_create ================"<< std::endl;

    AVL<int> tree(int_data_compare);


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
/*                                                                  Unit_test_insert */
/*                                                                  ~~~~~~~~~ */
static void Unit_test_insert(void)
{
    std::cout << "=================== Unit_test_insert ================"<< std::endl;    

    int at_tree = 5, i = 0, not_at_tree = 20;
    int arr[] = {1 ,50 , 5, 7, 19, 35}; 

    AVL<int> tree(int_data_compare);

    /* inserting data to the tree */
    for(i = 0; i < 6; ++i)
    {
        tree.insert(&arr[i]);

    }

    std::cout << "number of elements in the tree\n"<< tree.count() << std::endl;

    std::cout << "All data in the ordered tree from small to big" << std::endl;
    tree.for_each(action_print_int);
    std::cout << std::endl;


    std::cout << "Test AVLFind function for 5 that is in the tree \n" << std::endl;

    if(5 == *(int*)tree.find(&at_tree))
    {
        printf("AVLFind located the requested data as it should #SUCCESS#\n");
    }
    else
    {
        printf("AVLFind located the requested data as it should #FAIL#\n");    
    }


    std::cout << "Test AVLFind function for 20 that is not in the tree \n" << std::endl;

    if(nullptr == tree.find(&not_at_tree))
    {
        printf("AVLFind did not located the requested data as it should "
              "#SUCCESS#\n");
    }
    else
    {
        printf("AVLFind did not located the requested data as it should "
               "#FAIL#\n");    
    }

    std::cout << "================================================"<< std::endl;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                                                                  unit_test_remove */
/*                                                                  ~~~~~~~~~ */
static void unit_test_remove(void)
{
    std::cout << "=================== unit_test_remove ================"<< std::endl;    
   
    int arr[] = {5 ,10 , 3, 7, 19, 35, 4, 2, 1}; 

    AVL<int> tree(int_data_compare);


    printf("Remove from an empty tree \n");
    tree.remove(&arr[0]);

    /* inserting data to the tree */
    for(size_t i = 0; i < 9; ++i)
    {
        tree.insert(&arr[i]);

    }


    std::cout << "number of elements in the tree\n"<< tree.count() << std::endl;

    std::cout << "All data in the ordered tree from small to big" << std::endl;
    tree.for_each(action_print_int);
    std::cout << std::endl;

    printf("remove root <5>, leaf <1> intersection <10> element and print\n");
    printf("\n");
    tree.remove(&arr[0]);
    tree.remove(&arr[8]);
    tree.remove(&arr[1]);

    
    std::cout << "number of elements in the tree\n"<< tree.count() << std::endl;
    std::cout << "All data in the ordered tree from small to big" << std::endl;
    tree.for_each(action_print_int);
    std::cout << std::endl;






    std::cout << "================================================"<< std::endl;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                                                                  unit_test_balancing */
/*                                                                  ~~~~~~~~~ */
static void unit_test_balancing(void)
{
    std::cout << "=================== unit_test_balancing ================"<< std::endl;    
    
    int i = 0;
    int arr[] = {2 ,1, 3, 4, 5, 6, 7, 8, 9}; 

    /* Tree created */ 
    AVL<int> tree(int_data_compare);

    /* inserting data to the tree */
    for(i = 0; i < 9; ++i)
    {
        tree.insert(&arr[i]);
        
        printf ("height of the tree %lu \n", tree.height()); 
    } 

    std::cout << "number of elements in the tree\n"<< tree.count() << std::endl;
    std::cout << "All data in the ordered tree from small to big" << std::endl;
    tree.for_each(action_print_int);
    std::cout << std::endl;


    std::cout << "================================================"<< std::endl;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                                                                  unit_test_find_all */
/*                                                                  ~~~~~~~~~ */
static void unit_test_find_all(void)
{
    std::cout << "=================== unit_test_find_all ================"<< std::endl;    
   
    int i = 0;
    int arr[] = {2 ,1, 3, 4, 5, 6, 7, 8, 9}; 
    int arg = 6;

    /* Tree created */ 
    AVL<int> tree(int_data_compare);


    /* inserting data to the tree */
    for(i = 0; i < 9; ++i)
    {
        tree.insert(&arr[i]);
        
    } 

    std::cout << "number of elements in the tree\n"<< tree.count() << std::endl;
    std::cout << "All data in the ordered tree from small to big" << std::endl;
    tree.for_each(action_print_int);
    std::cout << std::endl;

    tree.find_all(is_match, &arg);

    std::cout << "All data int tree smaller then 6" << std::endl;
    for (auto i: tree.get_vector())
    {
        printf("%d->", *(int*)i);    
    }

    std::cout << std::endl;


    std::cout << "================================================"<< std::endl;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                                                                  unit_test_remove_all */
/*                                                                  ~~~~~~~~~ */
static void unit_test_remove_all(void)
{
    std::cout << "=================== unit_test_remove_all ================"<< std::endl;    
    
    int i = 0;
    int arr[] = {5 ,10 , 3, 7, 19, 35, 4, 2, 1};
    int arg = 6;

    AVL<int> tree(int_data_compare);

    /* inserting data to the tree */
    for(i = 0; i < 9; ++i)
    {
        tree.insert(&arr[i]);
    } 

    std::cout << "number of elements in the tree\n"<< tree.count() << std::endl;
    std::cout << "All data in the ordered tree from small to big" << std::endl;
    tree.for_each(action_print_int);
    std::cout << std::endl;

    printf("Find all data smaller then 6, and remove it and print the list \n");
    tree.remove_all(is_match, &arg);


    std::cout << "number of elements in the tree\n"<< tree.count() << std::endl;
    std::cout << "All data in the ordered tree from small to big" << std::endl;
    tree.for_each(action_print_int);
    std::cout << std::endl;

    std::cout << "================================================"<< std::endl;
}


/*============================================================================*/
/*                                   User function                            */             
/*============================================================================*/
/*                                                             int_data_compare */
int int_data_compare(const int data1, const  int data2)
{

	return (data1 - data2);
}

/*============================================================================*/
/*                                                           action print int */
int action_print_int(int data)
{

    printf("%d ", data);

    return 0;    
}

/*============================================================================*/
int is_match(int data, int arg)
{
    return (data < arg);
}
