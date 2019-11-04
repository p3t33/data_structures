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
#include <vector>


#define MAX(x,y) (((x) > (y)) ? (x) : (y))


namespace hrd9
{

template <typename T>
class AVL_node
{
    public:
        AVL_node(T* data = nullptr,
                 size_t height = 1,
                 AVL_node* children_left = nullptr,
                 AVL_node* children_right = nullptr):
                        m_data(data),
                        m_height(height),
                        m_children{children_left, children_right}
        {}


        AVL_node* operator=(const AVL_node* other)
        {
            m_data = other->m_data;
            // m_height = other->m_height;
            m_children[1] = other->m_children[1];
            m_children[0] = other->m_children[0];    
        }
    

        T* m_data;
        size_t m_height;
        struct AVL_node* m_children[2];

};


template <typename T>
class AVL
{
    private:

    using compare_t = std::function<int(const T data1, const T data2)>;
    using action_func_t = std::function<int(T data)>;
    using is_match_t = std::function<int(T data, T arg)>;

    static const int ZERO = 0;

    enum children {LEFT, RIGHT};
    enum boolean_state {FALSE, TRUE};
    enum status {SUCCESS, FAILURE, DATA_ALREADY_EXISTS};
    
    public:
        AVL(compare_t CompareFunc); // create
        ~AVL(); // destroy

        // Interface / API
        // ------------------------------------------------------------------
        int insert(T* data); // done
        void remove(T* data); // done
        T* find(const T* data); // done
        size_t count(); // done
        int is_empty(); // done
        size_t height(); // done
        int for_each(action_func_t action_func); // done
        int find_all(is_match_t is_match, T* arg); // done
        void remove_all(is_match_t is_match, T* arg);

        std::vector<T*>& get_vector();

        // ------------------------------------------------------------------

    private:
        // auxilary
        // ------------------------------------------------------------------
        // dtor 
        void destroy_recursive(AVL_node<T>* node);

        // AVLCount
        size_t count_recursive(AVL_node<T>* node);

        // AVLForEach
        int for_each_recursive(AVL_node<T>* node, action_func_t action_func); 
        
        // AVLRemove
        AVL_node<T> *remove_recursive(AVL_node<T>* node, T* data);
        AVL_node<T> *remove_node(AVL_node<T>* node);

        // AVLInsert
        AVL_node<T>* insert_recursive(AVL_node<T>* node, T* data);

        // AVLFind 
        T* find_recursive(AVL_node<T>* node, const T* data);

        // AVLFindAll
        int find_all_rec(AVL_node<T>* node, is_match_t is_match, T* arg);

        // remove_all
        int remove_all_rec(AVL_node<T>* node, is_match_t is_match, T* arg);

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
        
        int overwrite_node(AVL_node<T>* node, AVL_node<T>* node_next);  // TODO: should be done via cctor
        void destroy_node(AVL_node<T>* node); // done
        int has_only_one_child(AVL_node<T>* node); // done
        int find_only_child_path(AVL_node<T>* node); // done
        int is_leaf(AVL_node<T>* node); // done
        AVL_node<T> *node_next(AVL_node<T>* node); // done
        void height_of_nodes_children(AVL_node<T>* node,
                                      size_t* left,
                                      size_t* right); // done
        // -----------------------------------------------------------------

        // managing variables 
        // ------------------
        AVL_node<T>* m_root;
        compare_t m_CompareFunc;
        std::vector<T*> m_find_all; // used for find_all

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
m_CompareFunc(CompareFunc),
m_find_all(0)
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
    destroy_recursive(node->m_children[LEFT]);
    destroy_recursive(node->m_children[RIGHT]);
    destroy_node(node);
}

template <typename T>
void AVL<T>::destroy_node(AVL_node<T>* node)
{

    //TODO: exception

    delete node;
    node = nullptr; 
}
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                                                   Copy Constructor / cctor */
/*                                                   ~~~~~~~~~~~~~~~~~~~~~~~~ */

template <typename T>
std::vector<T*>& AVL<T>::get_vector()
{
    return (m_find_all);
}
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
            count_recursive(node->m_children[LEFT]) + 
            count_recursive(node->m_children[RIGHT]));
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

    return (m_root->m_height);
}

/*--------------------------------------------------------------------------- */
/*                      Auxiliary functions for FUnctionF                     */
/*--------------------------------------------------------------------------- */
/*                                                                  FUnctionF */

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
/*                                                                  FUnctionG */
/*                                                                  ~~~~~~~~~ */
template <typename T>
int AVL<T>::insert(T* data)
{
    if (TRUE == is_empty())
    {
        // TODO: exception
        m_root = new AVL_node<T>(data);
    }
    else
    {
        m_root = insert_recursive(m_root, data);
    }
    
    return (SUCCESS);
}


