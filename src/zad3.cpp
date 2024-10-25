// VAR 3
#include "../include/set.h"

Set Set::unificateWith(Set& diff) { // Функция объденения двух множеств
    Set result; // Создаем новое множество для результата

    for (size_t i = 0; i < SIZE; ++i) { // Добавляем элементы из текущего множества
        pNode* current = table[i];
        while (current != nullptr) {
            result.add(current->key);
            current = current->next;
        }
    }

    for (size_t i = 0; i < SIZE; ++i) { // Добавляем элементы из другого множества
        pNode* current = diff.table[i];
        while (current != nullptr) {
            result.add(current->key);
            current = current->next;
        }
    }
    return result;
}

Set Set::interWith(Set& other) {
    Set result;

    for (size_t i = 0; i < SIZE; ++i) {
        pNode* current = table[i];
        while (current != nullptr) {
            if (other.haveElement(current->key)) { // Если элемент в множестве есть
                result.add(current->key); // То выводим повторяющийся элемент
            }
            current = current->next; // Перемещаемся к следующему элементу
        }
    }
    return result; // Возвращаем результат
}

Set Set::diffWith(Set& other) {
    Set result;

    for (size_t i = 0; i < SIZE; ++i) {
        pNode* current = table[i];
        while (current != nullptr) {
            if (!other.haveElement(current->key)) { // Если элемента нет во втором множестве
                result.add(current->key);
            }
            current = current->next;
        }
    }
    return result;
}

int main() {
Set set1;
    int element;

    cout << "Введите элементы для первого множества: ";
    while (cin >> element && element != 0) {
        set1.add(element);
    }

    Set set2;

    cout << "Введите элементы для второго множества: ";
    while (cin >> element && element != 0) {
        set2.add(element);
    }

    cout << "Первое множество: ";
    set1.print();

    cout << "Второе множество: ";
    set2.print();

    Set unifSet = set1.unificateWith(set2);
    Set interSet = set1.interWith(set2);
    Set diffSet = set1.diffWith(set2);

    cout << "Объединение множеств: ";
    unifSet.print();

    cout << "Пересечение множеств: ";
    interSet.print();

    cout << "Разность множеств: ";
    diffSet.print();

    return 0;
}