#ifndef B_STAR_TREE_HPP
#define B_STAR_TREE_HPP

template<typename T, int O=4>
class BStarTree
{

public:

    BStarTree();
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
          int numberOfKeys;
          int maxCapacity;
          int minCapacity;   
          T *keys;
          Node* *children;
          Node* parent;
          bool isLeaf() const;
          bool isRoot() const;
          int getKeyIndex(const T& v) const;
          int getChildIndex(const Node* child) const;
          void removeKey(const T& v);
          void removeChild(const Node *child);
          void addKey(const T& v);
          void addChild(Node *child, int pos);
          void empty();
          bool isFull() const;
          bool isOverloaded() const;
          Node* getLeftSibling();
          Node* getRightSibling();
          Node*& biggestNode(Node *&subroot) const;
      };
    Node *root;
    int numNodes;

private://methods

    void add(const T& v, Node*& subRoot);
    void print(Node* subRoot) const;
    void printBackwards(Node* subRoot) const;
    void empty(Node*& subRoot);
    void handleDeletion(Node*& subRoot);
    void lendToLeft(Node *source);
    void lendToRight(Node *source); 
    void split(Node *leftNode, Node *rightNode);
    void splitRoot();
    bool search(T &value,const Node*subRoot) const;
    Node* getNodeAdress(T& v, Node *&subRoot) const;
    void merge(Node *& n);
};

#endif // B_STAR_TREE_HPP
