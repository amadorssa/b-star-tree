#ifndef B_STAR_TREE_HPP
#define B_STAR_TREE_HPP

#include "OrderedList.hpp"

template<typename T>
class BStarTree
{

    public:

        BStarTree(int o);
        ~BStarTree();
        BStarTree(const BStarTree& t);
        BStarTree& operator=(const BStarTree& t);

        void add(T v);
        void Delete(T v);
        bool isEmpty() const;
        void empty();
        void print() const;
        void printBackwards() const;
        void printByLevels() const;

    private://attributes

    int degree;
    struct Node
    {   
        Node(OrderedList<T> vals,DoubleLinkedList< Node* > s,Node *p=nullptr);
        Node(T v,DoubleLinkedList< Node* > s, Node *p );
        OrderedList<T> values;
        DoubleLinkedList<Node*> children;
        Node* parent;
        bool isLeaf() const;
        bool hasLeftBrother() const;
        bool hasRightBrother() const;
        bool isRoot() const;

    };
    Node *root;
    int numNodes;

    private://methods

        void add(const T& v, Node*& subRoot);
        void print(Node* subRoot) const;
        void printBackwards(Node* subRoot) const;
        void empty(Node*& subRoot);
        void Delete(T v, Node*& subRoot);
        void rotateleft(Node *source, T v);
        void rotateRight(Node *source, T v);
};

#endif//B_STAR_TREE_HPP