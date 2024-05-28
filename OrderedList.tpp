template <typename T>
OrderedList<T>::OrderedList(){}
/**********************************/
template <typename T>
void OrderedList<T>::Add(T value){
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
bool OrderedList<T>::SearchValue(T value) const{
  return list.searchValue(value);
}
/**********************************/
template <typename T>
void OrderedList<T>::Empty(){
  list.empty();
}
/**********************************/
template <typename T>
bool OrderedList<T>::IsEmpty() const{
  return list.isEmpty();
}
/**********************************/
template <typename T>
int OrderedList<T>::GetSize() const{
  return list.getSize();
}

/**********************************/
template <typename T>
OrderedList<T> OrderedList<T>::Merge(const OrderedList<T> &ol) const{
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
void OrderedList<T>::PrintAscending() const{
  list.print();
}
/**********************************/
template <typename T>
void OrderedList<T>::PrintDescending() const{
  list.printReverse();
}
