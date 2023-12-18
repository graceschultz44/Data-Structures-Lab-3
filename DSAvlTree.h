#ifndef DSAVL_TREE_H
#define DSAVL_TREE_H
#define DEBUG
#include <stdexcept>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <map>

// Template class for a node in an AVL tree
template <typename Comparable, typename Value>
class DSAvlTree
{
private:
    // Nested struct representing a node in the AVL tree
    struct DSAvlNode
    {
        Comparable key;               // The key value of the node
        DSAvlNode *left;              // Pointer to the left child
        DSAvlNode *right;             // Pointer to the right child
        int height;                   // Height of the node
        std::map<Value, int> mapVals; // Map to store associated values and their counts

        // Constructor for node with key, left and right children, and height
        DSAvlNode(const Comparable &theKey, DSAvlNode *lt, DSAvlNode *rt, int h)
            : key{theKey}, left{lt}, right{rt}, height{h} {}

        // Constructor for node with key, value, left and right children, and height
        DSAvlNode(const Comparable &theKey, Value v, DSAvlNode *lt, DSAvlNode *rt, int h)
            : key{theKey}, left{lt}, right{rt}, height{h}
        {
            mapVals.emplace(v, 1);
        }
    };

    DSAvlNode *root; // Root node of the AVL tree
    int size;        // Size of the AVL tree (number of nodes)

public:
    // Default constructor
    DSAvlTree() : root{nullptr}, size{0} {}

    // Copy constructor
    DSAvlTree(const DSAvlTree &rhs) : root{nullptr}
    {
        root = clone(rhs.root);
    }

    // Destructor
    ~DSAvlTree()
    {
        makeEmpty();
    }

    // Assignment operator
    DSAvlTree &operator=(const DSAvlTree &rhs)
    {
        makeEmpty();
        root = clone(rhs.root);
        return *this;
    }

    // Check if a key is contained in the tree
    std::map<Value, int> contains(const Comparable &x) const
    {
        return contains(x, root);
    }

    // Check if the tree is empty
    bool isEmpty() const
    {
        return root == nullptr;
    }

    // Make the tree empty
    void makeEmpty()
    {
        makeEmpty(root);
        root = nullptr;
        size = 0;
    }

    // Insert a key-value pair into the tree
    void insert(const Comparable &x, const Value &v)
    {
        insert(x, v, root);
    }

    // Insert a key-value pair with a specific count into the tree
    void insert(const Comparable &x, const Value &v, const int &a)
    {
        insert(x, v, a, root);
    }

    // Remove a key from the tree
    void remove(const Comparable &x)
    {
        remove(x, root);
    }

    // Get the size of the tree
    int getSize()
    {
        return size;
    }

    // Print the tree structure to an output stream
    void printTree(std::ostream &out)
    {
        printTree(out, root);
    }

private:
    // Private methods for various operations like insertion, removal, balancing, etc.

    // Insert a key-value pair into a subtree
    void insert(const Comparable &x, const Value &v, DSAvlNode *&t)
    {
        // Insert logic with balancing
        if (t == nullptr)
        {
            t = new DSAvlNode{x, v, nullptr, nullptr, 0}; // insert new node and increment size
            size++;
        }
        else if (x < t->key)
        {
            insert(x, v, t->left); // call recursively
        }
        else if (t->key < x)
        {
            insert(x, v, t->right); // call recursively
        }
        else
        {
            if (t->mapVals.find(v) == t->mapVals.end()) // if it's not in the tree, set frequency to 1
            {
                t->mapVals[v] = 1;
            }
            else
            {
                t->mapVals[v] += 1; // otherwise, increment frequency
            }
            return;
        }
        balance(t); // balance the tree
    }

    // Insert a key-value pair with count into a subtree
    void insert(const Comparable &x, const Value &v, const int &a, DSAvlNode *&t)
    {
        // Insert logic with count and balancing
        if (t == nullptr)
        {
            t = new DSAvlNode{x, v, nullptr, nullptr, 0}; // add a new node with a given frequency and increment size
            t->mapVals[v] = a;
            size++;
        }
        else if (x < t->key)
        {
            insert(x, v, a, t->left); // call recursively
        }
        else if (t->key < x)
        {
            insert(x, v, a, t->right); // call recursively
        }
        else
        {
            if (t->mapVals.find(v) == t->mapVals.end()) // if not in there, set the frequency equal to a
            {
                t->mapVals[v] = a;
            }
            else
            {
                t->mapVals[v] += a; // otherwise just add a
            }
            return;
        }
        balance(t); // balance the tree
    }

    // Remove a key from a subtree
    void remove(const Comparable &x, DSAvlNode *&t) // removes x from a subtree, t is the node that roots the subtree
    {
        // Remove logic with balancing
        if (t == nullptr)
        {
            throw std::runtime_error("Error, could not find 'x' in private remove function"); // throw an error
        }
        if (x < t->key)
        {
            remove(x, t->left); // call recursively
        }
        else if (t->key < x)
        {
            remove(x, t->right); // call recursively
        }
        else
        {
            if (t->right != nullptr) // if there is a right
            {
                DSAvlNode *tCopy = t;
                t->key = deleteLeftMostIn(tCopy->right);
            }
            else if (t->left != nullptr) // if there is a left
            {
                DSAvlNode *tCopy = t;
                t = t->left;
                delete tCopy;
            }
            else // otherwise
            {
                delete t;
                t = nullptr;
                size--;
                return;
            }
        }
        balance(t);
        t->height = std::max(height(t->left), height(t->right)) + 1;
    }

