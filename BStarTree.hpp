#ifndef B_STAR_TREE_HPP
#define B_STAR_TREE_HPP

template<typename T, int O=4>
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
  
      struct Node
      {   
        Node(Node *p);
        int numberOfElements;
        int maxCapacity;
        int minCapacity;   
        T *values;
        Node* *children;
        Node* parent;
        bool isLeaf() const;
        bool isRoot() const;
        int getValueIndex(const T& v) const;
        int getChildIndex(const Node*& n) const;
        void remove(const T& v);
        void add(const T& v);
        void empty();
        bool isFull() const;
        bool isOverloaded() const;
      };
      Node *root;
      int numNodes;

    private://methods

        void add(const T& v, Node*& subRoot);
        void print(Node* subRoot) const;
        void printBackwards(Node* subRoot) const;
        void empty(Node*& subRoot);
        void Delete(T v, Node*& subRoot);
        Node* getLeftSibling(Node* n);
        Node* getRightSibling(Node* n);
        void rotateleft(Node *source, T v);
        void rotateRight(Node *source, T v); 
        void splitLeft(Node *overloaded);
        void splitRight(Node *overloaded);
        void splitRoot();
        bool search(T &value,const Node*&subRoot) const;

};

#endif // B_STAR_TREE_HPP
