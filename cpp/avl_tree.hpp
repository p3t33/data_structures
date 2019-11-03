#ifndef _AVL_TREE_
#define _AVL_TREE_

/*******************************************************************************
*                          AVL tree
*                   =====================
* File Name: avl_tree.hpp
* Related files: avl_tree.cpp avl_tree_test.hpp
* #Version: V 1.0
* Writer: Kobi Medrish       
* Created: 3.11.19
* Last update: 3.11.19
*******************************************************************************/
#include <stddef.h> /* size_t */
#include <functional> // using

namespace hrd9
{

template <typename T>
struct AVL_node
{
    T* data;
    struct AVL_node *children[2];
    size_t height;
};


template <typename T>
class AVL
{
    private:

    using compare_t = std::function<int(const T data1, const T data2)>;
    using action_func_t = std::function<int(T& data)>;
    using is_match_t = std::function<int(T& data, T& param)>;

    enum children {LEFT, RIGHT};
    enum boolean_state {FALSE, TRUE};
    enum status {SUCCESS, FAILURE, DATA_ALREADY_EXISTS};
    
    public:
        AVL(compare_t CompareFunc); // create
        ~AVL(); // destroy

        // Interface / API
        // ------------------------------------------------------------------
        int insert(T& data);
        void remove(T& data);
        void *find(const T& data);
        size_t count();
        int is_empty();
        size_t height();
        int for_each(action_func_t ActionFunc);
        // ------------------------------------------------------------------

    private:
        // auxilary
        // ------------------------------------------------------------------
        // dtor 
        void destroy_recursive(AVL_node<T>* node);

        // AVLCount
        size_t count_recursive(AVL_node<T>* node);

        // AVLForEach
        int for_each_recursive(AVL_node<T>& node,
                             action_func_t ActionFunc,
                             T& param); 
        
        // AVLRemove
        AVL_node<T> *remove_recursive(AVL_node<T>& node, T& data);
        AVL_node<T> *remove_node(AVL_node<T>& node);

        // AVLInsert
        AVL_node<T> *insert_recursive(AVL_node<T>& node, T& data,
                            compare_t CompareFunc, T& param, int& status);

        // AVLFind 
        void *find_recursive(AVL_node<T>& node, const T& data);
        // ------------------------------------------------------------------



        // Balancing functions
        // -------------------------------------------------------------------
        void update_node_hight(AVL_node<T> *node);
        AVL_node<T> *rotate_left(AVL_node<T> *node);
        AVL_node<T> *rotate_right(AVL_node<T> *node);
        AVL_node<T> *rebalance_node(AVL_node<T> *node);
        // ------------------------------------------------------------------

        AVL_node<T> *create_new_node(T& data);
        int overwrite_node(AVL_node<T>& node, AVL_node<T>& node_next);
        void destroy_node(AVL_node<T>* node);
        int has_only_one_child(AVL_node<T>& node);
        int find_only_child_path(AVL_node<T>& node);
        int is_leaf(AVL_node<T>& node);
        AVL_node<T> *node_next(AVL_node<T>& node);
        void height_of_nodes_children(AVL_node<T>& node, size_t& left,size_t& right);

        // managing variables 
        // ------------------
        AVL_node<T>* m_root;
        compare_t m_CompareFunc;

};

/*============================================================================*/
/*                                  Class name                                */
/*============================================================================*/
/*                               ~~~~~~~~~~~~~~~~~                            */
/*                               special functions                            */
/*                               ~~~~~~~~~~~~~~~~~                            */
/*                                                         Constructor / ctor */
/*                                                         ~~~~~~~~~~~~~~~~~~ */

template <typename T>
AVL<T>::AVL(compare_t CompareFunc):
m_root(nullptr),
m_CompareFunc(CompareFunc)
{}



/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                                                          Destructor / dtor */
/*                                                          ~~~~~~~~~~~~~~~~~ */
template <typename T>
AVL<T>::~AVL()
{
    destroy_recursive(m_root);
    m_root = nullptr;
}

template <typename T>
void AVL<T>::destroy_recursive(AVL_node<T>* node)
{
    if (nullptr == node)
    {
        return;       
    }

    /* Postorder Left Right Root*/
    destroy_recursive(node->children[LEFT]);
    destroy_recursive(node->children[RIGHT]);
    destroy_node(node);
}

template <typename T>
void AVL<T>::destroy_node(AVL_node<T>* node)
{
    assert(node);

    node->children[LEFT] = nullptr;
    node->children[RIGHT] = nullptr;
    node->data = nullptr;

    delete  node;
    node = nullptr; 
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

template <typename T>
size_t AVL<T>::count()
{
    return (count_recursive(m_root));
}



/*--------------------------------------------------------------------------- */
/*                      Auxiliary functions for FUnctionE                     */
/*--------------------------------------------------------------------------- */
/*                                                                  FUnctionE */
template <typename T>
size_t AVL<T>::count_recursive(AVL_node<T>* node)
{
    if (nullptr == node)
    {
        return(SUCCESS);       
    }
    
    /* Preorder: Root-Left-Right */
    return (1 + 
            count_recursive(node->children[LEFT]) + 
            count_recursive(node->children[RIGHT]));
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
/*                                                                  FUnctionF */
/*                                                                  ~~~~~~~~~ */
template <typename T>
int AVL<T>::is_empty()
{
    return (nullptr == m_root);
}
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
#endif // _AVL_TREE_


