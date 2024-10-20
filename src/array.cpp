#include "../include/arr.h"

Array::Array() : size(0), razmer(10) {
    arr = new string[razmer];
}
Array::~Array() {
    delete[] arr; //Освобождение места
}
void Array::ShowArray() const {
    for (size_t i = 0; i < size; ++i) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

void Array::addToEnd(string value) {
    string *newArr = new string[size + 1]; //Добавление нового массива, который увеличен на 1
    for (size_t i = 0; i < size; ++i)
    {
        newArr[i] = arr[i];
    }
    delete[] arr;
    arr = newArr;
    arr[size++] = value;//Увеличение длины массива   
}

void Array::addAtIndex(size_t index, string value) {
    if (index > size) return;
    string *newArr = new string[size + 1];
    for (size_t i = 0; i < index; ++i) {
        newArr[i] = arr[i];
    }
    newArr[index] = value;
    for (size_t i = index; i < size; ++i) {
        newArr[i + 1] = arr[i];
    }
    delete[] arr;
    arr = newArr;
    size++;
    }

string Array::getIndex(size_t index) {
    if (index >= size) {
        throw out_of_range("Index out of range");
    }
    return arr[index];
}
    
void Array::removeAtIndex(size_t index) {
    if (index >= size) return;
    string *newArr = new string[size - 1];
    for(size_t i = 0; i < index; ++i) {
            newArr[i] = arr[i];
    }
    for(size_t i = index + 1; i < size; ++i) {
        newArr[i - 1] = arr[i];
    }
    delete[] arr;
    arr = newArr;
    size--;
}

void Array::replaceAtIndex(size_t index, string value) {
    if(index >= size) return;
    arr[index] = value; //Замена элемента
}

size_t Array::getSize() const {
    return size;
}