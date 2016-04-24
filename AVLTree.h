/*
 * CSCI-2421: Data Structures and Program Design
 * University of Colorado Denver
 * AVL Tree Base Implementation.
 */
#ifndef AVLTREE_H
#define AVLTREE_H

#include <iostream>
#include <string>
#include <vector>
#include "itemtype.h"
#include "AVLNode.h"

/* Forward declaration of the AVLNode class used within this AVL tree. */
class AVLNode;

/*
 * Standard implementation of an AVL (self-balancing) binary search tree.
 * This implementation is based on the standard process of inserting or
 * deleting elements from the tree and the propigating the changes in
 * height through a rebalance function. This rebalance function uses the
 * typical set of four rotation operations to ensure the AVL height
 * constraint is preserved: the height of the tree differs by no more than
 * one in any sub-tree.
 */
class AVLTree {
    /* Balance constants for left and right heavy tree weight. */
    const static int LEFT_HEAVY = -2;
    const static int BALANCED = 0;
    const static int RIGHT_HEAVY = 2;

public:
    /* Creates an empty AVL tree with size and height = 0. */
    AVLTree();

    /* Creates a copy of the provided tree. */
    AVLTree(const AVLTree& tree);

    /* 
     * Ensures that all of the AVLNodes within the tree are deleted using the
     * recursive destructor idiom. Every AVLNode is responsible for deleting
     * its own children.
     */
    virtual ~AVLTree();

    /*
     * Clear the current tree and copy the entire structure from tree into
     * this tree. All data within this tree will be erased.
     *
     * @param tree - The tree structure to be copied.
     */
    bool copyTree(const AVLTree& tree);

    /*
     * Adds all the nodes following the starting node to a vector
     */
    std::vector<ItemType> &addVector(std::vector<ItemType> &vec);

    /*
     * Insert the provided data value into this AVL tree. As the value is
     * inserted into this tree, the tree will have to be rebalanced to ensure
     * the balance constraints of the AVL data structure. After this operation
     * the trees height will not differ by more than one level and the balance
     * factor will not be more than 1 or less than -1.
     *
     * @param data - The data that will be inserted into the tree as the key.
     */
    bool insert(ItemType data);

    /*
     * Remove the data element from this AVL tree. The data element will be
     * found within the tree and subsequently removed. After the removal,
     * the tree will be rebalanced until the balance constrains of the AVL
     * data structure are met. After this operation the trees height will
     * not differ by more than one level and the balance factor will not be
     * more than 1 or less than -1.
     */
    bool remove(ItemType data);

    /*
     * Locate the data element from this AVL tree. The data element will be
     * found within the tree and returned as a reference to the data type.
     * Throws exceptions for empty tree and item not found.
     */
    ItemType &locate(ItemType data);

    /*
     * Clear the tree by removing all data elements. This function extensively
     * uses the recursive destructor call sequence to ensure that all AVLNodes
     * from the bottom up are destroyed. The size and height of the tree
     * after this operation will be 0. Returns true if successful.
     */
    bool clearTree();

    /*
     * Utility function for printing the balance values of every AVLNode within
     * this AVL tree. This function can be used to ensure that the tree is
     * properly balanced by not containing any balance factor greater than 1
     * or less than -1. Returns true if successful.
     */
    bool printBalance();

    /*
     * Returns the height of the largest depth within the tree. This function
     * recursively iterates through the tree to determine the largest depth
     * which is returned as the height of the tree.
     */
    unsigned int height() const;

    /*
     * Returns the number of AVLNodes (or keys) within this AVL tree. This number
     * simply represents how many items have been inserted/copied into the tree.
     */
    unsigned int size() const;

    /*
     * The following functions provide simple binary search tree traversals that
     * return the pre, in, and post orderings of the internal data.
     */
    std::string preorder() const;
    std::string inorder() const;
    std::string postorder() const;

    /*
     * Returns the string representation of this AVL tree as the inorder traversal
     * of the internal data.
     */
    std::string toString() const;

    /*
     * Allows this AVL tree to be assigned to another tree. This has the same effect
     * as copying the internal tree structure.
     *
     * @param tree - The tree that will be copied.
     */
    AVLTree& operator = (const AVLTree& tree);

