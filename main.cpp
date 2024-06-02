#include "BStarTree.hpp"
#include "BStarTree.cpp"
#include <iostream>

void displayMenu() {
    std::cout << "1. Insert a node" << std::endl;
    std::cout << "2. Delete a node" << std::endl;
    std::cout << "3. Display the tree" << std::endl;
    std::cout << "4. Exit" << std::endl;
}

template<typename T>
void insertNode(BStarTree<T>& t) {
    T value;
    std::cout << "Enter the value to insert: ";
    std::cin >> value;
    t.add(value);
}

template<typename T>
void deleteNode(BStarTree<T>& t) {
    T value;
    std::cout << "Enter the value to delete: ";
    std::cin >> value;
    t.Delete(value);
}

template<typename T>
void displayTree(const BStarTree<T>& t) {
    t.print();
}

int main() {
    BStarTree<int> tree;
    int option;
    do {
        displayMenu();
        std::cin >> option;
        switch(option) {
            case 1:
                insertNode(tree);
                break;
            case 2:
                deleteNode(tree);
                break;
            case 3:
                displayTree(tree);
                break;
            case 4:
                std::cout << "Exiting..." << std::endl;
                break;
            default:
                std::cout << "Invalid option" << std::endl;
        }
    } while(option != 4);
    return 0;
}

