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


#define MAX(x,y) (((x) > (y)) ? (x) : (y))


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
        size_t count(); // done
        int is_empty(); // dome
        size_t height(); // not sure
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
        AVL_node<T> *insert_recursive(AVL_node<T>& node, T& data);

        // AVLFind 
        void *find_recursive(AVL_node<T>& node, const T& data);
        // ------------------------------------------------------------------



        // Balancing functions
        // -------------------------------------------------------------------
        void update_node_hight(AVL_node<T> *node); // done
        AVL_node<T> *rotate_left(AVL_node<T> *node); // done
        AVL_node<T> *rotate_right(AVL_node<T> *node); // done
        AVL_node<T> *rebalance_node(AVL_node<T> *node); // done
        int node_balance_factor(AVL_node<T>* node); // done
        // ------------------------------------------------------------------

        // auxiliary
        // ------------------------------------------------------------------
        AVL_node<T>* create_new_node(T& data); // done
        int overwrite_node(AVL_node<T>& node, AVL_node<T>& node_next);
        void destroy_node(AVL_node<T>* node); // done
        int has_only_one_child(AVL_node<T>& node); // done
        int find_only_child_path(AVL_node<T>& node); // done
        int is_leaf(AVL_node<T>& node); // done
        AVL_node<T> *node_next(AVL_node<T>& node); // done
        void height_of_nodes_children(AVL_node<T>& node,
                                      size_t& left,
                                      size_t& right); // done
        // -----------------------------------------------------------------

        // managing variables 
        // ------------------
        AVL_node<T>* m_root;
        compare_t m_CompareFunc;

};

/*============================================================================*/
/*                                   Class AVL                                */
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

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
/*                                                                  FUnctionF */
/*                                                                  ~~~~~~~~~ */
// TODO not sure about implementaiton
template <typename T>
size_t AVL<T>::height()
{
    if (TRUE == is_empty())
    {
        return (0);
    }

    return (tree->root->height);
}

/*--------------------------------------------------------------------------- */
/*                      Auxiliary functions for FUnctionF                     */
/*--------------------------------------------------------------------------- */
/*                                                                  FUnctionF */

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
/*                                                                  FUnctionG */
/*                                                                  ~~~~~~~~~ */
template <typename T>
int AVL<T>::insert(T& data)
{
    if (TRUE == is_empty())
    {
        // TODO: exception
        m_root = create_new_node(data);

    }
    else
    {
        m_root = insert_recursive(m_root, data);
    }
    
    return (SUCCESS);
}

template <typename T>
AVL_node<T>* AVL<T>::create_new_node(T& data)
{
    /* Memory is allocated for a new node */

    // TODO: exception
    AVL_node<T>* new_node = new AVL_node<T>;

    new_node->data = data;
    new_node->height = 1;
    new_node->children[LEFT] = NULL;
    new_node->children[RIGHT] = NULL;

    return (new_node);
}

template <typename T>
AVL_node<T>* AVL<T>::insert_recursive(AVL_node<T>& node, T& data)
{
    int path = 0, difference = 0;

    difference = m_CompareFunc(data, node->data)

    /* if data to be inserted is same as the data at the tree */
    // TODO: return status
    if (ZERO == difference)
    {
        return (node);
    }

    /* if data to be inserted is greater then the data it is compared with
     * go RIGHT if smaller go LEFT */
    path = (difference > ZERO ? RIGHT : LEFT);

    if (nullptr == node->children[path])
    {
        node->children[path] = create_new_node(data);
    }
    else
    {
        node->children[path] = insert_recursive(node->children[path], data);
    }

    update_node_hight(node);
    node = rebalance_node(node);
 
    return (node);      
}

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



/*============================================================================*/
/*                               Balancing functions                          */
/*============================================================================*/
template <typename T>
void AVL<T>::update_node_hight(AVL_node<T> *node)
{
    size_t left_child_height = 0;
    size_t right_child_height = 0;

    /*in case node is a leaf there is nothing to update */


    /*Calculates the height of left and right children if there is any */
    height_of_nodes_children(node, &left_child_height, &right_child_height);

    /* store the longest path from the node to the farest leaf and add one for
       the node itself */
    node->height = MAX(left_child_height, right_child_height) + 1;
}

template <typename T>
AVL_node<T>* AVL<T>::rotate_left(AVL_node<T> *node)
{
    /* node is the unbalanced node */

    /* pivot node for rotation right */
    AVL_node<T>* pivot_node = nullptr;
    assert(node);
    pivot_node = node->children[RIGHT];

    /* unbalanced node is detached from pivot node and attached to pivots
     * left child */
    node->children[RIGHT] = node->children[RIGHT]->children[LEFT];

    /* pivot node left is attached to unbalanced node */ 
    pivot_node->children[LEFT] = node; 

    /* after rotation to the right is complite it is time to update the hight */
    update_node_hight(node);
    update_node_hight(pivot_node);

    return(pivot_node);
}

template <typename T>
AVL_node<T>* AVL<T>::rotate_right(AVL_node<T> *node)
{
    /* node is the unbalanced node */

    /* pivot node for rotation right */
    AVL_node<T>* pivot_node = nullptr;
    assert(node);

    pivot_node = node->children[LEFT];

    /* unbalanced node is detached from pivot node and attached to pivots
     * right child */
    node->children[LEFT] = node->children[LEFT]->children[RIGHT];
                             
    /* pivot node right is attached to unbalanced node */ 
    pivot_node->children[RIGHT] = node;

    /* after rotation to the right is complite it is time to update the hight */
    update_node_hight(node);
    update_node_hight(pivot_node);

    return(pivot_node);
}

