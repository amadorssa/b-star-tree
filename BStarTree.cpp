#include "BStarTree.hpp"
#include <cmath>

template <typename T, int O>
BStarTree<T, O>::BStarTree() : root(nullptr), numNodes(0) {};
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
template <typename T, int O> void BStarTree<T, O>::printByLevels() const {}

/********************************************************/
// PRIVATE METHODS
/********************************************************/

/********************************************************/
template <typename T, int O>
void BStarTree<T, O>::add(const T &v, Node *&subRoot) {
    if (!subRoot->isLeaf()) {
        int size = subRoot->numberOfElements, aux;
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
            subRoot->add(v); // If the node isnt full , just add.
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
template<typename T,int O>
bool BStarTree<T,O>::isFull(const Node*& subRoot) const
{
    return subRoot->values.GetSize() == order - 1;
}
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
    source->values.remove(source->values[source->numberOfElements-1]);
}
/********************************************************/
template<typename T, int O>
typename BStarTree<T,O>::Node*::getLeftSibling(){
    if (parent == nullptr) {
        return nullptr;
    }

    // Find this node index in the children array
    int index = -1;
    for (int i = 0; i <= parent->numberOfElements; ++i) {  
        if (parent->children[i] == this) {
            index = i;
            break;
        }
    }

    // Check if this node is the first child
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
    source->values.remove(source->values[0]);
}
template<typename T, int O>
typename BStarTree<T,O>::Node*::getRightSibling() {
    if (parent == nullptr) {
        return nullptr;
    }

    // Find this node index in the children array
    int index = -1;
    for (int i = 0; i <= parent->numberOfElements; ++i) {
        if (parent->children[i] == this) {
            index = i;
            break;
        }
    }

    // Check if this node is the last child
    if (index == -1 || index == parent->numberOfElements) {
        return nullptr;
    }

    // Return the right sibling
    return parent->children[index + 1];
}

/********************************************************/
template <typename T, int O>
void BStarTree<T, O>::splitRight(Node *overloaded) {}

/********************************************************/
template <typename T, int O>
void BStarTree<T, O>::splitLeft(Node *overloaded) {}

/********************************************************/
template <typename T, int O> void BStarTree<T, O>::splitRoot() {
    // In this case we have both the full list of values and the full list(which
    // can be treated as a queue) fo children We create a new root
    root->parent = new Node();
    Node *newRoot = root->parent;
    // We create 3 new nodes, which are the splits that will happen in the root
    Node *n1 = new Node();
    Node *n2 = new Node();
    Node *n3 = new Node();
    // We add them to an array
    Node *nodes[3] = {n1, n2, n3};
    // We add the values to the new nodes, as well as the new root
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < ceil((2 * O) / 3) - 1; ++j) {
            nodes[i]->values.add(root->values.getFirst());
            root->values.deleteFirst();
        }
        if (i < 2) {
            newRoot->values.add(root->values.getFirst());
            root->values.deleteFirst();
        }
    }
    // we add the root's children to the corresponding nodes, if it has any
    if (!root->isLeaf()) {
        for (int i = 0; i < 3; ++i) {
            // We add the children to the respective nodes
            for (int j = 0; i < ceil((2 * O) / 3); ++j) {
                nodes[i]->children.addBack(root->children.getFront());
                root->children.removeFront();
            }
        }
    }
    // We remove the root from the new root's children list
    newRoot->children.remove(root);
    //
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
BStarTree<T,O>::Node::Node(Node *p) : parent(p), numberOfElements(0) 
{
    if(isRoot())
    {
        //set minimun and maximum KEY capacitites for a root node
        minCapacity=1;
        maxCapacity=3*O+2;
    }
    else
    {
        //set minimun and maximum KEY capacitites for a non-root node
        minCapacity=std::ceil((2*O)/3)-1;
        maxCapacity=O-1;
    }
    T auxVals[maxCapacity + 1];       // one more in case it overloads
    Node *auxChldrn[maxCapacity + 2]; // one more in case it overloads

    values = auxVals;
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
template <typename T, int O> bool BStarTree<T, O>::Node::isOverloaded() const {
    return numberOfElements > maxCapacity;
}
/********************************************************/
template <typename T, int O> bool BStarTree<T, O>::Node::isFull() const {
    return numberOfElements == maxCapacity;
}

/********************************************************/
template <typename T, int O>
int BStarTree<T, O>::Node::getIndex(const T &v) const {
    for (int i = 0; i < numberOfElements; ++i) {
        if (values[i] == v)
            return i;
    }
}
/********************************************************/
template<typename T, int O>
void BStarTree<T,O>::Node::addValue(const T& v)
{                            
    int index = 0;
    for (index; index < numberOfElements; ++index) {
        if (values[index] == v)
            return;
        if (values[index] < v)
            break;
    }

    for (int i = index; i < numberOfElements; ++i)
        values[i + 1] = values[i];

    values[index] = v;
    ++numberOfElements;
}
/********************************************************/
template <typename T, int O> void BStarTree<T, O>::Node::remove(const T &v) {
    int index = getIndex(v);
    for (int i = index; i < numberOfElements; ++i) {
        values[i] = values[i + 1];
    }
    --numberOfElements;
}
