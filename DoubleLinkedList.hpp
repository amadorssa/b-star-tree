
#ifndef DOUBLELINKEDLIST_HPP
#define DOUBLELINKEDLIST_HPP
#define NOT_FOUND -1

/**
 * @file DoubleLinkedList.hpp
 * @brief Define una clase de lista doblemente enlazada genérica.
 * 
 * Esta clase implementa una lista doblemente enlazada que permite la inserción,
 * eliminación y búsqueda de elementos. Los elementos pueden ser de cualquier tipo
 * definido por el usuario, gracias al uso de plantillas.
 * @author Manuel Gortarez
 * @author Alan Torres
 */

template <typename T>
class DoubleLinkedList {
public:
    /**
     * @brief Constructor por defecto.
     * 
     * Inicializa una lista doblemente enlazada vacía.
     */
    DoubleLinkedList();

    /**
     * @brief Destructor.
     * 
     * Libera toda la memoria asociada con la lista doblemente enlazada.
     */
    ~DoubleLinkedList();

    /**
     * @brief Constructor de copia.
     * @param l La lista doblemente enlazada desde la cual se copiará.
     */
    DoubleLinkedList(const DoubleLinkedList &l);

    /**
     * @brief Operador de asignación.
     * @param l La lista doblemente enlazada a asignar.
     * @return Referencia a esta lista doblemente enlazada.
     */
    DoubleLinkedList &operator=(const DoubleLinkedList &l);

    /**
     * @brief Añade un elemento al principio de la lista.
     * @param v El valor a añadir.
     */
    void addFront(T v);

    /**
     * @brief Añade un elemento al final de la lista.
     * @param v El valor a añadir.
     */
    void addBack(T v);

    /**
     * @brief Añade un elemento en un índice específico.
     * @param v El valor a añadir.
     * @param index La posición donde se añadirá el valor.
     */
    void add(T v, const int index);

    /**
     * @brief Elimina el primer elemento de la lista.
     */
    void removeFront();

    /**
     * @brief Elimina el último elemento de la lista.
     */
    void removeBack();

    /**
     * @brief Elimina un elemento en un índice específico.
     * @param index La posición del elemento a eliminar.
     */
    void remove(const int index);

    /**
     * @brief Busca un valor en la lista.
     * @param v El valor a buscar.
     * @return True si el valor está en la lista, false en caso contrario.
     */
    bool searchValue(T v) const;

    /**
     * @brief Busca el índice de un valor en la lista.
     * @param v El valor a buscar.
     * @return El índice del primer elemento con el valor dado, o NOT_FOUND si no se encuentra.
     */
    int searchIndex(T v) const;

    /**
     * @brief Verifica si la lista está vacía.
     * @return True si la lista está vacía, false en caso contrario.
     */
    bool isEmpty() const;

    /**
     * @brief Obtiene el valor del primer elemento de la lista.
     * @return El valor del primer elemento.
     */
    T getFront() const;

    /**
     * @brief Obtiene el valor del último elemento de la lista.
     * @return El valor del último elemento.
     */
    T getBack() const;

    /**
     * @brief Acceso al elemento en un índice específico (const).
     * @param index El índice del elemento a acceder.
     * @return Una referencia constante al elemento en el índice especificado.
     */
    T &operator[](const int index) const;

    /**
     * @brief Acceso al elemento en un índice específico (no const).
     * @param index El índice del elemento a acceder.
     * @return Una referencia al elemento en el índice especificado.
     */
    T &operator[](const int index);

    /**
     * @brief Modifica el valor de un elemento en un índice específico.
     * @param v El nuevo valor para el elemento.
     * @param index El índice del elemento a modificar.
     */
    void modify(T v, const int index);

    /**
     * @brief Obtiene el tamaño de la lista.
     * @return El número de elementos en la lista.
     */
    int getSize() const;

    /**
     * @brief Elimina todos los elementos de la lista.
     */
    void empty();
/**
     * @brief Imprime los elementos de la lista en orden.
     * 
     * Recorre la lista desde el principio hasta el final, imprimiendo cada elemento.
     * Esta función es principalmente útil para propósitos de depuración.
     */
    void print() const;

    /**
     * @brief Imprime los elementos de la lista en orden inverso.
     * 
     * Recorre la lista desde el final hasta el principio, imprimiendo cada elemento.
     * Esta función es principalmente útil para propósitos de depuración.
     */
    void printReverse() const;

    /**
     * @brief Ordena los elementos de la lista.
     * 
     * Ordena los elementos de la lista en un orden específico, dependiendo de la implementación.
     * Nota: La implementación del ordenamiento no se especifica aquí.
     */
    void sort();

    /**
     * @brief Transfiere elementos de otra lista a esta lista, comenzando desde un índice específico.
     * @param l La lista desde la cual se transferirán los elementos.
     * @param index El índice en la lista `l` desde el cual comenzará la transferencia.
     * 
     * Los elementos se añaden al final de esta lista.
     */
    void transferFromIndex(DoubleLinkedList &l, int index);

    /**
     * @brief Transfiere un rango de elementos de otra lista a esta lista.
     * @param l La lista desde la cual se transferirán los elementos.
     * @param start El índice inicial en la lista `l` desde el cual comenzará la transferencia.
     * @param end El índice final en la lista `l` hasta donde se realizará la transferencia.
     * 
     * Los elementos se añaden al final de esta lista.
     */
    void transferIndexToIndex(DoubleLinkedList &l, int start, int end);

    /**
     * @brief Transfiere todos los elementos de otra lista a esta lista.
     * @param l La lista desde la cual se transferirán todos los elementos.
     * 
     * Los elementos de la lista `l` se añaden al final de esta lista. La lista `l` quedará vacía después de la operación.
     */
    void transferList(DoubleLinkedList &l);

private:
    int size; ///< Almacena el número de elementos en la lista.
    struct Element {
        Element(T v, Element *nxt = nullptr, Element *prv = nullptr); ///< Constructor del elemento.
        T value; ///< Valor almacenado en el elemento.
        Element *next, *previous; ///< Punteros al siguiente y anterior elemento en la lista, respectivamente.
    } *front, *back; ///< Punteros al primer y último elemento de la lista, respectivamente.
};

#include "DoubleLinkedList.tpp"

#endif // DOUBLELINKEDLIST_HPP