template <typename T>
AVL_node<T>* AVL<T>::rebalance_node(AVL_node<T> *node)
{
    assert(node);

    /* Left Left Case
     * --------------
     * T1, T2, T3 and T4 are subtrees.
     *          z                                    y 
     *         / \                                 /   \
     *        y   T4      Right Rotate (z)        x      z
     *       / \          - - - - - - - - ->    /  \    /  \ 
     *      x   T3                             T1  T2  T3  T4
     *     / \
     *   T1   T2
     *
     */

    if (2 == node_balance_factor(node) &&
        0 <= node_balance_factor(node->children[LEFT]))
        {
            return (rotate_right(node));
        }

    /* Left Right Case
     * ---------------
     *        z                              z                          x
     *       / \                           /   \                       /  \ 
     *      y   T4  Left Rotate (y)       x    T4  Right Rotate(z)   y      z
     *     / \      - - - - - - - - ->   /  \     - - - - - - - ->  / \    / \
     *    T1   x                        y    T3                   T1  T2 T3  T4
     *        / \                      / \
     *      T2   T3                  T1   T2
     *
     */

    if (2 == node_balance_factor(node) &&
        0 > node_balance_factor(node->children[LEFT]))
        {
        /* first balance nodes left child by rotating it to the left and then
         * it is just a < Left Left case> */ 
        node->children[LEFT] = rotate_left(node->children[LEFT]);
        /* balancing for < Left Left case > */
        return (rotate_right(node));
        }

    /*
     * Right Right Case
     * ----------------                
     *      z                               y
     *     /  \                           /   \ 
     *    T1   y     Left Rotate(z)      z      x
     *       /  \   - - - - - - - ->    / \    / \
     *      T2   x                     T1  T2 T3  T4
     *          / \
     *         T3  T4
     *
     */

    if (-2 == node_balance_factor(node) &&
         0 >= node_balance_factor(node->children[LEFT]))
        {
            return (rotate_left(node));
        }

    /* 
     * Right Left Case
     * ----------------
     *
     *    z                            z                            x
     *   / \                          / \                          /  \ 
     *  T1   y   Right Rotate (y)    T1   x      Left Rotate(z)   z      y
     *      / \  - - - - - - - - ->     /  \   - - - - - - - ->  / \    / \
     *     x   T4                      T2   y                  T1  T2  T3  T4
     *    / \                              /  \
     *  T2   T3                           T3   T4
     * 
     */

    if (-2 == node_balance_factor(node) &&
        0 < node_balance_factor(node->children[LEFT]))
        {
            node->children[RIGHT] = rotate_right(node->children[RIGHT]);
            return (rotate_left(node));
        } 

    return (node);
}

template <typename T>
int AVL<T>::node_balance_factor(AVL_node<T>* node)
{
    size_t right_child_height = 0;
	size_t left_child_height = 0;
	int balance_factor = 0;

	if (nullptr == node)
	{
		return (balance_factor);
	}

    height_of_nodes_children(node, &left_child_height, &right_child_height);

	if (left_child_height > right_child_height)
	{
		balance_factor = left_child_height - right_child_height;
	}
	else
	{
		balance_factor = - 1 * (int)(right_child_height - left_child_height);
	}

	return (balance_factor);
}

template <typename T>
void AVL<T>::height_of_nodes_children(AVL_node<T>& node, size_t& left,size_t& right)
{
    assert(node);
    assert(right);
    assert(left);

    /* Store the height of right child if there is one */
    if (nullptr != node->children[RIGHT])
    {
        *right = node->children[RIGHT]->height;
    }

    /* Store the height of left child if there is one */
    if (nullptr != node->children[LEFT])
    {
        *left = node->children[LEFT]->height;
    }
}


/*============================================================================*/
/*                               Auxiliary functions                          */
/*============================================================================*/

template <typename T>
int AVL<T>::overwrite_node(AVL_node<T>& node, AVL_node<T>& node_next)
{
    assert(node);
	assert(node_next);

    node->data = node_next->data;
    node->children[RIGHT] = node_next->children[RIGHT];
    node->children[LEFT] = node_next->children[LEFT];
}

template <typename T>
int AVL<T>::has_only_one_child(AVL_node<T>& node)
{
    assert(node);
    return ((nullptr == node->children[LEFT] || nullptr == node->children[RIGHT]));
}

template <typename T>
int AVL<T>::find_only_child_path(AVL_node<T>& node)
{
    assert(node);
    return (nullptr == node->children[LEFT]);
}

template <typename T>
int AVL<T>::is_leaf(AVL_node<T>& node)
{
    assert(node);
    return (nullptr == node->children[LEFT] && nullptr == node->children[RIGHT]);
}

template <typename T>
AVL_node<T>* AVL<T>::node_next(AVL_node<T>& node)
{
    assert(node);
    if (nullptr == node->children[LEFT])
    {
        return (node);
    }

    return (node_next(node->children[LEFT]));
}

} // namespace hrd9
#endif // _AVL_TREE_


