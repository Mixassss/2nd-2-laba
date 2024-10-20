#ifndef stack_h
#define stack_h

#include "utility.h"

struct Stack{

    string* data;
    int head;
    int capacity; //Вместимост стека

    Stack(size_t size);
    Stack();
    ~Stack();

    void push(string value); //Функция добавления
    string pop(); //Функция удаление элемента и возврат значения
    string peek(); // Функция удаления верхнего элемента
    bool isEmpty();
    size_t size();
};

#endif // STACK_H