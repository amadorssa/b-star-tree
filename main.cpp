#include "BStarTree.hpp"
#include "BStarTree.cpp"
#include <iostream>

void displayMenu() {
    std::cout << "1. Insert a key" << std::endl;
    std::cout << "2. Delete a key" << std::endl;
    std::cout << "3. Display the tree" << std::endl;
    std::cout << "4. Search a specific key" << std::endl;
    std::cout << "5. Exit" << std::endl;
}

template <typename T, int O>
void testAdd(BStarTree<T,O>& tree){ 
    tree.add(7);
    tree.add(10);
    tree.add(23);
    tree.add(58);
    tree.add(59);
    tree.add(61);
    tree.add(77);
    tree.print();
    std::cout << "-------------------------------------" << std::endl;

    tree.add(80);
    tree.print();
    std::cout << "-------------------------------------" << std::endl;

    tree.add(11);
    tree.add(20);
    tree.print();
    std::cout << "-------------------------------------" << std::endl;

    tree.add(44);
    tree.add(50);
    tree.print();
    std::cout << "-------------------------------------" << std::endl;

    tree.add(15);
    tree.print();
    std::cout << "-------------------------------------" << std::endl;

    tree.add(85);
    tree.add(90);
    tree.print();
    std::cout << "-------------------------------------" << std::endl;

    tree.add(87);
    tree.print();
    std::cout << "-------------------------------------" << std::endl;

    tree.add(8);
    tree.print();
    std::cout << "-------------------------------------" << std::endl;

    tree.add(1);
    tree.add(12);
    tree.add(30);
    tree.add(55);
    tree.add(66);
    tree.add(100);
    tree.print();
    std::cout << "-------------------------------------" << std::endl;

    tree.add(108);
    tree.print();
    std::cout << "-------------------------------------" << std::endl;

    tree.add(5);
    tree.print();
    std::cout << "-------------------------------------" << std::endl;

    tree.add(35);
    tree.print();
    std::cout << "-------------------------------------" << std::endl;

    tree.add(40);
    tree.print();
    std::cout << "-------------------------------------" << std::endl;
    tree.add(9);
    tree.add(13);
    tree.add(2);
    tree.add(3);
    tree.add(4);
    tree.print();
    std::cout << "-------------------------------------" << std::endl;
   /*
    tree.add(16);
    tree.add(18);
    tree.add(56);
    tree.add(60);
    tree.add(47);
    tree.add(101);
    tree.add(102);
    tree.print();
    std::cout << "-------------------------------------" << std::endl;
*/

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
            case 0:
                testAdd(tree);
                break;
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

