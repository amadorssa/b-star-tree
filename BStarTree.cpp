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
    if(!subRoot->isLeaf()){
        int size = subRoot->values.getSize(), aux;
        for(int i =  0; i < size; ++i){
            aux = subRoot->values[i];
            if(aux == v) return; // The value already exists.
            if(aux < v){
                add(v, subRoot->children[i]); // Explore the way. Recursive.
                break;  
            } 
        }
        
    }else{
        if(!subRoot->isFull())
            subRoot->values.add(v); // If the node isnt full , just add.
        else{
            Node *aux = subRoot->getLeftSibling();
            if(aux != nullptr && !isFull(aux)){
                rotateLeft(subRoot);
            }else{
                aux = subRoot->getRightSibling();
                if(aux != nullptr && !isFull(aux)){
                    rotateRight(subRoot);
                }else{
                    split(subRoot);
                }
            }
        }         
    }
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
bool BStarTree<T>::isFull(const Node*& subRoot) const
{
    return subRoot->values.GetSize() == order - 1;
}
/********************************************************/
template<typename T>
void BStarTree<T>::rotateleft(Node *source, T v)
{
    //We store a reference to the parent's value that's to be used
    T& valueInParent=source->parent->values[source->parent->children.searchIndex(source)-1];
    //puts the parent's value in the left sibling 
    source->getLeftSibling(source)->values.add(valueInParent);
    //puts the first value from the source into the parent
    valueInParent=source->values.getFirst();
    //removes the transfered value
    source->values.deleteFirst();
    //adds the element
    source->values.add(v);
    int help=0;


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

}
/********************************************************/
//Assumes ideal conditions. these conditions need to be verified outside of the method
template<typename T>
void BStarTree<T>::rotateRight(Node *source, T v)
{
    //We store a reference to the parent's value that's to be used
    T& valueInParent=source->parent->values[source->parent->children.searchIndex(source)];
    //puts the parent's value in the right sibling 
    source->getRightSibling(source)->values.add(valueInParent);
    //puts the first value from the source into the parent
    valueInParent=source->values.getLast();
    //removes the transfered value
    source->values.deleteLast();
    //adds the element
    source->values.add(v);
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