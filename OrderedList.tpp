template <typename T>
OrderedList<T>::OrderedList(){}
/**********************************/
template <typename T>
void OrderedList<T>::add(T value){
    if(IsEmpty()) list.addFront(value);
    else{
        int index = 0;
        while(index<list.getSize() && value>list[index]) ++index;
        list.add(value, index);
    }
}
/**********************************/
template <typename T>
void OrderedList<T>::Delete(T value){
  if(!SearchValue(value)) throw "The value isn't in the list";
  list.remove(list.searchIndex(value));
}
/**********************************/
template <typename T>
bool OrderedList<T>::searchValue(T value) const{
  return list.searchValue(value);
}
/**********************************/
template <typename T>
void OrderedList<T>::empty(){
  list.empty();
}
/**********************************/
template <typename T>
bool OrderedList<T>::isEmpty() const{
  return list.isEmpty();
}
/**********************************/
template <typename T>
int OrderedList<T>::getSize() const{
  return list.getSize();
}

/**********************************/
template <typename T>
OrderedList<T> OrderedList<T>::merge(const OrderedList<T> &ol) const{
    OrderedList ol1 = ol;
    DoubleLinkedList aux = list;
    int size = aux.getSize();
    for(int i = 0; i < size; ++i){
        ol1.Add(aux.getFront());
        aux.removeFront();
    }
    return ol1;    
}
/**********************************/
template <typename T>
void OrderedList<T>::printAscending() const{
  list.print();
}
/**********************************/
template <typename T>
void OrderedList<T>::printDescending() const{
  list.printReverse();
}
/**********************************/

template <typename T>
T& OrderedList<T>::getFirst() const
{
  return list.getFront();
}
/**********************************/
template <typename T>
T& OrderedList<T>::getLast() const
{
  return list.getBack();
}
/**********************************/
template <typename T>
T& OrderedList<T>::getFirst() 
{
  return list.getFront();
}
/**********************************/
template <typename T>
T& OrderedList<T>::getLast() 
{
  return list.getBack();
}
/**********************************/
template <typename T>
void OrderedList<T>::deleteFirst()
{
  list.removeFront();
}
/**********************************/
template <typename T>
void OrderedList<T>::deleteLast()
{
  list.removeBack();
}