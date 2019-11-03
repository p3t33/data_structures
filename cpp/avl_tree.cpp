/****************************************************************
*                       
* 						=====================
* File Name: template_code_cpp.cpp
* #Version: V 1.3.1
* Writer: Kobi Medrish       
* Reviewer:    
* Created: 16.5.19
* Last update: 16.9.19
****************************************************************/





/*============================================================================*/
/*                                  Definitions                               */
/*============================================================================*/
/*                                                      standard  directories */
/*                                                      ~~~~~~~~~~~~~~~~~~~~~ */
#include <iostream>
#include <assert.h> /* assert */
/*============================================================================*/
/*                                                          local directories */
/*                                                          ~~~~~~~~~~~~~~~~~ */
#include "avl_tree.hpp"
/*============================================================================*/
/*                                                           global variables */
/*                                                           ~~~~~~~~~~~~~~~~ */


/*============================================================================*/
/*                                                                      enums */
/*                                                                      ~~~~~ */


/*============================================================================*/
/*                                                                    structs */
/*                                                                    ~~~~~~~ */
namespace hrd9
{

/*============================================================================*/
/*                                  Class name                                */
/*============================================================================*/
/*                               ~~~~~~~~~~~~~~~~~                            */
/*                               special functions                            */
/*                               ~~~~~~~~~~~~~~~~~                            */
/*                                                         Constructor / ctor */
/*                                                         ~~~~~~~~~~~~~~~~~~ */

                                                                    

template <typename T>
AVL<T>::AVL(compare_t CompareFunc, void* param):
m_root(NULL),
m_CompareFunc(CompareFunc),
m_param(param)
{}



/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                                                          Destructor / dtor */
/*                                                          ~~~~~~~~~~~~~~~~~ */
template <typename T>
AVL<T>::~AVL()
{
    destroy_recursive(m_root);
    m_root = NULL;
}

template <typename T>
void AVL<T>::destroy_recursive(AVL_node<T>& node)
{
    if (NULL == node)
    {
        return;       
    }

    /* Postorder Left Right Root*/
    DestroyRecursive(node->children[LEFT]);
    DestroyRecursive(node->children[RIGHT]);
    DestroyNode(node);
}

template <typename T>
void AVL<T>::destroy_node(AVL_node<T>& node)
{
    assert(node);

    node->children[LEFT] = NULL;
    node->children[RIGHT] = NULL;
    node->data = NULL;

    delete [] node;
    node = NULL; 
}
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                                                   Copy Constructor / cctor */
/*                                                   ~~~~~~~~~~~~~~~~~~~~~~~~ */



/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                                                            copy assignment */
/*                                                            ~~~~~~~~~~~~~~~ */

/*============================================================================*/
/*                               ~~~~~~~~~~~~~~~~                             */
/*                               member functions                             */
/*                               ~~~~~~~~~~~~~~~~                             */


/*============================================================================*/
/*                        ~~~~~~~~~~~~~~~~~~~~~~~~~~~~                        */
/*                        friend / operators functions                        */
/*                        ~~~~~~~~~~~~~~~~~~~~~~~~~~~~                        */






/*============================================================================*/
/*                     API functions / Public member functions                */
/*============================================================================*/
/*                                                                  FUnctionE */
/*                                                                  ~~~~~~~~~ */

/*--------------------------------------------------------------------------- */
/*                      Auxiliary functions for FUnctionE                     */
/*--------------------------------------------------------------------------- */
/*                                                                  FUnctionE */

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
/*                                                                  FUnctionF */
/*                                                                  ~~~~~~~~~ */

/*--------------------------------------------------------------------------- */
/*                      Auxiliary functions for FUnctionF                     */
/*--------------------------------------------------------------------------- */
/*                                                                  FUnctionF */

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
/*                                                                  FUnctionG */
/*                                                                  ~~~~~~~~~ */

/*--------------------------------------------------------------------------- */
/*                      Auxiliary functions for FUnctionG                     */
/*--------------------------------------------------------------------------- */
/*                                                                  FUnctionG */

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
/*                                                                  FUnctionH */
/*                                                                  ~~~~~~~~~ */

/*--------------------------------------------------------------------------- */
/*                      Auxiliary functions for FUnctionH                     */
/*--------------------------------------------------------------------------- */
/*                                                                  FUnctionH */

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
/*                                                                  FUnctionI */
/*                                                                  ~~~~~~~~~ */
/*--------------------------------------------------------------------------- */
/*                      Auxiliary functions for FUnctionI                     */
/*--------------------------------------------------------------------------- */
/*                                                                  FUnctionI */

} // namespace hrd9
