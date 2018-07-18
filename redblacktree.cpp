#include <iostream>
#include "redblacktree.h"
using namespace std;


RedBlackTree::RedBlackTree()
        : root(NULL)
{
}

RedBlackTree::~RedBlackTree()
{
    DeleteNode(root);
}

void RedBlackTree::Insert(int key, int value)
{
    Node *temp = root;
    Node *uncle;
    Node *grandparent;

    bool recheck = true;

    int curr_loc;
    int parent_loc;

    Node *new_node = new Node;

    if(!root){ //if the root does not exist
        root = new Node;
        root->value = value;
        root->key = key;
        root->parent = nullptr;
        root->color = BLACK;
        root->left = nullptr;
        root->right = nullptr;
    }
    else {
        while (temp->left != nullptr || temp->right != nullptr) { //stops when the children (@ leaves) are nullptr
            if (value < temp->value) {
                temp = temp->left;
            } else if (value > temp->value) {
                temp = temp->right;
            }
        }

        Node *prev; //contains the parent node
        //new values inputted will always start off as red
        if (value < temp->value) {
            temp->left = new Node;
            prev = temp;
            temp = temp->left;

            temp->value = value;
            temp->key = key;
            temp->parent = prev;
            temp->color = RED;
            temp->left = nullptr;
            temp->right = nullptr;

        } else if (value > temp->value) {
            temp->right = new Node;
            prev = temp;
            temp = temp->right;

            temp->value = value;
            temp->key = key;
            temp->parent = prev;
            temp->color = RED;
            temp->left = nullptr;
            temp->right = nullptr;
        }

        /* Node *prev = temp;
         int prev_loc = 0;
         while (temp != nullptr) { //stops when the children (@ leaves) are nullptr
             prev = temp;
             if (value < temp->value) {
                 temp = temp->left;
                 prev_loc = 1;
             } else if (value > temp->value) {
                 temp = temp->right;
                 prev_loc = 0;
             }
         }
         if (prev_loc == 1) {
             prev->left = new_node;
         } else {
             prev->right = new_node;
         } */

        /* insert_helper(temp, temp, value, key); //inserts a value into
             temp->parent = temp;
             temp->color = RED; */

        int dir = 0; //left=1 and right=2

        while (recheck) {
            if (temp->parent != root) {
                if (temp->parent->color == RED) { //parent cannot be RED
                    //check to see if the uncle is red by going backward through the parents
                    //have to find which side is uncle is with respect to the parent
                    //have to find which side child (current node) is with respect to the parent
                    grandparent = temp->parent->parent;

                    if (grandparent->left && grandparent->right) { //if both the parent and uncle exist
                        if (grandparent->left == temp->parent) {
                            dir = 1;
                            uncle = grandparent->right;
                        } else if (grandparent->right == temp->parent) {
                            dir = 0;
                            uncle = grandparent->left;
                        }
                        if (uncle->color == RED) {
                            //recolor parent and uncle to red
                            //recolor grandparent to red
                            //make curr node = grandparent
                            if (grandparent != root) { //root cannot be colored to red
                                grandparent->color = RED;
                            }
                            temp->parent->color = BLACK;
                            uncle->color = BLACK;
                        } else if (uncle->color == BLACK) { //uncle is red
                            if (dir == 1) { //looking at left side of grandparent
                                if (temp == temp->parent->left) { //left-left case
                                    RotateRight(grandparent);
                                    color_swap(grandparent, temp->parent);//swap the colors of grandparent and parent
                                } else if (temp == temp->parent->right) { //left-right case
                                    RotateLeft(temp->parent);
                                    RotateRight(grandparent);
                                    color_swap(grandparent, temp->parent);
                                }
                            } else if (dir == 0) { //looking at right side of grandparent
                                if (temp == temp->parent->right) { //right-right case
                                    RotateLeft(grandparent);
                                    color_swap(grandparent, temp->parent);
                                } else if (temp == temp->parent->left) { //right-left case
                                    RotateRight(temp->parent);
                                    RotateLeft(grandparent);
                                    color_swap(grandparent, temp->parent);
                                }
                            }
                        }

                    } else { //only the parent exists (including the grandparent)
                        //parent moves to place of grandparent and grandparent becomes child of parent
                        //swap colors of old grandparent and old parent
                        if (temp->parent == grandparent->left) {
                            RotateRight(grandparent);
                            color_swap(grandparent, temp->parent);
                        } else if (temp->parent == grandparent->right) {
                            RotateLeft(grandparent);
                            color_swap(grandparent, temp->parent);
                        }
                    }
                    if(grandparent->parent){
                    if(grandparent->parent->color == grandparent->color){// && grandparent->parent->color == RED){
                        temp = grandparent;
                        recheck = true;
                    }
                    else{
                        recheck = false;
                    }
                    }
                }
                else{
                    break;
                }
            }
            else{
                break;
            }


        }
        }
}

void RedBlackTree::color_swap(Node* first, Node* second){
        Color store;
        store = first->color;
        first->color = second->color;
        second->color = store;
}

