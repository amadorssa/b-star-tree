#include "Queue.hpp"
template <typename T, int O> BStarTree<T, O>::BStarTree() : numNodes(0) {
    if (O < 4)
        throw "B* trees must be of at least order 4";
    root = new Node(nullptr);
}

/********************************************************/
template <typename T, int O> BStarTree<T, O>::~BStarTree() { empty(root); }

/********************************************************/
template <typename T, int O>
BStarTree<T, O>::BStarTree(const BStarTree<T, O> &t)
: numNodes(0), root(nullptr) {
    *this = t;
}

/********************************************************/
template <typename T, int O>
BStarTree<T, O> &BStarTree<T, O>::operator=(const BStarTree<T, O> &t) {
    if (this == &t)
        return *this;
    empty();
    copyNode(this->root, t.root);
    return *this;
}

/********************************************************/
template <typename T, int O> void BStarTree<T, O>::add(T v) { add(v, root); }

/********************************************************/
template <typename T, int O> bool BStarTree<T, O>::isEmpty() const {
    return root == nullptr;
}

/********************************************************/
template <typename T, int O> void BStarTree<T, O>::empty() {
    empty(root);
    root = new Node(nullptr);
}
/********************************************************/
template <typename T, int O> void BStarTree<T, O>::Delete(T v) {
     Node *subRoot = getNodeAdress(v, root);
    if (subRoot == nullptr)
        return;
    if (!subRoot->isLeaf()) {
        int index = subRoot->getKeyIndex(v);
        Node *newSubRoot = subRoot->biggestNode(subRoot->children[index]);
        subRoot->keys[index] = newSubRoot->keys[newSubRoot->numberOfKeys - 1];
        newSubRoot->removeKey(newSubRoot->keys[newSubRoot->numberOfKeys - 1]);
        handleDeletion(newSubRoot);
    } else {
        subRoot->removeKey(v);
        handleDeletion(subRoot);
    }
}

/********************************************************/
template <typename T, int O> void BStarTree<T, O>::print() const {
    if(root->numberOfKeys == 0 ) return ;
    Queue<Node *> q;
    q.enqueue(root);
    int level;
    Node *aux;
    while (!q.isEmpty()) {
        level = q.getSize();
        for (int i = 0; i < level; ++i) {
            aux = q.getFront();
            q.dequeue();
            std::cout << "(";
            for (int j = 0; j < aux->numberOfKeys; ++j) {
                std::cout << aux->keys[j] << ", ";
            }
            std::cout << "\b\b)";
            if (!aux->isLeaf()) {
                for (int k = 0; k < aux->numberOfKeys + 1; ++k) {
                    q.enqueue(aux->children[k]);
                }
            }
        }
        std::cout << std::endl << std::endl;
    }
}

