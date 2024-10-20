#ifndef arr_h
#define arr_h

#include "utility.h"

struct Array {
    string* arr;
    size_t size; //Размер массива
    size_t razmer;
     
    Array(); //Конструктор
    ~Array(); //Деструктор

    void ShowArray() const; // Вывод массива
    void addToEnd(string value); //Добавление элемента в конец массива
    void addAtIndex(size_t index, string value); // Добавление по индексу
    string getIndex(size_t index); //Получение элемента по индексу
    void removeAtIndex(size_t index); //Удаление элемента по индексу
    void replaceAtIndex(size_t index, string value);  // Замена элемента по индексу
    size_t getSize() const;
};

#endif