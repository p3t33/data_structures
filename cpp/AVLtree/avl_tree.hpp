#ifndef _AVL_TREE_
#define _AVL_TREE_

/*******************************************************************************
*                          AVL tree
*                   =====================
* File Name: avl_tree.hpp
* Related files: avl_tree.cpp avl_tree_test.hpp
* #Version: V 1.0
* Writer: Kobi Medrish       
* Created: 4.11.19
* Last update: 3.11.19
*******************************************************************************/
#include <stddef.h> // size_t
#include <functional> // using
#include <vector> // vector


namespace med
{

template <typename T>
class AVL_node
{
    private:
        enum children {LEFT, RIGHT};

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
            m_height = other->m_height;
            m_children[RIGHT] = other->m_children[RIGHT];
            m_children[LEFT] = other->m_children[LEFT];    
        }
    
        T* m_data;
        size_t m_height;
        struct AVL_node* m_children[2];
};


template <typename T>
class AVL
{
    private:
        using compare_t = std::function<int(const T& data1, const T& data2)>;
        using action_func_t = std::function<int(const T& data)>;
        using is_match_t = std::function<int(const T& data, const T& arg)>;

        enum children {LEFT, RIGHT};

        static const int success = 0;
        static const int zero = 0;

    public:
        AVL(compare_t CompareFunc);
        ~AVL();

        // Interface / API
        // ------------------------------------------------------------------
        int insert(T* data);
        void remove(T* data);
        T* find(const T* data);
        size_t count();
        int is_empty();
        size_t height();
        int for_each(action_func_t action_func);
        int find_all(is_match_t is_match, T* arg);
        void remove_all(is_match_t is_match, T* arg);

        std::vector<T*>& get_vector();
        // ------------------------------------------------------------------

    private:
        // Auxilary recursive functions
        // ------------------------------------------------------------------
        void destroy_recursive(AVL_node<T>* node); // destory 
        size_t count_recursive(AVL_node<T>* node); // count

        // for_each
        int for_each_recursive(AVL_node<T>* node, action_func_t action_func); 
        
        // remove
        AVL_node<T> *remove_recursive(AVL_node<T>* node, T* data); 
        AVL_node<T> *remove_node(AVL_node<T>* node);

        AVL_node<T>* insert_recursive(AVL_node<T>* node, T* data); // insert 
        T* find_recursive(AVL_node<T>* node, const T* data); // find 

        // find_all
        int find_all_rec(AVL_node<T>* node, is_match_t is_match, T* arg);

        // remove_all
        int remove_all_rec(AVL_node<T>* node, is_match_t is_match, T* arg);
        // ------------------------------------------------------------------

        // Auxiliary general functions
        // ------------------------------------------------------------------
        //TODO: where to implement and what about dereference of &
        inline int max_hight(size_t& first_num, size_t& second_num)
        {
            return (((first_num > second_num) ? first_num : second_num) + 1);    
        }

        void destroy_node(AVL_node<T>* node); // done
        int has_only_one_child(AVL_node<T>* node); // done
        int find_only_child_path(AVL_node<T>* node); // done
        int is_leaf(AVL_node<T>* node); // done
        AVL_node<T>* node_next(AVL_node<T>* node); // done
        void height_of_nodes_children(AVL_node<T>* node,
                                      size_t* left,
                                      size_t* right); // done
        // -----------------------------------------------------------------