    // Delete the leftmost node in a subtree and return its key
    Comparable deleteLeftMostIn(DSAvlNode *&t) // delete left most node in the passed subtree, and returns the key in that node
    {
        // Logic to delete the leftmost node
        if (t == nullptr) // this should not happen
        {
            throw std::runtime_error("Error in Comparable deleteLeftMostIn(DSAvlNode *t)");
        }
        if (t->left == nullptr)
        {
            // found left most node in subtree
            Comparable valueToReturn = t->key;
            delete t;
            t = nullptr;

            return valueToReturn;
        }
        else // otherwise
        {
            Comparable valueToReturn = deleteLeftMostIn(t->left);
            t->height = std::max(height(t->left), height(t->right)) + 1;
            balance(t);
            return valueToReturn;
        }
    }

    // Check if a key is contained in a subtree
    std::map<Value, int> contains(const Comparable &x, DSAvlNode *t) const // true/false if x is found in the tree
    {
        // Logic to check if a key is contained
        if (t == nullptr)
        {
            return std::map<Value, int>(); // returns an empty vector
        }
        else if (x < t->key)
        {
            return contains(x, t->left); // call recursively
        }
        else if (t->key < x)
        {
            return contains(x, t->right); // call recursively
        }
        else
        {
            return t->mapVals;
        }
    }

    // Make a subtree empty
    void makeEmpty(DSAvlNode *&t) // emptys the subtree
    {
        // Logic to make a subtree empty
        if (t != nullptr)
        {
            makeEmpty(t->left);
            makeEmpty(t->right);
            delete t;
            t = nullptr;
        }
    }

    DSAvlNode *clone(DSAvlNode *t) const
    {
        // clones the subtree
        if (t == nullptr)
        {
            return nullptr;
        }
        DSAvlNode *newNode = new DSAvlNode(*t);
        newNode->left = clone(t->left);
        newNode->right = clone(t->right);
        newNode->height = t->height;
        return newNode;
    }
    // Balancing: DSAVL Rotations

    int height(DSAvlNode *t) const // returns the height of node t or -1 if nullptr
    {
        return t == nullptr ? -1 : t->height;
    }

    static const int ALLOWED_IMBALANCE = 1; // 1 is the default; more will make balancing cheaper but the search is less efficent

    /**
     * 1. Performs rotations if the the the difference of the height stored in t's two child nodes
     *    more than ALLOWED_IMBALANCE.
     * 2. Updates the height information of the note t.
     *
     * Assumes that the high information in the child nodes is correct. This is guaranteed by calling
     * balance() recursivly from the inserted node up to the tree node (see insert()). Rotations will
     * only be performed for node alpha (parent of the parent of the inserted node). For all other nodes,
     * only the height will be updated.
     */
    void balance(DSAvlNode *&t) // balances the tree
    {
        if (t == nullptr)
        {
            return;
        }

        if (height(t->left) - height(t->right) > ALLOWED_IMBALANCE) // unbalancing insertion was left
        {
            if (height(t->left->left) >= height(t->left->right))
            {
                rotateWithLeftChild(t); // case 1 (outside)
            }
            else
            {
                doubleWithLeftChild(t); // case 2 (inside)
            }
        }
        else if (height(t->right) - height(t->left) > ALLOWED_IMBALANCE) // unbalancing insertion was right
        {
            if (height(t->right->right) >= height(t->right->left))
            {
                rotateWithRightChild(t); // case 4 (outside)
            }
            else
            {
                doubleWithRightChild(t); // case 3 (inside)
            }
        }
        t->height = max(height(t->left), height(t->right)) + 1;
    }

    int max(int lhs, int rhs) const
    {
        return lhs > rhs ? lhs : rhs;
    }

    /**
     * Uses preorder traversal with R and L swapped (NRL)
     *
     * Modified from: https://stackoverflow.com/questions/36802354/print-binary-tree-in-a-pretty-way-using-c
     */

    void printTree(std::ostream &out, DSAvlNode *&t)
    {
        if (t != nullptr)
        {
            out << t->key << ":";
            for (const auto &itr : t->mapVals)
            {
                out << itr.first << "," << itr.second << ";";
            }
            out << std::endl;
            printTree(out, t->left);
            printTree(out, t->right);
        }
    }

    /**
     * Rotate binary tree node with left child.
     * For DSAVL trees, this is a single rotation for case 1.
     * Update heights, then set new root.
     */
    void rotateWithLeftChild(DSAvlNode *&k2)
    {
        DSAvlNode *k1 = k2->left;
        k2->left = k1->right;
        k1->right = k2;
        k2->height = max(height(k2->left), height(k2->right)) + 1;
        k1->height = max(height(k1->left), k2->height) + 1;
        k2 = k1;
    }

    /**
     * Rotate binary tree node with right child.
     * For DSAVL trees, this is a single rotation for case 4.
     * Update heights, then set new root.
     */
    void rotateWithRightChild(DSAvlNode *&k1)
    {
        DSAvlNode *k2 = k1->right;
        k1->right = k2->left;
        k2->left = k1;
        k1->height = max(height(k1->left), height(k1->right)) + 1;
        k2->height = max(height(k2->right), k1->height) + 1;
        k1 = k2;
    }

    /**
     * Double rotate binary tree node: first left child.
     * with its right child; then node k3 with new left child.
     * For AVL trees, this is a double rotation for case 2.
     * Update heights, then set new root.
     */
    void doubleWithLeftChild(DSAvlNode *&k3)
    {
        rotateWithRightChild(k3->left);
        rotateWithLeftChild(k3);
    }

    /**
     * Double rotate binary tree node: first right child.
     * with its left child; then node k1 with new right child.
     * For AVL trees, this is a double rotation for case 3.
     * Update heights, then set new root.
     */
    void doubleWithRightChild(DSAvlNode *&k1)
    {
        rotateWithLeftChild(k1->right);
        rotateWithRightChild(k1);
    }
};
#endif
