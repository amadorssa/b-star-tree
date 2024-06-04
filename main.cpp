#include "BStarTree.hpp"
#include <iostream>

void displayMenu() {
    std::cout << "1. Insert a key" << std::endl;
    std::cout << "2. Delete a key" << std::endl;
    std::cout << "3. Display the tree" << std::endl;
    std::cout << "4. Search a specific key" << std::endl;
    std::cout << "5. Exit" << std::endl;
}

template<typename T,int O>
void insertNode(BStarTree<T, O>& t) {
    T value;
    std::cout << "Enter the value to insert: ";
    std::cin >> value;
    t.add(value);
}

template<typename T, int O>
void deleteNode(BStarTree<T, O>& t) {
    T value;
    std::cout << "Enter the value to delete: ";
    std::cin >> value;
    t.Delete(value);
}

template<typename T, int O>
void displayTree(const BStarTree<T, O>& t) {
    t.print();
}

template<typename T, int O>
void seachNode(const BStarTree<T, O>& t) {
    T value;
    std::cout<<"Enter the value to search: ";
    std::cin>>value;
    
    t.search(value) ? std::cout<<"The key was found within the tree\n" : std::cout<<"The key was not found within the tree\n";

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
                seachNode(tree);
                break;
            case 5:
                std::cout << "Exiting..." << std::endl;
                break;
            default:
                std::cout << "Invalid option" << std::endl;
        }
    } while(option != 5);
    return 0;
}

