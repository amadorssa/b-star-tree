#include <iostream>

//***********************************************************
template<typename T>
Queue<T>::Queue() : back(nullptr), size(0) {}

//***********************************************************
template<typename T>
Queue<T>::~Queue() {
    if(!isEmpty()) empty();
}

//***********************************************************
template<typename T>
Queue<T>::Queue(const Queue<T> &q) : back(nullptr), size(0) { *this = q; }

//**********************************************************
template<typename T>
Queue<T>& Queue<T>::operator=(const Queue<T> &q) {
    if (this == &q) return *this;
    empty();
    Element *aux = q.front;
    while (aux != nullptr) {
        push(aux->num);
        aux = aux->next;
    } 
    return *this;
}

//***********************************************************
template<typename T>
void Queue<T>::enqueue(T value) {
    try {
        Element *aux = new Element(value, isEmpty() ? nullptr : back->next);
        (isEmpty() ? aux->next : back->next) = aux;
        back = aux;
        ++size;
    } catch (std::bad_alloc &) {
        throw "Error: It's not possible to push the value in the queue.";
    }
}

//***********************************************************
template<typename T>
void Queue<T>::dequeue() {
    if (!isEmpty()) {
        if (size == 1) {
            delete back;
            back = nullptr;
        } else {
            Element *aux = back->next;
            back->next = back->next->next;
            delete aux;
        }
        --size;
    } else {
        throw "error...";
    }
}

//***********************************************************
template<typename T>
int Queue<T>::getSize() { return size; }

//***********************************************************
template<typename T>
T Queue<T>::getFront() {
    if (isEmpty()) throw "";   
    return back->next->value;
}

//***********************************************************
template <typename T> T Queue<T>::getBack() {
    if(isEmpty()) throw "";
    return back->value;
}

//***********************************************************
template<typename T>
bool Queue<T>::isEmpty() { return size == 0; }

//***********************************************************
template<typename T>
void Queue<T>::empty() {
    Element *aux = back->next;
    while (back->next != nullptr) {
        back->next = back->next->next;
        delete aux;
        aux = back->next;
    }
    back = nullptr;
    size = 0;
}

//***********************************************************
template<typename T>
Queue<T>::Element::Element(T v, Queue<T>::Element *nxt) : value(v), next(nxt) {}







