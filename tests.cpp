#include "BStarTree.hpp"
#include <iostream>

bool testSplit(){
    // Crear un arbol vacio de enteros de orden 5
    BStarTree<int, 5> tree;

    // PROBAR SPLIT DE NODO HOJA
    tree.add(59);
    tree.add(23);
    tree.add(7);
    tree.add(77);

    // El arbol impreso deberia ser 7,23,59,77
    tree.printByLevels();

    tree.add(73); // <- Sobrecarga el nodo raiz

    //      (59)
    // (7,23) (73,77)
    tree.printByLevels();

    tree.add(67);
    tree.add(19);
    tree.add(79);
    tree.add(61); // <- Sobrecarga el hijo derecho

    //         (59      73)
    // (7,19,23) (61,67) (77,79)
    tree.printByLevels();

    /**************************************************************************/

    // PROBAR SPLIT DE NODO RAIZ
    tree.add(40);
    tree.add(38); // <- Sobrecarga el nodo 

    //      (23      59      73)
    // (7,19) (38,40) (61,67) (77,79)
    tree.printByLevels();

    tree.add(80);
    tree.add(85);
    tree.add(90); // <- Sobrecarga el nodo

    //      (23      59      73      80)
    // (7,19) (38,40) (61,67) (77,79) (85,90)
    tree.add(25);
    tree.add(31);
    tree.add(35); // <- Sobrecarga el nodo, lo que provoca un split que a su vez sobrecarga el nodo raiz

    //                       59
    //       (23     35)             (73      80)
    //  (7,19) (25,31) (38,40) (61,67) (77,79) (85,90)
}

bool testMerge(){
    
}


int main() {

    if (testSplit())
        std::cout << "Split test passed" << std::endl;
    else
        std::cout << "Split test failed" << std::endl;

    return 0;
}
    