int RedBlackTree::Search(int key)
{
    Node *node = root;
    while (node)
    {
        if (node->key < key)
        {
            node = node->left;
        }
        else if (node->key > key)
        {
            node = node->right;
        }
        else
        {
            return node->value;
        }
    }

    throw std::runtime_error("Key not found");
}

void RedBlackTree::Delete(const int key)
{
    Node *node = root;
    while (node)
    {
        if (node->key > key)
        {
            node = node->left;
        }
        else if (node->key < key)
        {
            node = node->right;
        }
        else
        {
            break;
        }
    }

    if (!node || node->key != key)
    {
        return;
    }

    Color original;
    Node *sub, *old;
    if (!node->left)
    {
        Remove(node, sub = node->right);
    }
    else if (!node->right)
    {
        Remove(node, sub = node->left);
    }
    else
    {
        old = node->right;
        while (old->left)
        {
            old = old->left;
        }
        original = old->color;
        sub = old->right;

        if (old->parent == node)
        {
            sub->parent = node;
        }
        else
        {
            Remove(old, old->right);
            old->right = node->right;
            old->right->parent = old;
        }

        Remove(node, old);
        old->left = node->left;
        old->left->parent = old;
        old->color = node->color;
    }

    delete node;
    if (original == BLACK)
    {
        bool side;
        Node *sibling;
        while (old != root && old->color == BLACK)
        {
            if ((side = (old == old->parent->left)))
            {
                sibling = old->parent->right;
            }
            else
            {
                sibling = old->parent->left;
            }

            if (sibling->color == RED)
            {
                sibling->color = BLACK;
                old->parent->color = RED;
                side ? RotateLeft(old->parent) : RotateRight(old->parent);
                sibling = side ? old->parent->right : old->parent->left;
            }

            if (sibling->left->color == BLACK && sibling->right->color == RED)
            {
                sibling->color = RED;
                old = old->parent;
            }
            else
            {
                if (BLACK == side ? sibling->right->color : sibling->left->color)
                {
                    sibling->color = RED;
                    if (side)
                    {
                        sibling->left->color = BLACK;
                        RotateRight(sibling);
                        sibling = old->parent->right;
                    }
                    else
                    {
                        sibling->right->color = BLACK;
                        RotateLeft(sibling);
                        sibling = old->parent->left;
                    }
                }

                sibling->color = old->parent->color;
                old->parent->color = BLACK;
                if (side)
                {
                    sibling->left->color = BLACK;
                    RotateLeft(old->parent);
                }
                else
                {
                    sibling->right->color = BLACK;
                    RotateRight(old->parent);
                }

                old = root;
            }
        }
    }
}

void RedBlackTree::Display()
{
    DisplaySubTree(root, 0);
}

void RedBlackTree::RotateLeft(Node *x)
{
    Node *y;

    y = x->right;
    x->right = y->left;
    if (y->left)
    {
        y->left->parent = x;
    }

    y->parent = x->parent;
    y->left = x;

    if (!x->parent)
    {
        root = y;
    }
    else if (x == x->parent->left)
    {
        x->parent->left = y;
    }
    else
    {
        x->parent->right = y;
    }
    x->parent = y;
}

void RedBlackTree::RotateRight(Node *y)
{
    Node *x;

    x = y->left;
    y->left = x->right;
    if (x->right)
    {
        x->right->parent = y;
    }

    x->parent = y->parent;
    x->right = y;

    if (!y->parent)
    {
        root = x;
    }
    else if (y == y->parent->left)
    {
        y->parent->left = x;
    }
    else
    {
        y->parent->right = x;
    }

    y->parent = x;
}

void RedBlackTree::Remove(Node *dest, Node *src)
{
    if (dest->parent == NULL)
    {
        root = src;
    }
    else if (dest == dest->parent->left)
    {
        dest->parent->left = src;
    }
    else
    {
        dest->parent->right = src;
    }

    if (src)
    {
        src->parent = dest->parent;
    }
}



void RedBlackTree::DisplaySubTree(Node *node, int tabs)
{
    if (!node)
    {
        return;
    }

    DisplaySubTree(node->left, tabs + 1);

    for (int i = 0; i < tabs; ++i)
    {
        std::cout << "\t\t";
    }
    std::cout << node->key << (node->color ? "B" : "R") << std::endl;

    DisplaySubTree(node->right, tabs + 1);
}

void RedBlackTree::DeleteNode(Node *node)
{
    if (!node)
    {
        return;
    }

    if (node->left)
    {
        DeleteNode(node->left);
    }

    if (node->right)
    {
        DeleteNode(node->right);
    }

    delete node;
}

void RedBlackTree::insert_helper(Node *prev, Node *pointer, int val, int key){

    if(pointer != root && pointer == nullptr){
        if(prev->value > val){
            prev->left= new Node;
            prev->value = val;
            prev->key = key;
        }
        else if(prev->value <val){
            prev->right= new Node;
            prev->value = val;
            prev->key = key;
        }
    }
    else {
        if (val < pointer->value) {
            insert_helper(pointer, pointer->left, val, key); //pointer->left =
        } else if (val > pointer->value) {
            insert_helper(pointer, pointer->right, val, key); //pointer->right =
        }
    }
}