/********************************************************/
template <typename T, int O> bool BStarTree<T, O>::search(T v) const {
    return search(v, root);
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
            aux = subRoot->keys[i];
            if (aux == v)
                return; // The value already exists.
            if (v < aux) {
                add(v, subRoot->children[i]); // Explore the way. Recursive.
                return;
            }
        }
        add(v, subRoot->children[subRoot->numberOfKeys]);
    } else {
        subRoot->addKey(v);
        if (!subRoot->isOverloaded())
            return; // If the node isnt full , just add.
        else {
            if (subRoot->isRoot()) {
                splitRoot();
                return;
            }
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
template <typename T, int O> void BStarTree<T, O>::empty(Node *&subRoot) {
    if (subRoot != nullptr) {
        int nm = subRoot->numberOfKeys + 1;
        for (int i = 0; i < nm; ++i)
            empty(subRoot->children[i]);
        delete subRoot;
        subRoot = nullptr;
        --numNodes;
    }
}

/********************************************************/

template <typename T, int O>
void BStarTree<T, O>::handleDeletion(Node *&subRoot) {
  
    // The easiest case.
    if (subRoot->numberOfKeys >= subRoot->minCapacity || subRoot->isRoot())
    {
        return;
    }
    
    // The node is a leaf but if we delete the key then the node's capacity will
    // be under the minimum.
    Node *leftSibling = subRoot->getLeftSibling();
    Node *rightSibling = subRoot->getRightSibling();
    Node *parent=subRoot->parent;
    bool hasLeft = leftSibling != nullptr &&
                  leftSibling->numberOfKeys > leftSibling->minCapacity;
    bool hasRight = rightSibling != nullptr &&
                   rightSibling->numberOfKeys > rightSibling->minCapacity;

    if(rightSibling == nullptr){
        lendToRight(leftSibling);
        handleDeletion(leftSibling);
    }
    else if(leftSibling == nullptr){
        lendToLeft(rightSibling);
        handleDeletion(rightSibling);
    } 
    else if(hasLeft) lendToRight(subRoot->getLeftSibling());
    else if(hasRight) lendToLeft(subRoot->getRightSibling());
    else if(parent->isRoot())
    {
        merge(subRoot);
        return;
    }
    else
    {
        merge(subRoot);
        handleDeletion(parent);      
    }
}

/******************p**************************************/
template <typename T, int O> void BStarTree<T, O>::lendToRight(Node *source) {
    // We store a reference to the parent's value that's to be used
    T valueInParent = source->parent->keys[source->parent->getChildIndex(source)];
    //we store a reference to the sibling
    Node *sibling=source->getRightSibling();
    // we store the index of the value
    int indexOfParentValue = source->parent->getKeyIndex(valueInParent);
    // puts the parent's value into the right sibling
    source->getRightSibling()->addKey(valueInParent);
    // changes the parent value
    source->parent->keys[indexOfParentValue] =
        source->keys[source->numberOfKeys - 1];
    // removes the transferred value from the source
    source->removeKey(source->keys[source->numberOfKeys - 1]);
    if(!source->isLeaf())
    {
        sibling->addChild(source->children[source->numberOfChildren-1],0);
        source->children[source->numberOfChildren-1]->parent=sibling;
        source->children[source->numberOfChildren-1]=nullptr;
        --source->numberOfChildren;
    }
}
/********************************************************/
template <typename T, int O>
typename BStarTree<T, O>::Node *BStarTree<T, O>::Node::getLeftSibling() {
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
// Assumes ideal conditions. these conditions need to be verified outside of the
// method
template <typename T, int O> void BStarTree<T, O>::lendToLeft(Node *source) {
    // We store a reference to the parent's value that's to be used
    T valueInParent = source->parent->keys[source->parent->getChildIndex(source) -1];
    //we store a reference to the sibling
    Node *sibling=source->getLeftSibling();
    // we store the index of the value
    int indexOfParentValue = source->parent->getKeyIndex(valueInParent);
    // puts the parent's value into the left sibling
    sibling->addKey(valueInParent);
    // changes the parent value
    source->parent->keys[indexOfParentValue] = source->keys[0];
    // removes the transferred value from the source
    source->removeKey(source->keys[0]);
    if(!source->isLeaf())
    {
        sibling->addChild(source->children[0],sibling->numberOfChildren);
        source->children[0]->parent=sibling;
        --source->numberOfChildren;
        for(int i=0;i<source->numberOfChildren;++i)
        {
            source->children[i]=source->children[i+1];
        }
    }
}
template <typename T, int O>
typename BStarTree<T, O>::Node *BStarTree<T, O>::Node::getRightSibling() {
    if (parent == nullptr) {
        return nullptr;
    }

    // Find this node index in the children array
    int index = parent->getChildIndex(this);

    // Check if this node is the last child, or isn't in the children list
    if (index == -1 || index == parent->numberOfKeys) {
        return nullptr;
    }

    // Return the right sibling
    return parent->children[index + 1];
}

/********************************************************/
template <typename T, int O>
void BStarTree<T, O>::split(Node *leftNode, Node *rightNode) {
    // We store a reference to the parent
    Node *parent = leftNode->parent;
    // The keys's selection order will be keys from left node, key from parent and
    // keys from rgiht node We create the new nodes
    Node *n1 = new Node(parent);
    Node *n2 = new Node(parent);
    Node *n3 = new Node(parent);

    // We create an array with the values we'll be handing to the two nodes, and
    // hand them
    T valuesToGive[2 * O];
    // we create an index to store the valuesToGive's
    int indexValues = 0;
    // add the elements from the left node
    for (int i = 0; i < leftNode->numberOfKeys; ++i) {
        valuesToGive[i] = leftNode->keys[i];
        indexValues++;
    }
    // add the element from the parent
    valuesToGive[indexValues] = parent->keys[parent->getChildIndex(leftNode)];
    parent->removeKey(valuesToGive[indexValues]);
    indexValues++;
    // add the elements from the right node
    for (int i = 0; i < rightNode->numberOfKeys; ++i) {
        valuesToGive[indexValues] = rightNode->keys[i];
        indexValues++;
    }
    // we reset the index since we'll be needing it for the transfers to the new
    // nodes
    indexValues = 0;
    // we fill the first node
    for (indexValues; indexValues < leftNode->minCapacity; ++indexValues) {
        n1->addKey(valuesToGive[indexValues]);
    }
    // We give one value to the parent
    parent->addKey(valuesToGive[indexValues]);
    indexValues++;
    // we fill the second node
    for (int i = 0; i < leftNode->minCapacity; ++i) {
        n2->addKey(valuesToGive[indexValues]);
        indexValues++;
    }
    // we give one value to the parent
    parent->addKey(valuesToGive[indexValues]);
    indexValues++;
    // we fill the last node
    for (indexValues; indexValues < 2 * O; ++indexValues) {
        n3->addKey(valuesToGive[indexValues]);
    }

    // we check if one of the nodes has children, so we know if we're splitting
    // roots or branches
    if (!leftNode->isLeaf()) {
        // we create an array with pointers pointing to splitting nodes' children
        Node *childrenToGive[2 * O + 1];
        // we create a different index, for clarity
        int indexChildren = 0;
        // we add the left node's children
        for (int i = 0; i < leftNode->numberOfKeys + 1; ++i) {
            childrenToGive[indexChildren] = leftNode->children[i];
            indexChildren++;
        }
        // we add the right node's children
        for (int i = 0; i < rightNode->numberOfKeys + 1; ++i) {
            childrenToGive[indexChildren] = rightNode->children[i];
            indexChildren++;
        }
        // we reset indexChildren
        indexChildren = 0;
        // we add the corresponding children to the first node
        for (int i = 0; i < n1->numberOfKeys + 1; ++i) {
            n1->addChild(childrenToGive[indexChildren], i);
            childrenToGive[indexChildren]->parent = n1;
            indexChildren++;
        }
        // we add the corresponding children to the second node
        for (int i = 0; i < n2->numberOfKeys + 1; ++i) {
            n2->addChild(childrenToGive[indexChildren], i);
            childrenToGive[indexChildren]->parent = n2;
            indexChildren++;
        }
        // we add the corresponding children to the third node
        for (int i = 0; i < n3->numberOfKeys + 1; ++i) {
            n3->addChild(childrenToGive[indexChildren], i);
            childrenToGive[indexChildren]->parent = n3;
            indexChildren++;
        }
    }
    // We save the index of the leftmost node
    int leftIndex = parent->getChildIndex(leftNode);
    // we remove the current nodes from the parent
    parent->removeChild(leftNode);
    parent->removeChild(rightNode);
    // we add the new nodes to the parent
    parent->addChild(n3, leftIndex);
    parent->addChild(n2, leftIndex);
    parent->addChild(n1, leftIndex);
    // we check if the parent itself became overloaded
    if (parent->isOverloaded()) {
        if (parent->isRoot())
            splitRoot();
        else {
            Node *leftS = parent->getLeftSibling();
            if (leftS != nullptr && !leftS->isFull())
                lendToLeft(parent);
            else {
                Node *rightS = parent->getRightSibling();
                if (rightS != nullptr && !rightS->isFull())
                    lendToRight(parent);
                else {
                    if (rightS != nullptr)
                        split(parent, rightS);
                    else
                        split(leftS, parent);
                }
            }
        }
    }
}

/********************************************************/
template <typename T, int O> void BStarTree<T, O>::splitRoot() {
    // We create a new root
    root->parent = new Node(nullptr);
    Node *newRoot = root->parent;
    // We create 3 new nodes, which are the splits that will happen in the root
    Node *n1 = new Node(newRoot);
    Node *n2 = new Node(newRoot);
    Node *n3 = new Node(newRoot);
    // We create an int to store the index of the keys in the root
    int indexRoot = 0;
    // We store the minimum amount of keys required in a branch node
    int minKeys = (2 * O - 1) / 3;
    // We add the values to the new nodes, as well as the new root
    for (int i = 0; i < minKeys; ++i) {
        n1->addKey(root->keys[indexRoot]);
        indexRoot++;
    }
    // We add a value to the new root
    newRoot->addKey(root->keys[indexRoot]);
    indexRoot++;
    // second node
    for (int i = 0; i < minKeys; ++i) {
        n2->addKey(root->keys[indexRoot]);
        indexRoot++;
    }
    // We add a value to the new root
    newRoot->addKey(root->keys[indexRoot]);
    indexRoot++;
    // third node
    for (indexRoot; indexRoot < root->maxCapacity + 1; ++indexRoot) {
        n3->addKey(root->keys[indexRoot]);
    }
    // we reset indexRoot
    indexRoot = 0;
    // we add the root's children to the corresponding nodes, if it has any
    if (!root->isLeaf()) {
        // we add corresponding children to first node
        for (int i = 0; i < n1->numberOfKeys + 1; ++i) {
            n1->addChild(root->children[indexRoot], i);
            root->children[indexRoot]->parent = n1;
            indexRoot++;
        }
        // we add the corresponding children to the second node
        for (int i = 0; i < n2->numberOfKeys + 1; ++i) {
            n2->addChild(root->children[indexRoot], i);
            root->children[indexRoot]->parent = n2;
            indexRoot++;
        }
        // we add the corresponding children to the third root
        for (int i = 0; i < n3->numberOfKeys + 1; ++i) {
            n3->addChild(root->children[indexRoot], i);
            root->children[indexRoot]->parent = n3;
            indexRoot++;
        }
    }
    // we add the new nodes to the new root
    newRoot->addChild(n3, 0);
    newRoot->addChild(n2, 0);
    newRoot->addChild(n1, 0);
    // We delete the old root
    delete root;
    // we point the root to the new root
    root = newRoot;
}

/********************************************************/
template <typename T, int O>
bool BStarTree<T, O>::search(T &value, const Node *subRoot) const {
    for (int i=0; i < subRoot->numberOfKeys; ++i) {
        if (value == subRoot->keys[i])
            return true;
    }
    if(subRoot->isLeaf()) return false;
    for(int i=0;i<subRoot->numberOfKeys;++i)
    {
        if (value < subRoot->keys[i])
            return search(value, subRoot->children[i]);
    }
    if (value > subRoot->keys[subRoot->numberOfKeys - 1] && !subRoot->isLeaf())
        return search(value, subRoot->children[subRoot->numberOfKeys]);
    return false;
}

template <typename T, int O>
typename BStarTree<T, O>::Node *
BStarTree<T, O>::getNodeAdress(T &value, Node *&subRoot) const {
    int i;
    for (i = 0; i < subRoot->numberOfKeys; ++i) {
        if (value == subRoot->keys[i])
            return subRoot;
    }
    if(subRoot->isLeaf()) return nullptr;
    for(int i=0;i<subRoot->numberOfKeys;++i)
    {
        if (value < subRoot->keys[i])
            return getNodeAdress(value, subRoot->children[i]);
    }
    if (value > subRoot->keys[subRoot->numberOfKeys - 1] && !subRoot->isLeaf())
        return getNodeAdress(value, subRoot->children[subRoot->numberOfKeys]);
    return nullptr;
}

template <typename T, int O>
void BStarTree<T, O>::copyNode(Node *&copy, const Node *source) {
    // If the source is null, the copy will be null
    if (source == nullptr) {
        copy = nullptr;
        return;
    }

    copy = new Node(nullptr);

    // copy the attributes of the source node
    copy->numberOfKeys = source->numberOfKeys;
    copy->minCapacity = source->minCapacity;
    copy->maxCapacity = source->maxCapacity;

    // copy the keys
    for (int i = 0; i < source->numberOfKeys; ++i) {
        copy->keys[i] = source->keys[i];
    }

    // copy the children
    for (int i = 0; i <= source->numberOfKeys; ++i) {
        copyNode(copy->children[i], source->children[i]);
    }

    ++numNodes;
}

/********************************************************/
template <typename T, int O> void BStarTree<T, O>::merge(Node *&n) {

    // We save the siblings and the parent.
    Node *right = n->getRightSibling(),*left = n->getLeftSibling(),
    *parent = n->parent;

    // We save our index (n).
    int index = parent->getChildIndex(n);

    // We save the separators.
    T leftkey = parent->keys[index - 1], rightkey = parent->keys[index];

    // For saving all the keys from left, this, right and parent.
    T aux_keys[3 * n->minCapacity + 1];

    // We save the number of keys from right, left and this.
    int size = 0;

    
    // SPECIAL CASE:
    // The root with one key and two children.
    // The other brother has minimun.
    if (parent->numberOfKeys == 2 && parent->isRoot()) {
     
        Node *newRoot = new Node(nullptr);

        // We save the total number of keys of the parent and its children.
        int numauxkeys = parent->numberOfKeys;
        
        for(int i = 0; i < parent->numberOfChildren; ++i)
            numauxkeys += parent->children[i]->numberOfKeys;
  
        // Add keys from parent to the new Root.
        for(int i = 0; i < parent->numberOfKeys; ++i){
            newRoot->addKey(parent->keys[i]);
        }

        // Add keys from children to the new Root.
        for (int i = 0; i < parent->numberOfChildren; ++i) {
            for(int j = 0; j < parent->children[i]->numberOfKeys; ++j){
                newRoot->addKey(parent->children[i]->keys[j]);
            }
        }

        // Add the grandchildrens to the new Root.
        int k = 0;
        for(int i = 0; i < parent->numberOfChildren; ++i){
            for(int j = 0; j < parent->children[i]->numberOfChildren; ++j){
                newRoot->addChild(parent->children[i]->children[j], k);
                parent->children[i]->children[j]->parent = newRoot;
                ++k;
            }
        }

        // Free these nodes.
        delete root, n, left, right;
        root = newRoot;        
        return;
    }
    
    //Aqui empezamos a llenar aux_keys con las llaves correspondientes
    for(int i = 0;i<left->numberOfKeys;++i){
        aux_keys[i] = left->keys[i];
        size++;
    }
    aux_keys[size++]=leftkey;
    for(int i = 0; i<n->numberOfKeys;++i){
        aux_keys[size] = n->keys[i];
        size++;
    }
    aux_keys[size++] = rightkey;
    for(int i = 0; i<right->numberOfKeys;++i){
        aux_keys[size] = right->keys[i];
        ++size;
    }
    Node *aux_left=new Node(parent), *aux_right= new Node(parent);
    // Lleno los nuevos nodos con las llaves correspondientes
    for (int i = 0; i < size; ++i) {
        if (i < n->maxCapacity)
            aux_left->addKey(aux_keys[i]);
        else if (i == n->maxCapacity)
            parent->addKey(aux_keys[i]);
        else if (i > n->maxCapacity)
            aux_right->addKey(aux_keys[i]);
    }
    // Empezamos a conectar los hijos de los nodos con los nuevos nodos
    if(!n->isLeaf())
    {
        Node *aux_children[(3 * (n->minCapacity)) +2];

        int child_size = 0;
        for (int i = 0; i < left->numberOfChildren; ++i)
        {
            aux_children[i] = left->children[i];
            child_size++;
        }
        for(int i=0;i<n->numberOfChildren;++i)
        {
            aux_children[child_size] = n->children[i];
            child_size++;
        }
        for(int i=0;i<right->numberOfChildren;++i)
        {
            aux_children[child_size] = right->children[i];
            child_size++;
        }
        // Conectamos los nodos con sus nuevos hijos
        for (int i = 0; i < child_size; ++i) {
            if (i < child_size / 2) {
                aux_left->addChild(aux_children[i],0);
                aux_children[i]->parent = aux_left; // Conectamos los hijos con los padres
            } else {
                aux_right->addChild(aux_children[i],0);
                aux_children[i]->parent = aux_right;
            }
        }
    }
    parent->removeKey(leftkey);
    parent->removeKey(rightkey);
    parent->removeChild(right);
    parent->removeChild(n);
    parent->removeChild(left);
    parent->addChild(aux_left, index - 1);
    parent->addChild(aux_right, index);
}
/********************************************************/
// NODE METHODS
/********************************************************/

/********************************************************/
template <typename T, int O>
BStarTree<T, O>::Node::Node(Node *p)
: parent(p), numberOfKeys(0), numberOfChildren(0) {
    if (isRoot()) {
        // set minimun and maximum KEY capacitites for a root node
        minCapacity = 1;
        maxCapacity = 2 * O - 1;
    } else {
        // set minimun and maximum KEY capacitites for a non-root node
        minCapacity = (2 * O - 1) / 3;
        maxCapacity = O - 1;
    }

    keys = new T[maxCapacity + 1];
    children = new Node *[maxCapacity + 2];
    for (int i = 0; i < maxCapacity + 2; ++i)
        children[i] = nullptr;
}
/********************************************************/
template <typename T, int O> BStarTree<T, O>::Node::~Node() {
    delete[] keys;
    delete[] children;
}
/********************************************************/
template <typename T, int O> bool BStarTree<T, O>::Node::isLeaf() const {
    return numberOfChildren == 0;
}
/********************************************************/
template <typename T, int O> bool BStarTree<T, O>::Node::isRoot() const {
    return parent == nullptr;
}
/********************************************************/
template <typename T, int O> bool BStarTree<T, O>::Node::isOverloaded() const {
    return numberOfKeys > maxCapacity;
}
/********************************************************/
template <typename T, int O> bool BStarTree<T, O>::Node::isFull() const {
    return numberOfKeys == maxCapacity;
}

/********************************************************/
template <typename T, int O>
int BStarTree<T, O>::Node::getKeyIndex(const T &v) const {
    for (int i = 0; i < numberOfKeys; ++i) {
        if (keys[i] == v)
            return i;
    }
    return -1;
}
/********************************************************/
template <typename T, int O> void BStarTree<T, O>::Node::addKey(const T &v) {
    int index = 0;
    for (index; index < numberOfKeys; ++index) {
        if (keys[index] == v)
            return;
        if (keys[index] > v)
            break;
    }

    for (int i = numberOfKeys; i > index; --i)
        keys[i] = keys[i - 1];

    keys[index] = v;
    ++numberOfKeys;
}
/********************************************************/
template <typename T, int O>
void BStarTree<T, O>::Node::addChild(Node *child, int pos) {
    for (int i = numberOfChildren; i > pos; --i) {
        children[i] = children[i - 1];
    }
    children[pos] = child;
    child->parent=this;
    ++numberOfChildren;
}
/********************************************************/
template <typename T, int O> void BStarTree<T, O>::Node::removeKey(const T &v) {
    int index = getKeyIndex(v);
    for (int i = index; i < numberOfKeys - 1; ++i) {
        keys[i] = keys[i + 1];
    }
    --numberOfKeys;
}
/********************************************************/
template <typename T, int O>
void BStarTree<T, O>::Node::removeChild(const Node *child) {
    int index = 0;
    for (index; index < numberOfChildren; ++index) {
        if (children[index] == child)
            break;
    }
    delete children[index];
    --numberOfChildren;
    for (index; index < numberOfChildren; ++index) {
        children[index] = children[index + 1];
    }
}
/********************************************************/
template <typename T, int O>
int BStarTree<T, O>::Node::getChildIndex(const Node *child) const {
    int index = -1;
    for (int i = 0; i < numberOfChildren; ++i) {
        if (children[i] == child) {
            index = i;
            break;
        }
    }
    return index;
}

/********************************************************/
template <typename T, int O>
typename BStarTree<T, O>::Node *&
BStarTree<T, O>::Node::biggestNode(Node *&subRoot) const {
    if (subRoot->isLeaf()) {
        return subRoot;
    }
    return biggestNode(subRoot->children[subRoot->numberOfChildren-1]);
}