template <typename T>
AVL_node<T>* AVL<T>::insert_recursive(AVL_node<T>* node, T* data)
{
    int path = 0, difference = 0;

    difference = m_CompareFunc(*data, *(node->m_data));

    /* if data to be inserted is same as the data at the tree */
    // TODO: return status
    if (ZERO == difference)
    {
        return (node);
    }

    /* if data to be inserted is greater then the data it is compared with
     * go RIGHT if smaller go LEFT */
    path = (difference > ZERO ? RIGHT : LEFT);

    if (nullptr == node->m_children[path])
    {
        node->m_children[path] = new AVL_node<T>(data);
    }
    else
    {
        node->m_children[path] = insert_recursive(node->m_children[path], data);
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
template <typename T>
int AVL<T>::for_each(action_func_t action_func)
{
    return (for_each_recursive(m_root, action_func));
}

template <typename T>
int AVL<T>::for_each_recursive(AVL_node<T>* node, action_func_t action_func)
{
    if (nullptr != node)
    {
        /* In Oreder: Left-Root-Right */
        // TODO: exception
        for_each_recursive(node->m_children[LEFT], action_func);

        // TODO: exception
        action_func(*(node->m_data));

        // TODO: exception

        for_each_recursive(node->m_children[RIGHT], action_func);
    }

    return (SUCCESS);
}


/*--------------------------------------------------------------------------- */
/*                      Auxiliary functions for FUnctionH                     */
/*--------------------------------------------------------------------------- */
/*                                                                  FUnctionH */

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
/*                                                                  FUnctionI */
/*                                                                  ~~~~~~~~~ */
template <typename T>
T* AVL<T>::find(const T* data)
{
    // TODO: exception
    return (find_recursive(m_root, data));
}

template <typename T>
T* AVL<T>::find_recursive(AVL_node<T>* node, const T* data)
{
    int path = 0, deffrance = 0;

    if (nullptr == node)
	{
		return (nullptr);
	}

    deffrance = m_CompareFunc(*data, *(node->m_data));

    /* if deffrance between data at node and data provided for the search is 
     * zero then data was found */
    if(ZERO == deffrance)
    {
        return (node->m_data);
    }

    /* in case data provided for the search is smaller or bigger then the data
     * at the node there is a need to decide which path to take to procide the
     * search */ 
    path = (deffrance > ZERO ? RIGHT : LEFT);
    
    /* if the path is a "dead end" then data is not in the tree */
    if (nullptr == node->m_children[path])
    {
        return nullptr;
    }

    /* Search will continue in accordance to the chosen path */ 
    return (find_recursive(node->m_children[path], data));
}


/*--------------------------------------------------------------------------- */
/*                      Auxiliary functions for FUnctionI                     */
/*--------------------------------------------------------------------------- */
/*                                                                  FUnctionI */

template <typename T>
void AVL<T>::remove(T* data)
{
    m_root = remove_recursive(m_root, data);
}

template <typename T>
AVL_node<T>* AVL<T>::remove_recursive(AVL_node<T>* node, T* data)
{
    int path = 0, deffrance = 0;

    if (nullptr == node)
    {
        return(node);
    }

    deffrance = m_CompareFunc(*data, *(node->m_data));
    /* 
     * Start of search for matching data
     * ---------------------------------
     */
    if (ZERO != deffrance)
    {
        path = (deffrance > ZERO ? RIGHT : LEFT);

        node->m_children[path] = remove_recursive(node->m_children[path], data);    
    }
    else
    {
        node = remove_node(node);
    }
    
    
    if (nullptr != node)
    {
        update_node_hight(node);
        node = rebalance_node(node);
    }

    return (node);
}

/*--------------------------------------------------------------------------- */
/*                      Auxiliary functions for FUnctionI                     */
/*--------------------------------------------------------------------------- */
/*                                                                  FUnctionI */
template <typename T>
void AVL<T>::remove_all(is_match_t is_match, T* arg)
{
    remove_all_rec(m_root, is_match, arg);
}

template <typename T>
int AVL<T>::remove_all_rec(AVL_node<T>* node, is_match_t is_match, T* arg)
{

    if (nullptr != node)
    {
        remove_all_rec(node->m_children[RIGHT], is_match, arg); 
        remove_all_rec(node->m_children[LEFT], is_match, arg);  
        if (TRUE == is_match(*(node->m_data), *arg))
        {
            remove(node->m_data);
        }
    }
    return (SUCCESS);
}



template <typename T>
AVL_node<T>* AVL<T>::remove_node(AVL_node<T>* node)
{
    //int path = 0;
    AVL_node<T>* disposable_node = nullptr;

    /* in case there is no children */
    if (TRUE == is_leaf(node))
    {
        destroy_node(node);  
        return (nullptr);  
    }

    else if (TRUE == has_only_one_child(node))
	{

        disposable_node = node->m_children[find_only_child_path(node)];

        /* Overwrite node with information from temp_node */
        *node = *(disposable_node);

        //overwrite_node(node, disposable_node);
        destroy_node(disposable_node);		
        //disposable_node = nullptr;
	}
    else /* node has 2 children */
    {
        /* There is a need to find nodes <NEXT>. */
        //disposable_node = node_next(node->m_children[RIGHT]);

        /* overite data with the data of <NEXT> */
        node->m_data = (node_next(node->m_children[RIGHT]))->m_data;

        /* Now go to the right and start searching the data that was used to
           Overite the data in the node. once it will be found ut will have 
           one ore zero children and will be handled by simple cases in 
           RemoveNode */
		node->m_children[RIGHT] = remove_recursive(node->m_children[RIGHT],
                                                   node->m_data);
    }
    
    return (node); 
}

/*--------------------------------------------------------------------------- */
/*                      Auxiliary functions for FUnctionI                     */
/*--------------------------------------------------------------------------- */
/*                                                                  FUnctionI */
template <typename T>
int AVL<T>::find_all(is_match_t is_match, T *arg)
{
    return (find_all_rec(m_root, is_match, arg));
}

template <typename T>
int AVL<T>::find_all_rec(AVL_node<T>* node, is_match_t is_match, T* arg)
{
    if (nullptr != node)
    {
        find_all_rec(node->m_children[LEFT], is_match, arg); 
        if (TRUE == is_match(*(node->m_data), *arg))
        {
            // TODO: exception
            m_find_all.push_back(node->m_data);
        }

        find_all_rec(node->m_children[RIGHT], is_match, arg);  
    }

    return (SUCCESS);    
}
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
    node->m_height = MAX(left_child_height, right_child_height) + 1;
}

template <typename T>
AVL_node<T>* AVL<T>::rotate_left(AVL_node<T> *node)
{
    /* node is the unbalanced node */

    /* pivot node for rotation right */
    AVL_node<T>* pivot_node = nullptr;
    assert(node);
    pivot_node = node->m_children[RIGHT];

    /* unbalanced node is detached from pivot node and attached to pivots
     * left child */
    node->m_children[RIGHT] = node->m_children[RIGHT]->m_children[LEFT];

    /* pivot node left is attached to unbalanced node */ 
    pivot_node->m_children[LEFT] = node; 

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

    pivot_node = node->m_children[LEFT];

    /* unbalanced node is detached from pivot node and attached to pivots
     * right child */
    node->m_children[LEFT] = node->m_children[LEFT]->m_children[RIGHT];
                             
    /* pivot node right is attached to unbalanced node */ 
    pivot_node->m_children[RIGHT] = node;

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
        0 <= node_balance_factor(node->m_children[LEFT]))
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
        0 > node_balance_factor(node->m_children[LEFT]))
        {
        /* first balance nodes left child by rotating it to the left and then
         * it is just a < Left Left case> */ 
        node->m_children[LEFT] = rotate_left(node->m_children[LEFT]);
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
         0 >= node_balance_factor(node->m_children[LEFT]))
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
        0 < node_balance_factor(node->m_children[LEFT]))
        {
            node->m_children[RIGHT] = rotate_right(node->m_children[RIGHT]);
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
void AVL<T>::height_of_nodes_children(AVL_node<T>* node, size_t* left,size_t* right)
{
    assert(node);
    assert(right);
    assert(left);

    /* Store the height of right child if there is one */
    if (nullptr != node->m_children[RIGHT])
    {
        *right = node->m_children[RIGHT]->m_height;
    }

    /* Store the height of left child if there is one */
    if (nullptr != node->m_children[LEFT])
    {
        *left = node->m_children[LEFT]->m_height;
    }
}


/*============================================================================*/
/*                               Auxiliary functions                          */
/*============================================================================*/

template <typename T>
int AVL<T>::overwrite_node(AVL_node<T>* node, AVL_node<T>* node_next)
{
    node->m_data = node_next->m_data;
    node->m_children[RIGHT] = node_next->m_children[RIGHT];
    node->m_children[LEFT] = node_next->m_children[LEFT];
}

template <typename T>
int AVL<T>::has_only_one_child(AVL_node<T>* node)
{
    assert(node);
    return ((nullptr == node->m_children[LEFT] || nullptr == node->m_children[RIGHT]));
}

template <typename T>
int AVL<T>::find_only_child_path(AVL_node<T>* node)
{
    assert(node);
    return (nullptr == node->m_children[LEFT]);
}

template <typename T>
int AVL<T>::is_leaf(AVL_node<T>* node)
{
    assert(node);
    return (nullptr == node->m_children[LEFT] && nullptr == node->m_children[RIGHT]);
}

template <typename T>
AVL_node<T>* AVL<T>::node_next(AVL_node<T>* node)
{
    assert(node);
    if (nullptr == node->m_children[LEFT])
    {
        return (node);
    }

    return (node_next(node->m_children[LEFT]));
}

} // namespace hrd9
#endif // _AVL_TREE_


