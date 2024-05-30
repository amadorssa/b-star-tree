#include "BStarTree.hpp"
#include "Queue.hpp"
#include <cmath>
template<typename T,int O>
BStarTree<T,O>::BStarTree(int o): root(nullptr), numNodes(0),order(o) {};
/********************************************************/
template<typename T,int O>
BStarTree<T,O>::~BStarTree()
{
    empty();
}
/********************************************************/
template<typename T, int O>
BStarTree<T,O>::BStarTree(const BStarTree<T,O>& t): numNodes(0), root(nullptr)
{
    *this=t;
}

/********************************************************/
template<typename T, int O>
BStarTree<T,O>& BStarTree<T,O>::operator=(const BStarTree<T,O>& t)
{

}
/********************************************************/
template<typename T, int O>
void BStarTree<T,O>::add(T v)
{
    add(v,root);
}
/********************************************************/
template<typename T, int O>
bool BStarTree<T,O>::isEmpty() const
{
    return root==nullptr;
}

/********************************************************/
template<typename T, int O>
void BStarTree<T,O>::empty()
{
    empty(root);
}
/********************************************************/
template<typename T, int O>
void BStarTree<T,O>::Delete(T v)
{
    Delete(v,root);
}
/********************************************************/
template<typename T,int O>
void BStarTree<T,O>::print() const
{
    print(root);
}
/********************************************************/
template<typename T, int O>
void BStarTree<T,O>::printBackwards() const
{
    printBackwards(root);
}

/********************************************************/
template<typename T, int O>
void BStarTree<T,O>::printByLevels() const
{
    
}

/********************************************************/
// PRIVATE METHODS
/********************************************************/

/********************************************************/
template<typename T, int O>
void BStarTree<T,O>::add(const T& v, Node*& subRoot)
{
    if(!subRoot->isLeaf()){
        int size = subRoot->values.getSize(), aux;
        for (int i = 0; i < size; ++i) {
            aux = subRoot->values[i];
            if (aux == v)
                return; // The value already exists.
            if (aux < v) {
                add(v, subRoot->children[i]); // Explore the way. Recursive.
                break;
            }
        }

    } else {
        if (!subRoot->isFull())
            subRoot->values.add(v); // If the node isnt full , just add.
        else {
            Node *leftS = subRoot->getLeftSibling();
            if (leftS != nullptr && !isFull(leftS)) {
                rotateLeft(subRoot);
            } else {
                Node *rightS = subRoot->getRightSibling();
                if (rightS != nullptr && !isFull(rightS)) {
                    rotateRight(subRoot);
                } else {
                    if (leftS != nullptr)
                        splitLeft(subRoot);
                    else
                        splitRight(subRoot);
                }
            }
        }
    }
}

/********************************************************/

template<typename T, int O>
void BStarTree<T, O>::print(Node *subRoot) const
{

}
/********************************************************/
template<typename T,int O>
void BStarTree<T,O>::printBackwards(Node *subRoot) const
{
  
}

/********************************************************/
template<typename T, int O>
void BStarTree<T,O>::empty(Node *& subRoot)
{

}
/********************************************************/
template <typename T, int O> void BStarTree<T,O>::empty(Node *&subRoot) {
    if (subRoot != nullptr) {
        int nm = subRoot->children.getSize();
        for (int i = 0; i < nm; ++i)
            empty(subRoot->children[i]);
        delete subRoot;
        subRoot = nullptr;
        --numNodes;
    }
}

/********************************************************/

template<typename T, int O>
void BStarTree<T,O>::Delete(T v, Node*& subRoot)
{

}
/********************************************************/
template<typename T,int O>
bool BStarTree<T,O>::isFull(const Node*& subRoot) const
{
    return subRoot->values.GetSize() == order - 1;
}
/********************************************************/
template<typename T, int O>
void BStarTree<T,O>::rotateleft(Node *source, T v)
{
    // We store a reference to the parent's value that's to be used
    T &valueInParent =
        source->parent->values[source->parent->children.searchIndex(source) - 1];
    // puts the parent's value in the left sibling
    source->getLeftSibling(source)->values.add(valueInParent);
    // puts the first value from the source into the parent
    valueInParent = source->values.getFirst();
    // removes the transfered value
    source->values.deleteFirst();
    // adds the element
    source->values.add(v);

}
/********************************************************/

