#ifndef set_h
#define set_h

#include "utility.h"

const size_t SIZE = 100; //Размер хэш-таблицы

struct pNode {
    int key;
    pNode* next;

     // Конструктор для удобства создания узлов
    pNode(int& k) : key(k), next(nullptr) {}
};

struct Set {
    pNode* table[SIZE];
    size_t elementCount = 0;
    Set();
    ~Set();

    void add(int key);
    bool remove(int key);
    bool haveElement(int key);
    void print();
    Set unificateWith(Set& other);
    Set interWith(Set& other);
    Set diffWith(Set& other);
};

#endif // SET_H