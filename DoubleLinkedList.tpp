
#include <iostream>
#include <iterator>
#include <stdexcept>

//*************************************************************
template <typename T>
DoubleLinkedList<T>::DoubleLinkedList()
: size(0), front(nullptr), back(nullptr) {}

//*************************************************************
template <typename T> DoubleLinkedList<T>::~DoubleLinkedList() { empty(); }

//*************************************************************
template <typename T>
DoubleLinkedList<T>::DoubleLinkedList(const DoubleLinkedList &l)
: size(0), front(nullptr), back(nullptr) {
    *this = l;
}

//*************************************************************
template <typename T>
DoubleLinkedList<T> &DoubleLinkedList<T>::operator=(const DoubleLinkedList &l) {
    if (this == &l)
        return *this;
    empty();
    for (int i = 0; i < l.size; ++i)
        addBack(l[i]);
    return *this;
}

//*************************************************************
template <typename T> void DoubleLinkedList<T>::addFront(T v) {
    if (size == 0) {
        front = new Element(v);
        back = front;
    } else {
        Element *aux = new Element(v, front); // it associate from right to left.
        front->previous = aux;
        front = aux;
    }
    ++size;
}

//*************************************************************
template <typename T> void DoubleLinkedList<T>::addBack(T v) {
    if (size == 0)
        addFront(v);
    else {
        back = back->next = new Element(v, nullptr, back);
        ++size;
    }
}

//*************************************************************
template <typename T> void DoubleLinkedList<T>::add(T v, const int index) {
    if (index < 0 || index > size)
        throw "Error: index out of range.";
    if (index == 0)
        addFront(v);
    else if (index == size)
        addBack(v);
    else {
        Element *now = front;
        for (int i = 0; i < index; ++i)
            now = now->next;
        Element *aux = new Element(v, now, now->previous);
        now->previous->next = aux;
        now->previous = aux;
        ++size;
    }
}

//*************************************************************
template <typename T> void DoubleLinkedList<T>::removeFront() {
    if (isEmpty())
        throw "is empty";
    if (size == 1) {
        delete front;
        back = front = nullptr;
    } else {
        Element *aux = front;
        front = front->next;
        front->previous = nullptr;
        delete aux;
    }
    --size;
}

//************************************************************
template <typename T> void DoubleLinkedList<T>::removeBack() {
    if (isEmpty())
        throw "is empty.";
    if (size == 1) {
        removeFront();
    } else {
        back = back->previous;
        delete back->next;
        back->next = nullptr;
        --size;
    }
}

//*************************************************************
template <typename T> void DoubleLinkedList<T>::remove(const int index) {
    if (isEmpty())
        throw "error, is empty";
    if (index < 0 || index >= size)
        throw "out of range";
    if (index == size - 1)
        removeBack();
    else {
        if (index == 0)
            removeFront();
        else {
            Element *now = front;
            for (int i = 0; i < index; ++i)
                now = now->next;
            Element *aux = now;
            now->previous->next = now->next;
            now->next->previous = now->previous;
            delete aux;
            --size;
        }
    }
}

//*************************************************************
template <typename T> bool DoubleLinkedList<T>::searchValue(T v) const {
    if (isEmpty())
        throw "error, the queue is empty";
    Element *now = front;
    while (now != nullptr && now->value != v)
        now = now->next;
    if (now == nullptr)
        return false;
    return true;
}

//*************************************************************
template <typename T> int DoubleLinkedList<T>::searchIndex(T v) const {
    Element *now = front;
    int index;
    for (index = 0; now != nullptr && now->value != v; ++index)
        now = now->next;
    return now != nullptr ? index : NOT_FOUND;
}

//*************************************************************
template <typename T> bool DoubleLinkedList<T>::isEmpty() const {
    return size == 0;
}

//*************************************************************
template <typename T> T DoubleLinkedList<T>::getFront() const {
    if (isEmpty())
        throw "Error is empty";
    else
        return front->value;
}

//*************************************************************
template <typename T> T DoubleLinkedList<T>::getBack() const {
    if (isEmpty())
        throw "Error is empty";
    else
        return back->value;
}

//*************************************************************
template <typename T>
T &DoubleLinkedList<T>::operator[](const int index) const {
    if (isEmpty())
        throw "Error is empty";
    if (index < 0 || index >= size)
        throw "Out of range";
    Element *aux = front;
    for (int i = 0; i < index; ++i)
        aux = aux->next;
    return aux->value;
}

//*************************************************************
template <typename T> T &DoubleLinkedList<T>::operator[](const int index) {
    if (isEmpty())
        throw "Error is empty";
    if (index < 0 || index >= size)
        throw "Out of range";
    Element *aux = front;
    for (int i = 0; i < index; ++i)
        aux = aux->next;
    return aux->value;
}