template<typename T, int O>
typename BStarTree<T,O>::Node* BStarTree<T,O>::getLeftSibling(Node* actual)
{   
// Revisar si el nodo es la raíz
    if (actual == nullptr || actual->parent == nullptr) {
        return nullptr;
    }

    // Encontrar el índice del nodo en la lista de hijos del padre
    Node *parent = actual->parent;
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
/********************************************************/
//Assumes ideal conditions. these conditions need to be verified outside of the method
template<typename T, int O>
void BStarTree<T,O>::rotateRight(Node *source, T v)
{
                                                                                                                                                    //We store a reference to the parent's value that's to be used
    T& valueInParent=source->parent->values[source->parent->children.searchIndex(source)];
    //puts the parent's value in the right sibling 
    source->getRightSibling(source)->values.add(valueInParent);
    // puts the first value from the source into the parent
    valueInParent = source->values.getLast();
    // removes the transfered value
    source->values.deleteLast();
    // adds the element
    source->values.add(v);
}

template<typename T, int O>
typename BStarTree<T,O>::Node* BStarTree<T,O>::getRightSibling(Node* actual)
{
    // Revisar si el nodo es la raíz
    if (actual == nullptr || actual->parent == nullptr) {
        return nullptr;
    }

    // Encontrar el índice del nodo en la lista de hijos del padre
    Node *parent = actual->parent;
    int childIndex = -1;
    int numChildren = parent->children.getSize();
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
template<typename T, int O>
void BStarTree<T,O>::splitRight(Node *overloaded)
{

}

/********************************************************/
template<typename T, int O>
void BStarTree<T,O>::splitLeft(Node *overloaded)
{

}

/********************************************************/
template<typename T, int O>
void BStarTree<T,O>::splitRoot()
{
    //In this case we have both the full list of values and the full list(which can be treated as a queue) fo children
    //We create a new root
    root->parent=new Node();
    Node *newRoot=root->parent;
    //We create 3 new nodes, which are the splits that will happen in the root
    Node *n1=new Node();
    Node *n2=new Node();
    Node *n3=new Node();
    //We add them to an array
    Node *nodes[3]={n1,n2,n3};
    //We add the values to the new nodes, as well as the new root
    for(int i=0;i<3;++i)
    {
        for(int j=0;j<ceil((2*order)/3)-1;++j)
        {
            node[i]->values.add(root->values.getFirst());
            root->values.deleteFirst();
        }
        if(i<2)
        {
             newRoot->values.add(root->values.getFirst());
             root->values.deleteFirst();
        }
    }
    //we add the root's children to the corresponding nodes, if it has any
    if(!root.isLeaf())
    {
        for(int i=0;i<3;++i)
        {
            //We add the children to the respective nodes
            for(int j=0;i<ceil((2*order)/3);++j)
            {
                n[i]->children.addBack(root->children.getFront());
                root->children.removeFront();
            }
        } 
    }
    //We remove the root from the new root's children list
    newRoot->children.remove(root);
    //

}


/********************************************************/
template <typename T,int O>
bool BStarTree<T,O>::search(T &value, const Node *&subRoot) const {
    int i = 0;
    for (i; i < order - 1; ++i) {
        if (value == subRoot->values[i])
            return true;
        if (value < subRoot->values[i])
            return search(value, subRoot->children[i]);
    }
    return false;
}

/********************************************************/
// NODE METHODS
/********************************************************/

template<typename T,int O>
bool BStarTree<T,O>::Node::isLeaf() const
{
    return children.isEmpty();
}
/********************************************************/
template<typename T, int O>
BStarTree<T,O>::Node::Node(Node *p)
{
    numberOfElements=0;
    parent=p;
    if(isRoot())
    {
        //set minimun and maximum KEY capacitites
        minCapacity=1;
        maxCapacity=3*O+2;
    }
    else
    {
        //set minimun and maximum KEY capacitites
        minCapacity=ceil((2*O)/3)-1;
        maxCapacity=O-1;
    }
    T auxVals[maxCapacity+1];//one more in case it overloads
    Node *auxChldrn[maxCapacity+2];//one more in case it overloads

    values=auxVals;
    children=auxChldrn;
}
/********************************************************/
template<typename T, int O>
bool BStarTree<T,O>::Node::isLeaf() const
{
    return children[0]==nullptr;
}
/********************************************************/
template<typename T, int O>
bool BStarTree<T,O>::Node::isRoot() const
{
    return parent==nullptr;
}
/********************************************************/
template<typename T, int O>
bool BStarTree<T,O>::Node::isOverloaded() const
{
    return numberOfElements>maxCapacity; 
}
/********************************************************/
template<typename T, int O>
bool BStarTree<T,O>::Node::isFull() const
{
    return numberOfElements==maxCapacity;
}

/********************************************************/
template<typename T, int O>
int BStarTree<T,O>::Node::getIndex(const T& v) const
{
    for(int i=0;i<numberOfElements;++i)
    {
        if(values[i]==v) return i;
    }
}
/********************************************************/
template<typename T, int O>
void BStarTree<T,O>::Node::add(const T& v)
{                            
    int index = 0;
    for(index; index < numberOfElements; ++index){
        if(values[index] == v) return;
        if(values[index] < v) break;
    }

    for(int i = index; i < numberOfElements; ++i)
        values[i + 1] = values[i];
    
    values[index] = v;
    ++numberOfElements;

}
/********************************************************/
template<typename T, int O>
void BStarTree<T,O>::Node::remove(const T& v)
{
    int index=getIndex(v);
    for(int i=index;i<numberOfElements;++i)
    {
        values[i]=values[i+1];
    }
    --numberOfElements;
} 