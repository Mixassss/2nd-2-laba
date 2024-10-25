#include "../include/set.h"

Set::Set() : elementCount(0) {
  for(size_t i = 0; i < SIZE; ++i) {
    table[i] = nullptr; //Присваиванпие каждой ноды, нулевого значения
  }
}

Set::~Set() {
  for (size_t i = 0; i < SIZE; ++i) {
    pNode* current = table[i];
    while (current != nullptr) {
      pNode* toDelete = current;
      current = current->next; // Освобождение каждой ноды
      delete toDelete;
    }
  }
}

size_t hashFunction(int key) {
  hash<int> hasher;
  return hasher(key) % SIZE;
}

void Set::add(int key) {
  if (haveElement(key)) return; // Проверка наличия элемента перед добавлением

  size_t hashValue = hashFunction(key); // Хэш значение для этого ключа
  pNode* newPair = new pNode(key); // Создаем новый узел

  if (table[hashValue] == nullptr) {
    table[hashValue] = newPair; // Если ячейка пуста, вставляем новый элемент
    elementCount++;
  } else {
    pNode* current = table[hashValue];
    pNode* previous = nullptr;

    while (current != nullptr && current->key < key) { // Пробегаем по узлам, пока не найдем правильное место для вставки
      previous = current;
      current = current->next;
    }

    if (previous == nullptr) { // Вставка нового узла в нужное место
      newPair->next = table[hashValue]; // Вставляем в начало списка
      table[hashValue] = newPair; 
      } else {
        newPair->next = current; // Вставляем между предыдущим и текущим узлом
        previous->next = newPair;
      }
    elementCount++;
  }
}

bool Set::remove(int key) {
  size_t index = hashFunction(key);
  pNode* current = table[index];
  pNode* previous = nullptr;

  while (current != nullptr) {
    if (current->key == key) {
      if (previous == nullptr) {
        table[index] = current->next; // Удаляем первый узел в списке
      } else {
        previous->next = current->next; // Удаляем узел из середины или конца
      }
      delete current; // Освобождаем память
      elementCount--;
      return true; // Элемент успешно удален
    }
    previous = current;
    current = current->next;
  }
  return false; // Элемент не найден
}

bool Set::haveElement(int key) {
  size_t index = hashFunction(key);
  pNode* current = table[index];
  while(current != nullptr) {
    if(current->key == key) {
      return true; // Элемент найден
    }
    current = current->next;
  }
  return false; // Элемент не найден
}

void Set::print() {
  cout << "{";
  bool first = true; // Флаг для проверки первого элемента
  for (size_t i = 0; i < SIZE; ++i) {
    pNode* current = table[i];
    while (current != nullptr) {
      if (!first) {
        cout << ", "; // Добавляем запятую перед следующими элементами
      }
      cout << current->key;
      first = false; // Устанавливаем флаг в false после первого элемента
      current = current->next;
    }
  }
  cout << "}" << endl; // Закрываем скобку
}