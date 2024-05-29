#include "BStarTree.hpp"

template<typename T>
BStarTree<T>::BStarTree(int o): root(nullptr), numNodes(0),degree(o) {};
/********************************************************/
template<typename T>
BStarTree<T>::~BStarTree()
{
    empty();
}
/********************************************************/
template<typename T>
BStarTree<T>::BStarTree(const BStarTree<T>& t): numNodes(0), root(nullptr)
{
    *this=t;
}
/********************************************************/
template<typename T>
BStarTree<T>& BStarTree<T>::operator=(const BStarTree<T>& t)
{

}
/********************************************************/
template<typename T>
void BStarTree<T>::add(T v)
{
    add(v,root);
}
/********************************************************/
template<typename T>
bool BStarTree<T>::isEmpty() const
{
    return root==nullptr;
}
/********************************************************/
template<typename T>
void BStarTree<T>::empty()
{
    empty(root);
}
/********************************************************/
template<typename T>
void BStarTree<T>::Delete(T v)
{
    Delete(v,root);
}
/********************************************************/
template<typename T>
void BStarTree<T>::print() const
{
    print(root);
}
/********************************************************/
template<typename T>
void BStarTree<T>::printBackwards() const
{
    printBackwards(root);
}

/********************************************************/
template<typename T>
void BStarTree<T>::printByLevels() const
{
    
}



/********************************************************/
//PRIVATE METHODS
/********************************************************/




/********************************************************/
template<typename T>
void BStarTree<T>::add(const T& v, Node*& subRoot)
{

}
/********************************************************/
template<typename T>
void BStarTree<T>::print(Node *subRoot) const
{

}
/********************************************************/
template<typename T>
void BStarTree<T>::printBackwards(Node *subRoot) const
{

}
/********************************************************/
template<typename T>
void BStarTree<T>::empty(Node *& subRoot)
{

}
/********************************************************/
template<typename T>
void BStarTree<T>::Delete(T v, Node*& subRoot)
{

}
/********************************************************/
template<typename T>
void BStarTree<T>::rotateleft(Node *source, T v)
{
    source->values.get
}
/********************************************************/
template<typename T>
void BStarTree<T>::rotateRight(Node *source, T v)
{

}


/********************************************************/
//NODE METHODS
/********************************************************/



/********************************************************/
template<typename T>
BStarTree<T>::Node::Node(OrderedList<T> vals,DoubleLinkedList<Node*> s, Node *p): values(vals),children(s), parent(p){}
/********************************************************/
template<typename T>
BStarTree<T>::Node::Node(T v,DoubleLinkedList<Node*> s, Node *p): children(s), parent(p)
{
    values.add(v);
}
/********************************************************/
template<typename T>
bool BStarTree<T>::Node::isLeaf() const
{
    return children.isEmpty();
}
/********************************************************/
template<typename T>
bool BStarTree<T>::Node::isRoot() const
{
    return parent==nullptr;
}