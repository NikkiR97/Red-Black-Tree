//
// Created by Nikkitha on 3/9/2018.
//

#ifndef REDBLACKTREE_H
#define REDBLACKTREE_H

class RedBlackTree
{
public:
    RedBlackTree();
    ~RedBlackTree();
    /**
     * @brief Insert
     * @param key - the nodes are sorted by key
     * @param value - the value of the node
     *
     * THIS FUNCTION IS NOT IMPLEMENTED. YOU ARE TO IMPLEMENT IT.
     * This function inserts a new node with key=@param key and value =@param value into the red-black tree.
     * The new node should be inserted as a red node and then the tree should be fixed.
     */
    void Insert(const int key, const int value);
    /**
     * @brief Search
     * @param key - searches by key
     * @return
     * This function searches for nodes by key
     */
    int Search(const int key);
    /**
     * @brief Delete
     * @param key
     * Deletes a node by key, and re-balances the tree
     */
    void Delete(const int key);
    /**
     * @brief Display
     * Displays the red-black tree.
     */
    void Display();
private:
    enum Color
    {
        RED,
        BLACK
    };

    struct Node
    {
        Color color;
        int key;
        int value;
        Node *parent;
        Node *left;
        Node *right;
    };

    Node *root;
//This are helper functions that you can use if needed.
    void RotateLeft(Node *x);
    void RotateRight(Node *y);
    void Remove(Node *dest, Node *src);
    void DisplaySubTree(Node *node, int tabs);
    void DeleteNode(Node *node);

    void insert_helper(Node *prev, Node *pointer, int val, int key);

    void color_swap(Node* first, Node* second);
};

#endif //HW2_130_REDBLACKTREE_H
