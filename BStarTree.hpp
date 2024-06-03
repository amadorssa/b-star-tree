/**
 * \file BStarTree.hpp
 * \brief This file contains the implementation of the BStarTree class.
 * \author Fausto Medina, Manuel Gortarez, Alan Torres y Amado Rosas.
 * \date 2024-06-03
*/

#ifndef B_STAR_TREE_HPP
#define B_STAR_TREE_HPP

template<typename T, int O=4>
class BStarTree
{

public:

    /**
     * \brief Default constructor
     * \details This constructor creates an empty B star tree.
     */
    */
    BStarTree();

    /**
     * \brief Destructor
     * \details This destructor deletes all the nodes of the B star tree.
    */
    ~BStarTree();

    /**
     * \brief Copy constructor
     * \details This constructor creates a new B star tree that is a copy of the given B star tree.
     * \param t The B star tree to be copied.
    */
    BStarTree(const BStarTree& t);

    /**
     * \brief Assignment operator
     * \details This operator assigns the given B star tree to the current B star tree.
     * \param t The B star tree to be assigned.
     * \return A reference to the current B star tree.
    */
    BStarTree& operator=(const BStarTree& t);

    /**
     * \brief Adds a value to the B star tree.
     * \details This method adds a value to the B star tree.
     * \param v The value to be added.
    */
    void add(T v);

    /**
     * \brief Deletes a value from the B star tree.
     * \details This method deletes a value from the B star tree.
     * \param v The value to be deleted.
    */
    void Delete(T v);

    /**
     * \brief Checks if the B star tree is empty.
     * \details This method checks if the B star tree is empty.
     * \return True if the B star tree is empty, false otherwise.
    */
    bool isEmpty() const;

    /**
     * \brief Empties the B star tree.
     * \details This method empties the B star tree.
    */
    void empty();

    /**
     * \brief Prints the B star tree.
     * \details This method prints the B star tree in postorder by levels.
    */
    void print() const;

    /**
     * \brief Searches for a value in the B star tree.
     * \details This method searches for a value in the B star tree.
     * \param v The value to be searched.
     * \return True if the value is found, false otherwise.
     * 
    */
    bool search(T v) const;

private://attributes
  
    struct Node
    {   

        /**
         * \brief Default constructor to node.
         * \details This constructor creates a new node with the given parent.
         * \param p The parent of the new node.
        */
        Node(Node *p);

        /**
         * \brief Destructor to node.
         * \details This destructor deletes all the keys and children of the node.
        */
        ~Node();

        /**
         * \brief Number of keys in the node.
        */
        int numberOfKeys;

        /**
         * \brief Number of children in the node.
        */
        int numberOfChildren;
        
        /**
         * \brief Maximum capacity of keys in the node.
        */
        int maxCapacity;

        /**
         * \brief Minimum capacity of keys in the node.
        */
        int minCapacity;   

        /**
         * \brief Array of keys in the node.
        */
        T *keys;

        /**
         * \brief Array of children in the node.
        */
        Node* *children;

        /**
         * \brief Pointer to the parent of the node.
        */
        Node* parent;

        /**
         * \brief Checks if the node is a leaf.
         * \return True if the node is a leaf, false otherwise.
        */
        bool isLeaf() const;

        /**
         * \brief Checks if the node is the root.
         * \return True if the node is the root, false otherwise.
        */
        bool isRoot() const;

        /**
         * \brief Gets the index of a key in the node.
         * \param v The key to be searched.
         * \return The index of the key in the node.
        */
        int getKeyIndex(const T& v) const;

        /**
         * \brief Gets the index of a child node in the  node.
         * \param child The child node to be searched.
         * \return The index of the child node in the node.
        */
        int getChildIndex(const Node* child) const;
        
        /**
         * \brief Removes a key from the node.
         * \param v The key to be removed.
        */
        void removeKey(const T& v);
        
        /**
         * \brief Removes a child node from the node.
         * \param child The child to be removed.
        */
        void removeChild(const Node *child);

        /**
         * \brief Adds a key to the node.
         * \param v The key to be added.
        */
        void addKey(const T& v);

        /**
         * \brief Adds a child node to the node.
         * \param child The child to be added.
        */
        void addChild(Node *child, int pos);

        /**
         * \brief Empties the node.
        */
        void empty();

        /**
         * \brief Checks if the node is full.
         * \return True if the node is full, false otherwise.
        */
        bool isFull() const;

        /**
         * \brief Checks if the node is overloaded.
         * \return True if the node is overloaded, false otherwise.
        */
        bool isOverloaded() const;

        /**
         * \brief Get the left sibling of the node.
         * \return The pointer to the left sibling of the node.
        */
        Node* getLeftSibling();

        /**
         * \brief Get the right sibling of the node.
         * \return The pointer to the right sibling of the node.
        */
        Node* getRightSibling();

        /**
         * \brief Get the biggest node in the subtree.
         * \param subRoot 
         * \retun The pointer to the biggest node in the subtree.
        */
        Node*& biggestNode(Node *&subRoot) const;         
    };

    /**
     * \brief Pointer to the root of the B star tree.
    */
    Node *root;

    /**
     * \brief Number of nodes in the B star tree.
    */
    int numNodes;

private://methods

    /**
     * \brief Adds a value to the node of the tree.
     * \param v The value to be added.
     * \param subRoot The node of the tree where the value is going to be added.
    */
    void add(const T& v, Node*& subRoot);

    /**
     * \brief Prints the node of the tree.
     * \param subRoot The node of the tree to be printed.
    */
    void print(Node* subRoot) const;

    /**
     * \brief Empties the B star tree.
     * \param subRoot The node of the tree to be emptied.
     * 
    */
    void empty(Node*& subRoot);

    /**
     * \brief Rearranges the keys and child pointers of the node after a deletion.
     * \details This method is called when a key or a child is removed from the node, ensuring that the remaining keys and children are correctly ordered and referenced.
     */
    void handleDeletion(Node*& subRoot);

    /**
     * \brief Lends the minor key of the node to the left sibling.
     * \param subRoot The node of the tree that is going to lend the key.
    */
    void lendToLeft(Node *source);

    /**
     * \brief Lends the mayor key of the node to the right sibling.
     * \param subRoot The node of the tree that is going to lend the key.
    */
    void lendToRight(Node *source); 

    /**
     * \brief Splits the node of the tree.
     * \param leftNode 
     * \param rightNode 
    */
    void split(Node *leftNode, Node *rightNode);

    /**
     * \brief Splits the root of the tree.
    */
    void splitRoot();

    /**
     * \brief Copies the node of the tree.
     * \param copy 
     * \param source The pointer to the node to be copied.
    */
    void copyNode(Node *&copy, const Node *source);

    /**
     * \brief Searches for a value in the node of the tree.
     * \param value The value to be searched.
     * \param subRoot The pointer to the node of the tree where the value is going to be searched.
     * \return True if the value is found, false otherwise.
    */
    bool search(T &value,const Node*subRoot) const;

    /**
     * \brief Gets the node of the tree that contains the value.
     * \param v The value to be searched.
     * \param subRoot The pointer to the node of the tree where the value is going to be searched.
    */
    Node* getNodeAdress(T& v, Node *&subRoot) const;

    /**
     * \brief Merges the node of the tree.
     * \param n The pointer to the node of the tree to be merged.
    */
    void merge(Node *& n);
};

#endif // B_STAR_TREE_HPP
