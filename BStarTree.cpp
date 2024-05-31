#include "BStarTree.hpp"
#include <cmath>
#include "Queue.hpp"

template <typename T, int O>
BStarTree<T, O>::BStarTree() : root(nullptr), numNodes(0)
 {
    if(O<4) throw "B* trees must be of at least order 4";
 };
/********************************************************/
template <typename T, int O> BStarTree<T, O>::~BStarTree() { empty(); }
/********************************************************/
template <typename T, int O>
BStarTree<T, O>::BStarTree(const BStarTree<T, O> &t)
: numNodes(0), root(nullptr) {
    *this = t;
}

/********************************************************/
template <typename T, int O>
BStarTree<T, O> &BStarTree<T, O>::operator=(const BStarTree<T, O> &t) {}
/********************************************************/
template <typename T, int O> void BStarTree<T, O>::add(T v) { add(v, root); }
/********************************************************/
template <typename T, int O> bool BStarTree<T, O>::isEmpty() const {
    return root == nullptr;
}

/********************************************************/
template <typename T, int O> void BStarTree<T, O>::empty() { empty(root); }
/********************************************************/
template <typename T, int O> void BStarTree<T, O>::Delete(T v) {
    Delete(v, root);
}
/********************************************************/
template <typename T, int O> void BStarTree<T, O>::print() const {
    print(root);
}
/********************************************************/
template <typename T, int O> void BStarTree<T, O>::printBackwards() const {
    printBackwards(root);
}

/********************************************************/
template <typename T, int O> void BStarTree<T, O>::printByLevels() const {
  Queue<Node*> q;
  q.enqueue(root);
  while(!q.isEmpty()){
    int level = q.getSize();
    for(int i = 0; i<level; ++i){
      Node* aux = q.getFront();
      q.dequeue();
      std::cout<<"(";
      for(int j = 0; i<aux->numberOfKeys; ++i){
        std::cout<<aux->keys[j]<<", ";
      }
      std::cout<<"\b\b)";
      if(!aux->isLeaf()){
        for(int k = 0; i<aux->numberOfKeys+1;++k){
          q.enqueue(aux->children[k]);
        }
      }
    }
    std::cout<<std::endl<<std::endl;
  }
}

/********************************************************/
// PRIVATE METHODS
/********************************************************/

/********************************************************/
template <typename T, int O>
void BStarTree<T, O>::add(const T &v, Node *&subRoot) {
    if (!subRoot->isLeaf()) {
        int size = subRoot->numberOfKeys, aux;
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
            subRoot->addValue(v); // If the node isnt full , just add.
        else {
            Node *leftS = subRoot->getLeftSibling();
            if (leftS != nullptr && !leftS->isFull()) {
                lendToLeft(subRoot);
            } else {
                Node *rightS = subRoot->getRightSibling();
                if (rightS != nullptr && !rightS->isFull()) {
                    lendToRight(subRoot);
                } else {
                    if (rightS != nullptr)
                        split(subRoot, rightS);
                    else
                        split(leftS, subRoot);
                }
            }
        }
    }
}

/********************************************************/

template <typename T, int O> void BStarTree<T, O>::print(Node *subRoot) const {}
/********************************************************/
template <typename T, int O>
void BStarTree<T, O>::printBackwards(Node *subRoot) const {}

/********************************************************/
template <typename T, int O> void BStarTree<T, O>::empty(Node *&subRoot) {
    if (subRoot != nullptr) {
        int nm = subRoot->numberOfElements + 1;
        for (int i = 0; i < nm; ++i)
            empty(subRoot->children[i]);
        delete subRoot;
        subRoot = nullptr;
        --numNodes;
    }
}

/********************************************************/

template <typename T, int O>
void BStarTree<T, O>::Delete(T v, Node *&subRoot) {}

