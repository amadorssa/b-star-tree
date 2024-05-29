#include "BStarTree.hpp"

template<typename T>
BStarTree<T>::BStarTree(int o): root(nullptr), numNodes(0),order(o) {};
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
typename BStarTree<T>::Node* BStarTree<T>::getLeftSibling(Node* actual)
{   
    // Revisar si el nodo es la raíz
    if (actual == nullptr || actual->parent==nullptr){
        return nullptr;
    }

    // Encontrar el índice del nodo en la lista de hijos del padre
    Node* parent = actual->parent;
    int childIndex = -1;
    int numChildren = parent->children.getSize();
    for (int i = 0; i < numChildren; ++i) {
        if (parent->children[i] == actual) {
            childIndex = i;
            break;
        }
    }

    // Si el nodo no está en la lista de hijos del padre, regresar nullptr
    if (childIndex <= 0) {
        return nullptr;
    }

    // Regresar el nodo izquierdo
    return parent->children[childIndex - 1];
}


template<typename T>
typename BStarTree<T>::Node* BStarTree<T>::getRightSibling(Node* actual)
{
    // Revisar si el nodo es la raíz
    if (actual == nullptr || actual->parent==nullptr){
        return nullptr;
    }

    // Encontrar el índice del nodo en la lista de hijos del padre
    Node* parent = actual->parent;
    int childIndex = -1; 
    numChildren = parent->children.getSize();
    for (int i = 0; i < numChildren; ++i) {
        if (parent->children[i] == actual) {
            childIndex = i;
            break;
        }
    }

    // Si el nodo no está en la lista de hijos del padre, regresar nullptr
    if (childIndex == -1 || childIndex == numChildren - 1) {
        return nullptr;
    }

    // Regresar el nodo derecho
    return parent->children[childIndex + 1];
}

/********************************************************/
//NODE METHODS
/********************************************************/

template<typename T>
bool BStarTree<T>::Node::isLeaf() const
{
    return children.isEmpty();
}



template<typename T>
bool BStarTree<T>::Node::hasLeftSon() const
{
    continue;
}

template<typename T>
bool BStarTree<T>::Node::hasRightSon() const
{
    continue;
}


/********************************************************/
template<typename T>
BStarTree<T>::Node::Node(OrderedList<T> vals,DoubleLinkedList<Node*> s): values(vals),children(s){}
/********************************************************/
template<typename T>
BStarTree<T>::Node::Node(T v,DoubleLinkedList<Node*> s): children(s)
{
    values.add(v);
}
/********************************************************/
template<typename T>
bool BStarTree<T>::Node::isLeaf() const
{
    return children.isEmpty();
}