        // Balancing functions
        // ------------------------------------------------------------------
        void update_node_hight(AVL_node<T> *node);
        AVL_node<T> *rotate_left(AVL_node<T> *node);
        AVL_node<T> *rotate_right(AVL_node<T> *node);
        AVL_node<T> *rebalance_node(AVL_node<T> *node);
        int node_balance_factor(AVL_node<T>* node);
        // ------------------------------------------------------------------


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

/*                                                          destroy_recursive */
/*                                                          ~~~~~~~~~~~~~~~~~ */
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

/*                                                               destroy_node */
/*                                                               ~~~~~~~~~~~~ */
template <typename T>
void AVL<T>::destroy_node(AVL_node<T>* node)
{

    //TODO: exception

    delete node;
    node = nullptr; 
}

/*============================================================================*/
/*                               ~~~~~~~~~~~~~~~~                             */
/*                               member functions                             */
/*                               ~~~~~~~~~~~~~~~~                             */

/*============================================================================*/
/*                     API functions / Public member functions                */
/*============================================================================*/
/*                                                                      count */
/*                                                                      ~~~~~ */
template <typename T>
size_t AVL<T>::count()
{
    return (count_recursive(m_root));
}

/*--------------------------------------------------------------------------- */
/*                          Auxiliary functions for count                     */
/*--------------------------------------------------------------------------- */
/*                                                            count_recursive */
/*                                                            ~~~~~~~~~~~~~~~ */
template <typename T>
size_t AVL<T>::count_recursive(AVL_node<T>* node)
{
    if (nullptr == node)
    {
        return(success);       
    }
    
    /* Preorder: Root-Left-Right */
    return (1 + 
            count_recursive(node->m_children[LEFT]) + 
            count_recursive(node->m_children[RIGHT]));
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                                                                   is_empty */
/*                                                                   ~~~~~~~~ */
template <typename T>
int AVL<T>::is_empty()
{
    return (nullptr == m_root);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                                                                     height */
/*                                                                     ~~~~~~ */
// TODO not sure about implementaiton
template <typename T>
size_t AVL<T>::height()
{
    if (true == is_empty())
    {
        return (0);
    }

    return (m_root->m_height);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                                                                     insert */
/*                                                                     ~~~~~~ */
template <typename T>
int AVL<T>::insert(T* data)
{
    if (true == is_empty())
    {
        // TODO: exception
        m_root = new AVL_node<T>(data);
    }
    else
    {
        m_root = insert_recursive(m_root, data);
    }
    
    return (success);
}

/*--------------------------------------------------------------------------- */
/*                          Auxiliary functions for insert                    */
/*--------------------------------------------------------------------------- */
/*                                                           insert_recursive */
/*                                                           ~~~~~~~~~~~~~~~~ */
template <typename T>
AVL_node<T>* AVL<T>::insert_recursive(AVL_node<T>* node, T* data)
{
    int path = 0, difference = 0;

    difference = m_CompareFunc(*data, *(node->m_data));

    /* if data to be inserted is same as the data at the tree */
    // TODO: return status
    if (zero == difference)
    {
        return (node);
    }

    /* if data to be inserted is greater then the data it is compared with
     * go RIGHT if smaller go LEFT */
    path = (difference > zero ? RIGHT : LEFT);

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

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                                                                   for_each */
/*                                                                   ~~~~~~~~ */
template <typename T>
int AVL<T>::for_each(action_func_t action_func)
{
    return (for_each_recursive(m_root, action_func));
}

/*--------------------------------------------------------------------------- */
/*                       Auxiliary functions for insfor_eachert               */
/*--------------------------------------------------------------------------- */
/*                                                         for_each_recursive */
/*                                                         ~~~~~~~~~~~~~~~~~~ */
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

    return (success);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                                                                       find */
/*                                                                       ~~~~ */
template <typename T>
T* AVL<T>::find(const T* data)
{
    // TODO: exception
    return (find_recursive(m_root, data));
}

/*--------------------------------------------------------------------------- */
/*                             Auxiliary functions find                       */
/*--------------------------------------------------------------------------- */
/*                                                             find_recursive */
/*                                                             ~~~~~~~~~~~~~~ */
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
    if(zero == deffrance)
    {
        return (node->m_data);
    }

    /* in case data provided for the search is smaller or bigger then the data
     * at the node there is a need to decide which path to take to procide the
     * search */ 
    path = (deffrance > zero ? RIGHT : LEFT);
    
    /* if the path is a "dead end" then data is not in the tree */
    if (nullptr == node->m_children[path])
    {
        return nullptr;
    }

    /* Search will continue in accordance to the chosen path */ 
    return (find_recursive(node->m_children[path], data));
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                                                                     remove */
/*                                                                     ~~~~~~ */
template <typename T>
void AVL<T>::remove(T* data)
{
    m_root = remove_recursive(m_root, data);
}

/*--------------------------------------------------------------------------- */
/*                             Auxiliary functions remove                     */
/*--------------------------------------------------------------------------- */
/*                                                           remove_recursive */
/*                                                           ~~~~~~~~~~~~~~~~ */
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
    if (zero != deffrance)
    {
        path = (deffrance > zero ? RIGHT : LEFT);

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

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                                                                 remove_all */
/*                                                                 ~~~~~~~~~~ */
template <typename T>
void AVL<T>::remove_all(is_match_t is_match, T* arg)
{
    remove_all_rec(m_root, is_match, arg);
}

/*--------------------------------------------------------------------------- */
/*                             Auxiliary functions remove_all                 */
/*--------------------------------------------------------------------------- */
/*                                                             remove_all_rec */
/*                                                             ~~~~~~~~~~~~~~ */
template <typename T>
int AVL<T>::remove_all_rec(AVL_node<T>* node, is_match_t is_match, T* arg)
{

    if (nullptr != node)
    {
        remove_all_rec(node->m_children[RIGHT], is_match, arg); 
        remove_all_rec(node->m_children[LEFT], is_match, arg);  
        if (true == is_match(*(node->m_data), *arg))
        {
            remove(node->m_data);
        }
    }
    return (success);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                                                                remove_node */
/*                                                                ~~~~~~~~~~~ */
template <typename T>
AVL_node<T>* AVL<T>::remove_node(AVL_node<T>* node)
{
    //int path = 0;
    AVL_node<T>* disposable_node = nullptr;

    /* in case there is no children */
    if (true == is_leaf(node))
    {
        destroy_node(node);  
        return (nullptr);  
    }

    else if (true == has_only_one_child(node))
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

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                                                                   find_all */
/*                                                                   ~~~~~~~~ */
template <typename T>
int AVL<T>::find_all(is_match_t is_match, T *arg)
{
    return (find_all_rec(m_root, is_match, arg));
}

/*--------------------------------------------------------------------------- */
/*                             Auxiliary functions find_all                   */
/*--------------------------------------------------------------------------- */
/*                                                               find_all_rec */
/*                                                               ~~~~~~~~~~~~ */
template <typename T>
int AVL<T>::find_all_rec(AVL_node<T>* node, is_match_t is_match, T* arg)
{
    if (nullptr != node)
    {
        find_all_rec(node->m_children[LEFT], is_match, arg); 
        if (true == is_match(*(node->m_data), *arg))
        {
            // TODO: exception
            m_find_all.push_back(node->m_data);
        }

        find_all_rec(node->m_children[RIGHT], is_match, arg);  
    }

    return (success);    
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                                                                 get_vector */
/*                                                                 ~~~~~~~~~~ */
template <typename T>
std::vector<T*>& AVL<T>::get_vector()
{
    return (m_find_all);
}

/*============================================================================*/
/*                               Balancing functions                          */
/*============================================================================*/
/*                                                          update_node_hight */
/*                                                          ~~~~~~~~~~~~~~~~~ */
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

    node->m_height = max_hight(left_child_height, right_child_height);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                                                                rotate_left */
/*                                                                ~~~~~~~~~~~ */
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

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                                                               rotate_right */
/*                                                               ~~~~~~~~~~~~ */
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

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                                                             rebalance_node */
/*                                                             ~~~~~~~~~~~~~~ */
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

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                                                        node_balance_factor */
/*                                                        ~~~~~~~~~~~~~~~~~~~ */
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

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                                                   height_of_nodes_children */
/*                                                   ~~~~~~~~~~~~~~~~~~~~~~~~ */
template <typename T>
void AVL<T>::height_of_nodes_children(AVL_node<T>* node,
                                      size_t* left,
                                      size_t* right)
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
/*                                                         has_only_one_child */
/*                                                         ~~~~~~~~~~~~~~~~~~ */
template <typename T>
int AVL<T>::has_only_one_child(AVL_node<T>* node)
{
    assert(node);
    return ((nullptr == node->m_children[LEFT] || 
             nullptr == node->m_children[RIGHT]));
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                                                       find_only_child_path */
/*                                                       ~~~~~~~~~~~~~~~~~~~~ */
template <typename T>
int AVL<T>::find_only_child_path(AVL_node<T>* node)
{
    assert(node);
    return (nullptr == node->m_children[LEFT]);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                                                                    is_leaf */
/*                                                                    ~~~~~~~ */
template <typename T>
int AVL<T>::is_leaf(AVL_node<T>* node)
{
    assert(node);
    return (nullptr == node->m_children[LEFT] && 
            nullptr == node->m_children[RIGHT]);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                                                                  node_next */
/*                                                                  ~~~~~~~~~ */
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