/********************************************************/
template<typename T, int O>
void BStarTree<T,O>::lendToRight(Node *source)
{
    // We store a reference to the parent's value that's to be used
    T valueInParent =source->parent->values[source->parent->getChildIndex(source) + 1];
    //we store the index of the value
    int indexOfParentValue=source->parent->getValueIndex(valueInParent);
    //puts the parent's value into the right sibling
    source->getRightSibling()->addValue(valueInParent);
    //changes the parent value
    source->parent->values[indexOfParentValue]=source->values[source->numberOfElements-1];
    // removes the transferred value from the source
    source->values.removeValue(source->values[source->numberOfElements-1]);
}
/********************************************************/
template<typename T, int O>
typename BStarTree<T,O>::Node* BStarTree<T,O>::Node::getLeftSibling(){
    if (parent == nullptr) {
        return nullptr;
    }

    // Find this node index in the children array
    int index = parent->getChildIndex(this);

    // Check if this node is the first child, or isn't in the children list
    if (index <= 0) {
        return nullptr;
    }

    // Return the left sibling
    return parent->children[index - 1];
}
/********************************************************/
//Assumes ideal conditions. these conditions need to be verified outside of the method
template<typename T, int O>
void BStarTree<T,O>::lendToLeft(Node *source)
{
    // We store a reference to the parent's value that's to be used
    T valueInParent =source->parent->values[source->parent->getChildIndex(source) + 1];
    //we store the index of the value
    int indexOfParentValue=source->parent->getValueIndex(valueInParent);
    //puts the parent's value into the left sibling
    source->getLeftSibling()->addValue(valueInParent);
    //changes the parent value
    source->parent->values[indexOfParentValue]=source->values[0];
    // removes the transferred value from the source
    source->values.removeValue(source->values[0]);
}
template<typename T, int O>
typename BStarTree<T,O>::Node* BStarTree<T,O>::Node::getRightSibling() {
    if (parent == nullptr) {
        return nullptr;
    }

    // Find this node index in the children array
    int index=parent->getChildIndex(this);

    // Check if this node is the last child, or isn't in the children list
    if (index == -1 || index == parent->numberOfKeys) {
        return nullptr;
    }

    // Return the right sibling
    return parent->children[index + 1];
}

