#include "BStarTree.hpp"
#include "Queue.hpp"
#include <cmath>

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
            Node *leftS = subRoot->getLeftSibling();
            if(leftS != nullptr && !isFull(leftS)){
                rotateLeft(subRoot);
            }else{
                Node *rightS = subRoot->getRightSibling();
                if(rightS != nullptr && !isFull(rightS)){
                    rotateRight(subRoot);
                }else{
                    if(leftS!=nullptr) splitLeft(subRoot);
                    else splitRight(subRoot);
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
template<typename T>
void BStarTree<T>::splitRight(Node *overloaded)
{
    //Declaration of list of values
    OrderedList<T> totalValues;
    //We save relevant memory locations
    Node *sibling=getRightSibling(overloaded);
    Node *parent=overloaded->parent;
    //We save the position of the overloaded node in it's parent's children list
    int positionOverloaded=parent->children.searchIndex(overloaded);
    //We save the position of the node that is rightest of splitting nodes
    int mostRightPosition=positionOverloaded+2;
    //We fill the list of values
    totalValues=totalValues.merge(overloaded->values);
    totalValues=totalValues.merge(sibling->values);
    totalValues.add(parent->values[positionOverloaded]);
    //We create a queue to save the children of the overloaded node and it's sibling
    Queue<Node*> totalChildren;
    //We fill the queue with the overloaded node's children, as well as it's sibling's
    for(int i=0; i<overloaded->children.getSize();++i) totalChildren.enqueue(overloaded->children[i]);
    for(int i=0; i<sibling->children.getSize();++i) totalChildren.enqueue(sibling->children[i]);
    //We create 3 new nodes which are to be the splits
    Node *n1=new Node();
    Node *n2=new Node();
    Node *n3=new Node();
    //We fill said nodes, and push the corresponding values to the parent
    for(int i=0;i<ceil((2*order)/3)-1;++i)
    {
        n1->values.add(totalValues.getFirst());
        totalValues.deleteFirst();
    }
    parent->values.add(totalValues.getFirst());
    totalValues.deleteFirst();
    //Second node
    for(int i=0;i<ceil((2*order)/3)-1;++i)
    {
        n2->values.add(totalValues.getFirst());
        totalValues.deleteFirst();
    }
    parent->values.add(totalValues.getFirst());
    totalValues.deleteFirst();
    //Third node
    for(int i=0;i<ceil((2*order)/3)-1;++i)
    {
        n3->values.add(totalValues.getFirst());
        totalValues.deleteFirst();
    }
    parent->values.add(totalValues.getFirst());
    totalValues.deleteFirst();
    //We check if the queue isn't empty(it would mean we're in a leaf scenario)
    if(!totalChildren.isEmpty())
    {
        //We add the children to the respective nodes
        for(int i=0;i<ceil((2*order)/3);++i)
        {
            n3->children.add(totalChildren.getFront());
            totalChildren.dequeue();
        }
        //second node
        for(int i=0;i<ceil((2*order)/3);++i)
        {
            n2->children.add(totalChildren.getFront());
            totalChildren.dequeue();
        }
        //third node
        for(int i=0;i<ceil((2*order)/3);++i)
        {
            n1->children.add(totalChildren.getFront());
            totalChildren.dequeue();
        }
    }
    //we add the new nodes to the parent node
    parent->children.add(n3,mostRightPosition);
    parent->children.add(n2,mostRightPosition);
    parent->children.add(n1,mostRightPosition);
    //we remove the original overloaded node and it's sibling
    parent->children->remove(positionOverloaded);
    parent->children->remove(positionOverloaded);

    //We check if the parent didn't become overloaded itself, and handle the situation
    if(isOverloaded(parent))
    {
        //We check if we can perform a rotation, and do so if possible
        Node *leftS = parent->getLeftSibling();
            if(leftS != nullptr && !isFull(leftS)){
                rotateLeft(parent);
            }else{
                Node *rightS = parent->getRightSibling();
                if(rightS != nullptr && !isFull(rightS)){
                    rotateRight(parent);
                }else{
                    //We perform the corresponding split
                    if(leftS!=nullptr) splitLeft(parent);
                    else splitRight(parent);
                }
            }
    }
}
/********************************************************/
template<typename T>
void BStarTree<T>::splitLeft(Node *overloaded)
{
        //Declaration of list of values
    OrderedList<T> totalValues;
    //We save relevant memory locations
    Node *sibling=getLeftSibling(overloaded);
    Node *parent=overloaded->parent;
    //We save the position of the overloaded node in it's parent's children list
    int positionOverloaded=parent->children.searchIndex(overloaded);
    //We save the position of the node that is rightest of splitting nodes
    int mostRightPosition=positionOverloaded+1;
    //We fill the list of values
    totalValues=totalValues.merge(overloaded->values);
    totalValues=totalValues.merge(sibling->values);
    totalValues.add(parent->values[positionOverloaded]);
    //We create a queue to save the children of the overloaded node and it's sibling
    Queue<Node*> totalChildren;
    //We fill the queue with the overloaded node's children, as well as it's sibling's
    for(int i=0; i<sibling->children.getSize();++i) totalChildren.enqueue(sibling->children[i]);
    for(int i=0; i<overloaded->children.getSize();++i) totalChildren.enqueue(overloaded->children[i]);
    //We create 3 new nodes which are to be the splits
    Node *n1=new Node();
    Node *n2=new Node();
    Node *n3=new Node();
    //We fill said nodes, and push the corresponding values to the parent
    for(int i=0;i<ceil((2*order)/3)-1;++i)
    {
        n1->values.add(totalValues.getFirst());
        totalValues.deleteFirst();
    }
    parent->values.add(totalValues.getFirst());
    totalValues.deleteFirst();
    //Second node
    for(int i=0;i<ceil((2*order)/3)-1;++i)
    {
        n2->values.add(totalValues.getFirst());
        totalValues.deleteFirst();
    }
    parent->values.add(totalValues.getFirst());
    totalValues.deleteFirst();
    //Third node
    for(int i=0;i<ceil((2*order)/3)-1;++i)
    {
        n3->values.add(totalValues.getFirst());
        totalValues.deleteFirst();
    }
    parent->values.add(totalValues.getFirst());
    totalValues.deleteFirst();
    //We check if the queue isn't empty(it would mean we're in a leaf scenario)
    if(!totalChildren.isEmpty())
    {
        //We add the children to the respective nodes
        for(int i=0;i<ceil((2*order)/3);++i)
        {
            n3->children.add(totalChildren.getFront());
            totalChildren.dequeue();
        }
        //second node
        for(int i=0;i<ceil((2*order)/3);++i)
        {
            n2->children.add(totalChildren.getFront());
            totalChildren.dequeue();
        }
        //third node
        for(int i=0;i<ceil((2*order)/3);++i)
        {
            n1->children.add(totalChildren.getFront());
            totalChildren.dequeue();
        }
    }
    //we add the new nodes to the parent node
    parent->children.add(n3,mostRightPosition);
    parent->children.add(n2,mostRightPosition);
    parent->children.add(n1,mostRightPosition);
    //we remove the original overloaded node and it's sibling
    parent->children->remove(positionOverloaded-1);
    parent->children->remove(positionOverloaded-1);

    //We check if the parent didn't become overloaded itself, and handle the situation
    if(isOverloaded(parent))
    {
        //We check if we can perform a rotation, and do so if possible
        Node *leftS = parent->getLeftSibling();
            if(leftS != nullptr && !isFull(leftS)){
                rotateLeft(parent);
            }else{
                Node *rightS = parent->getRightSibling();
                if(rightS != nullptr && !isFull(rightS)){
                    rotateRight(parent);
                }else{
                    //We perform the corresponding split
                    if(leftS!=nullptr) splitLeft(parent);
                    else splitRight(parent);
                }
            }
    }
}
/********************************************************/
template<typename T>
bool BStarTree<T>::isOverloaded(const Node *subRoot) const
{
    return subRoot->values.getSize()>=order;
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
BStarTree<T>::Node::Node(Node *p): parent(p){}
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