//*************************************************************
template <typename T> void DoubleLinkedList<T>::modify(T v, const int index) {
    if (isEmpty())
        throw "Error is empty";
    if (index < 0 || index >= size)
        throw "Out of range";
    Element *aux = front;
    for (int i = 0; i < index; ++i)
        aux = aux->next;
    aux->value = v;
}

//*************************************************************
template <typename T> int DoubleLinkedList<T>::getSize() const { return size; }

//*************************************************************
template <typename T> void DoubleLinkedList<T>::empty() {
    if (isEmpty())
        return;
    while (!isEmpty())
        removeFront();
}

//**************************************************************
template <typename T> void DoubleLinkedList<T>::print() const {
    if (isEmpty())
        return;
    Element *aux = front;
    std::cout << "Front->(";
    for (int i = 0; i < size; ++i) {
        std::cout << aux->value << ", ";
        aux = aux->next;
    }
    std::cout << "\b\b)" << std::endl;
}
//**************************************************************
template <typename T> void DoubleLinkedList<T>::printReverse() const {
    if (isEmpty())
        return;
    Element *aux = back;
    std::cout << "Back->(";
    for (int i = 0; i < size; ++i) {
        std::cout << aux->value << ", ";
        aux = aux->previous;
    }
    std::cout << "\b\b)" << std::endl;
}

//**************************************************************
template <typename T>
void DoubleLinkedList<T>::sort() {
    if (size <= 1)
        return;
    Element *current = front->next;
    while (current != nullptr) {
        Element *next = current->next;
        Element *compare = current->previous;

        while (compare != nullptr && current->value < compare->value) {
            compare = compare->previous;
        }
        if (compare != current->previous) {
            if (current->next != nullptr)
                current->next->previous = current->previous;
            else
                back = current->previous; 
            if (current->previous != nullptr)
                current->previous->next = current->next;
            // Inserta current después de compare
            if (compare == nullptr) { // Insertar al principio
                current->next = front;
                front->previous = current;
                front = current;
                front->previous = nullptr;
            } else { // Insertar en medio o al final
                current->next = compare->next;
                current->previous = compare;
                if (compare->next != nullptr)
                    compare->next->previous = current;
                else
                    back = current; // Actualiza back si current se inserta al final
                compare->next = current;
            }
        }
        current = next;
    }
}

//**************************************************************
template <typename T>
void DoubleLinkedList<T>::transferIndexToIndex(DoubleLinkedList &l, int start, int end){
  if (start < 0 || end >= l.size || start > end) throw std::out_of_range("Indexes out of range");
  if (l.isEmpty()) throw std::runtime_error("Cannot transfer from an empty list"); 
  if (this == &l) throw std::logic_error("Cannot self transfer"); 
    
  Element* aux = l.front;
  //Put the aux pointer on the node we want to transfer
  for(int i = 0; i<start; ++i) aux = aux->next;
  Element* beginning = aux; //Initialize the beginning of the sub-list we want to transfer
  Element* newBack = aux; //Initialize the newBack of our list
  for(int i = start; i<end; ++i) newBack = newBack->next; //Put the newBack pointer to the last element we want to transfer
  //Connect the list from where we transfer with the remain elements
  if(beginning == l.front){ //Consider the case where the first element of our sub-list is also the first element of the list we transfer elements
    l.front = newBack->next;
  }
  else{
  aux->previous->next = newBack->next;
  }
  //Connect to the receiver list
  if(isEmpty()){
    front = beginning; //If the list is empty we connect to the front 
  }
  else{
    back->next = beginning; //If the list isn't empty then we connect to back->next
    beginning->previous=back;

  }
  //Update the back pointer
  back=newBack;
  //Disconnect from the sender list
  back->next = nullptr;
  //Update the sizes of both lists
  size +=(end-start+1);
  l.size-=(end-start+1);

}
//**************************************************************
template <typename T>
void DoubleLinkedList<T>::transferFromIndex(DoubleLinkedList &l, int index){
  transferIndexToIndex(l, index, (l.size)-1); 
}
//**************************************************************
template <typename T>
void DoubleLinkedList<T>::transferList(DoubleLinkedList &l){
  transferIndexToIndex(l, 0 , (l.size)-1);
}
//**************************************************************
template <typename T>
DoubleLinkedList<T>::Element::Element(T v, DoubleLinkedList<T>::Element *nxt,DoubleLinkedList<T>::Element *prv): value(v), next(nxt), previous(prv) {}