/********************************************************/
template <typename T, int O>
void BStarTree<T, O>::split(Node *leftNode,Node *rightNode )
 {
    //We store a reference to the parent
    Node *parent=leftNode->parent;
    //The keys's selection order will be keys from left node, key from parent and keys from rgiht node
    //We create the new nodes
    Node *n1= new Node(parent);
    Node *n2= new Node(parent);
    Node *n3= new Node(parent);

    //We create an array with the values we'll be handing to the two nodes, and hand them
    T valuesToGive[2*O];
    //we create an index to store the valuesToGive's
    int indexValues=0;
    //add the elements from the left node
    for(int i=0; i<leftNode->numberOfKeys;++i)
    {
        valuesToGive[i]=leftNode->values[i];
        indexValues++;
    }
    //add the element from the parent
    valuesToGive[indexValues]=parent->values[parent->getChildIndex(leftNode)];
    indexValues++;
    //add the elements from the right node
    for(int i=0; i<rightNode->numberOfKeys;++i)
    {
        valuesToGive[indexValues]=rightNode->values[i];
        indexValues++;
    }

    //we reset the index since we'll be needing it for the transfers to the new nodes
    indexValues=0;
    //we fill the first node
    for(indexValues;indexValues<leftNode->minCapacity;++indexValues)
    {
        n1->addValue(valuesToGive[indexValues]);
    }
    //We give one value to the parent
    parent->addValue(valuesToGive[indexValues]);
    indexValues++;
    //we fill the second node
    for(indexValues;indexValues<leftNode->minCapacity;++indexValues)
    {
        n2->addValue(valuesToGive[indexValues]);
    }
    //we give one value to the parent
    parent->addValue(valuesToGive[indexValues]);
    indexValues++;
    //we fill the last node
    for(indexValues;indexValues<2*O;++indexValues)
    {
        n3->addValue(valuesToGive[indexValues]);
    }

    //we check if one of the nodes has children, so we know if we're splitting roots or branches
    if(!leftNode->isLeaf())
    {
        //we create an array with pointers pointing to splitting nodes' children
        Node *childrenToGive[2*O+1];
        //we create a different index, for clarity
        int indexChildren=0;
        //we add the left node's children
        for(int i=0;i<leftNode->numberOfKeys+1;++i)
        {
            childrenToGive[indexChildren]=leftNode->children[i];
            indexChildren++;
        }
        //we add the right node's children
        for(int i=0;i<rightNode->numberOfKeys+1;++i)
        {
            childrenToGive[indexChildren]=rightNode->children[i];
            indexChildren++;
        }
        //we reset indexChildren
        indexChildren=0;
        //we add the corresponding children to the first node
        for(int i=0;i<n1->numberOfKeys+1;++i)
        {
            n1->addChild(childrenToGive[indexChildren],i);
            indexChildren++;
        }
        //we add the corresponding children to the second node
        for(int i=0;i<n2->numberOfKeys+1;++i)
        {
            n1->addChild(childrenToGive[indexChildren],i);
            indexChildren++;
        }
        //we add the corresponding children to the third node
        for(int i=0;i<n3->numberOfKeys+1;++i)
        {
            n1->addChild(childrenToGive[indexChildren],i);
            indexChildren++;
        }
    }
    //We save the index of the leftmost node
    int leftIndex=parent->getChildIndex(leftNode);
    //we remove the current nodes from the parent
    parent->removeChild(leftNode);
    parent->removeChild(rightNode);
    //we add the new nodes to the parent
    parent->addChild(n3,leftIndex);
    parent->addChild(n2,leftIndex);
    parent->addChild(n1,leftIndex);
    //we check if the parent itself became overloaded
    if(parent->isOverloaded())
    {
        if(parent->isRoot) splitRoot();
        else
        {
            Node *leftS = parent->getLeftSibling();
            if (leftS != nullptr && !leftS->isFull()) lendToLeft(parent);
            else
            {
                Node *rightS = parent->getRightSibling();
                if (rightS != nullptr && !rightS->isFull()) lendToRight(parent);
                else
                {
                    if (rightS != nullptr) split(parent, rightS);
                    else split(leftS, parent);
                }
            }
        }
    }
}
 
/********************************************************/
template <typename T, int O>
void BStarTree<T, O>::splitRoot()
{
    //We create a new root
    root->parent = new Node(nullptr);
    Node *newRoot = root->parent;
    // We create 3 new nodes, which are the splits that will happen in the root
    Node *n1 = new Node(newRoot);
    Node *n2 = new Node(newRoot);
    Node *n3 = new Node(newRoot);
    //We create an int to store the index of the keys in the root
    int  indexRoot=0;
    //We store the minimum amount of keys required in a branch node
    int minKeys=(2/3)*(O-1);
    //We add the values to the new nodes, as well as the new root
    for(int i=0;i<minKeys;++i)
    {
        n1->addValue(root->values[indexRoot]);
        indexRoot++;
    }
    //We add a value to the new root
    newRoot->addValue(root->values[indexRoot]);
    indexRoot++;
    //second node
    for(int i=0;i<minKeys;++i)
    {
        n2->addValue(root->values[indexRoot]);
        indexRoot++;
    }
    //We add a value to the new root
    newRoot->addValue(root->values[indexRoot]);
    indexRoot++;
    //third node
    for(indexRoot;indexRoot<root->maxCapacity;++indexRoot)
    {
        n3->addValue(root->values[indexRoot]);
        indexRoot++;
    }
    //we reset indexRoot
    indexRoot=0;
    // we add the root's children to the corresponding nodes, if it has any
    if (!root->isLeaf())
    {
        //we add corresponding children to first node
        for(int i=0;i<n1->numberOfKeys+1;++i)
        {
            n1->addChild(root->children[indexRoot]);
            indexRoot++;
        }
        //we add the corresponding children to the second node
        for(int i=0;i<n2->numberOfKeys+1;++i)
        {
            n1->addChild(root->children[indexRoot]);
            indexRoot++;
        }
        //we add the corresponding children to the third root
        for(int i=0;i<n3->numberOfKeys+1;++i)
        {
            n3->addChild(root->children[indexRoot]);
        }
    }
    //we add the new nodes to the new root
    newRoot->addChild(n3,0);
    newRoot->addChild(n2,0);
    newRoot->addChild(n1,0);
    // We delete the old root
    delete root;
    //we point the root to the new root
    root=newRoot;
}

