#include "../include/stack.h"

Stack::Stack(size_t size) : capacity(size), head(-1) {
    data = new string[capacity];
}

Stack::Stack() : capacity(10), head(-1) { // Например, установить начальную емкость 10
    data = new string[capacity];
}

Stack::~Stack() {
    delete[] data;
}

void Stack::push(string value) {
    if (head == capacity - 1) {
        throw overflow_error("Стек переполнен.");
    }
    data[++head] = value; // Добавление элемента и увеличение индекса
}

string Stack::pop() {
    if (head == -1) {
        throw underflow_error("Стек пустой.");
    }
    return data[head--]; // Возврат элемента и уменьшение индекса
}

 string Stack::peek() {
    if(head == -1) {
        throw underflow_error("Стек пустой.");
    }
    return data[head];
}

bool Stack::isEmpty() {
    return head == -1;
}

size_t Stack::size() {
    return head + 1;
}