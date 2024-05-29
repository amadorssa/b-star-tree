#ifndef QUEUE_HPP
#define QUEUE_HPP

template<typename T = int>
class Queue {

public:
    Queue();

    ~Queue();

    Queue(const Queue<T> &q);

    Queue<T> &operator=(const Queue<T> &q);

    void enqueue(T value);

    void dequeue();

    int getSize();

    T getFront();

    T getBack();

    bool isEmpty();

    void empty();

    void Print();

private:
    int size;

    struct Element {
        Element(T v, Element *nxt = nullptr);
        T value;
        Element *next;
    } *back;
};

#include "Queue.tpp"
#endif //QUEUE_HPP