/********************************************************/
template <typename T, int O>
bool BStarTree<T, O>::search(T &value, const Node *&subRoot) const {
    int i = 0;
    for (i; i < subRoot->numberOfElements; ++i) {
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

/********************************************************/
template<typename T, int O>
BStarTree<T,O>::Node::Node(Node *p) : parent(p), numberOfKeys(0) 
{
    if(isRoot())
    {
        //set minimun and maximum KEY capacitites for a root node
        minCapacity=1;
        maxCapacity=3*O+1;
    }
    else
    {
        //set minimun and maximum KEY capacitites for a non-root node
        minCapacity=(2/3)*(O-1);
        maxCapacity=O-1;
    }
    T auxVals[maxCapacity + 1];       // one more in case it overloads
    Node *auxChldrn[maxCapacity + 2]; // one more in case it overloads

    keys = auxVals;
    children = auxChldrn;
}
/********************************************************/
template <typename T, int O> bool BStarTree<T, O>::Node::isLeaf() const {
    return children[0] == nullptr;
}
/********************************************************/
template <typename T, int O> bool BStarTree<T, O>::Node::isRoot() const {
    return parent == nullptr;
}
/********************************************************/
template<typename T, int O>
bool BStarTree<T,O>::Node::isOverloaded() const
{
    return numberOfKeys>maxCapacity; 
}
/********************************************************/
template<typename T, int O>
bool BStarTree<T,O>::Node::isFull() const
{
    return numberOfKeys==maxCapacity;
}

/********************************************************/
template<typename T, int O>
int BStarTree<T,O>::Node::getKeyIndex(const T& v) const
{
    for(int i=0;i<numberOfKeys;++i)
    {
        if(keys[i]==v) return i;
    }
}
/********************************************************/
template<typename T, int O>
void BStarTree<T,O>::Node::addKey(const T& v)
{                            
    int index = 0;
    for(index; index < numberOfKeys; ++index){
        if(keys[index] == v) return;
        if(keys[index] < v) break;
    }

    for(int i = index; i < numberOfKeys; ++i)
        keys[i + 1] = keys[i];

    keys[index] = v;
    ++numberOfKeys;

}
/********************************************************/
template<typename T, int O>
void BStarTree<T,O>::Node::addChild(Node *child,int pos)
{
    //we can derive number of children from number of keys
    for(int i=numberOfKeys;i>pos-1;--i)
    {
        children[i]=children[i-1];
    }
    children[pos]=child;
}
/********************************************************/
template<typename T, int O>
void BStarTree<T,O>::Node::removeKey(const T& v)
{
    int index=getKeyIndex(v);
    for(int i=index;i<numberOfKeys-1;++i)
    {
        keys[i]=keys[i+1];
    }
    --numberOfKeys;
} 
/********************************************************/
template<typename T, int O>
void BStarTree<T,O>::Node::removeChild(const Node *child)
{
    int index=0;
    for(index;index<numberOfKeys+1;++index)
    {
        if(children[index]==child) break;
    }
    delete children[index];
    for(index;index<numberOfKeys;++index)
    {
        children[index]==children[index+1];
    }
}
/********************************************************/
template<typename T, int O>
int BStarTree<T,O>::Node::getChildIndex(const Node* child) const
{
    int  index=-1;
    for (int i = 0; i <=numberOfKeys; ++i) {
            if (children[i] == child) {
                index = i;
                break;
            }
    }
    return index;
}