    /*
     * Insertion operator for inserting the inorder string representation of this AVL
     * tree into the provided stream.
     *
     * @param out - The output stream.
     * @param tree - The tree to insert.
     */
    friend std::ostream& operator << (std::ostream& out, const AVLTree& tree);

protected:
    /*
     * Recursive support function for to add nodes to a vector.
     */
    std::vector<ItemType> &addVector(AVLNode *node, std::vector<ItemType> &vec);

    /*
     * Recursive support function. Returns the height of the sub-tree starting
     * at AVLNode. If AVLNode is a nullptr, the sub-tree height is 0. Non-const version
     * used internally by the rebalance function.
     *
     * @param AVLNode - The current AVLNode.
     */
    unsigned int height(AVLNode* AVLNode);

    /*
     * Recursive support function. This is the main rebalancing function of the
     * AVL tree implementation. This function takes the current AVLNode-based sub-tree
     * and uses the four AVL rotation functions to rebalance the tree after
     * an insertion or deletion operation.
     *
     * @param AVLNode - The root of the sub-tree to balance.
     */
    void rebalance(AVLNode* AVLNode);

    /*
     * Computes the balance of the provided AVLNode based on the height of the 
     * sub-trees connected to AVLNode. If the balance is less than or equal to 
     * LEFT_HEAVY, then the sub-tree is left heavy and needs rebalanced. Similarly,
     * if the balance is greater than or equal to RIGHT_HEAVY, then the sub-tree
     * is right heavy and needs rebalanced.
     *
     * @param AVLNode - The current AVLNode.
     */
    bool setBalance(AVLNode* AVLNode);

    /*
     * Recursive support function. Prints the balance of the provided AVLNode. This
     * is essentially an inorder traversal of the balance values stored by all
     * of the AVLNodes.
     * 
     * @param AVLNode - The current AVLNode.
     */
    void printBalance(AVLNode* AVLNode);

    /*
     * Recursive support function. Returns the height of the sub-tree starting 
     * at AVLNode. If AVLNode is a nullptr, the sub-tree height is 0. This is the
     * const version used for the public height function.
     *
     * @param AVLNode - The current AVLNode.
     */
    unsigned int height(AVLNode* AVLNode) const;

    /*
     * Recursive support function. Keeps a running total of the number of AVLNodes
     * that have been visited in the inorder traversal. The count is by reference
     * and will store the total AVLNode count when complete.
     * 
     * @param AVLNode - The current AVLNode.
     * @param count - The current total number of AVLNodes visited.
     */
    void size(AVLNode* AVLNode, unsigned int& count) const;

    /*
     * Recursive support functions. The following functions provide the recursive
     * implementations of the pre, in, and post order traversals of the tree.
     *
     * @param out - The current string represetnation being built.
     * @param AVLNode - The current AVLNode.
     */
    void preorder(std::stringstream& out, AVLNode* AVLNode) const;
    void inorder(std::stringstream& out, AVLNode* AVLNode) const;
    void postorder(std::stringstream& out, AVLNode* AVLNode) const;
    
    /*
     * The following functions implement the main AVL tree rotation functions.
     * Each is defined by their well known definitions based on the simple
     * left or right rotations, or the compound left-then-right and
     * right-then-left compound rotations. Each function returns the new
     * root that resulted from the rotation. These functions losely follow the
     * guide provided at: http://www.cise.ufl.edu/~nemo/cop3530/AVL-Tree-Rotations.pdf
     *
     * @param AVLNode - The current sub-tree AVLNode to perform the rotation on.
     * @return The root of the newly rotated sub-tree.
     */
    AVLNode* rotateLeft(AVLNode* AVLNode);
    AVLNode* rotateRight(AVLNode* AVLNode);
    AVLNode* rotateLeftRight(AVLNode* AVLNode);
    AVLNode* rotateRightLeft(AVLNode* AVLNode);

    /*
     * Recursive support function. Recursively copys the sub-tree
     * and returns a pointer to the new parent AVLNode.
     * 
     * @param AVLNode - The sub-tree root to be copied.
     * @return New parent AVLNode
     */
    AVLNode* copySubtree(AVLNode* AVLNode);

protected:
    AVLNode* root;
};

#endif
