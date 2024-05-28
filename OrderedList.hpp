#ifndef ORDEREDLIST_HPP
#define ORDEREDLIST_HPP

#include "DoubleLinkedList.hpp"

/**
 * The OrderedList class implements an ordered list of elements of type T.
 * This class internally uses a DoubleLinkedList to store the elements.
 * Elements are maintained in ascending order based on their value.
 * @author Alan Torres
 * @author Manuel Gortarez
 */
template <typename T>
class OrderedList {
  public:
    /**
     * Default constructor. Initializes a new instance of OrderedList.
     */
    OrderedList();

    /**
     * Adds an element to the list in the correct position to maintain order.
     * @param value The value to add.
     */
    void Add(T value);

    /**
     * Deletes a specific element from the list.
     * @param value The value to delete.
     * @throws const char* if the value is not found in the list.
     */
    void Delete(T value);

    /**
     * Checks if a specific value is present in the list.
     * @param value The value to search for.
     * @return true if the value is present, false otherwise.
     */
    bool SearchValue(T value) const;

    /**
     * Removes all elements from the list, leaving it empty.
     */
    void Empty();

    /**
     * Checks if the list is empty.
     * @return true if the list has no elements, false otherwise.
     */
    bool IsEmpty() const;

    /**
     * Returns the number of elements in the list.
     * @return The size of the list.
     */
    int GetSize() const;

    /**
     * Merges this list with another ordered list, keeping the elements in order.
     * @param ol The other ordered list to merge with.
     * @return A new ordered list resulting from the merge.
     */
    OrderedList<T> Merge(const OrderedList<T> &ol) const;

    /**
     * Prints the elements of the list in ascending order.
     */
    void PrintAscending() const;

    /**
     * Prints the elements of the list in descending order.
     */
    void PrintDescending() const;

  private:
    /**
     * The double-linked list that stores the elements of the ordered list.
     */
    DoubleLinkedList<T> list;
};

#include "OrderedList.tpp"

#endif // !ORDEREDLIST_HPP
