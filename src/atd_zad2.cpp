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

size_t hashFunction(int& key) {
  hash<int> hasher;
  return hasher(key) % SIZE;
}

void Set::add(int& key) {
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
    if (current != nullptr && current->key == key) { // Если текущий узел имеет тот же ключ, ничего не делаем
      delete newPair; // Удаляем временный узел
      return;
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

void Set::remove(int& key) {
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
            return;
        }
        previous = current;
        current = current->next;
    }
}

bool Set::haveElement(int& key) {
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
  for(size_t i = 0; i < SIZE; ++i) { // Инициализация переменной i
    pNode* current = table[i];
    while(current != nullptr) {
      cout << current->key << " ";
      current = current->next;
    }
  }
  cout << endl;
}

void printUsage( char* programName) {
    cerr << "Использование: " << programName << " --file <filename> --query '<command>'" << endl;
}

string Ftext(string& path, string& nameStruct) { // Функция сохранения фулл текста файла без нужной структуры
  string str, text;
  ifstream fin;
  fin.open(path);

  while (getline(fin, str)) { // Сохранение фулл текста в переменную
    stringstream ss(str);
    string tokens;
    getline(ss, tokens, ' ');
    if (tokens != nameStruct) {
      text += str + "\n";
    }
  }

  fin.close();
  return text;
}

void write(string& path, string& text) { // Функция записи данных в файл
  ofstream fout(path);
  if (!fout.is_open()) {
    cout << "Не удалось открыть файл для записи" << endl;
    return;
  }
  fout << text;
  fout.close();
}

Set setReadFile(string& path, string& nameStruct) {
  Set data;
  string str;

  ifstream fin(path);
  if (!fin.is_open()) {
    cout << "Не удалось открыть файл для чтения" << endl;
    return data; // Возвращаем пустой массив, если не удалось открыть файл
  }

  while (getline(fin, str)) {
    stringstream ss(str);
    string tokens;
    getline(ss, tokens, ' ');
    if (tokens == nameStruct) { // Проверяем на совпадение с нужной структурой
      while (getline(ss, tokens, ' ')) {
                int position = tokens.find_first_of(':');
                tokens.replace(position, 1, " ");
                stringstream iss(tokens);
                int key;
                iss >> key;
                data.add(key);
            }
    }
  }
  fin.close();
  return data;
}

string printHashTable( Set& set, string& name) { // Функция для перебора всех элементов хеш-таблицы
    string str = name + ' ';
    for (int i = 0; i < SIZE; ++i) {
        pNode* current = set.table[i];
        while (current) {
            str += to_string(current->key) + ':';
            current = current->next;
        }
    }
    return str;
}

void SETADD (string& name, string& value, string& path) {
  string textfull = Ftext(path, name);
    Set nums = setReadFile(path, name);
    
    string str;
    if (nums.elementCount != 0) {
      int key = stoi(value);
        nums.add(key);
        textfull += printHashTable(nums, name);
        write(path, textfull);
    } else {
        int key = stoi(value);
        textfull += name + ' ' + to_string(key) + ':' + value + "\n";
        write(path, textfull);
    }
}

void SETDEL (string& name, string& path, string& value) {
  Set data = setReadFile(path, name);
    
  if (data.elementCount == 0) {
    throw out_of_range("Ошибка: нет такого списка или он пуст");
  }

  int key = stoi(value);
    data.remove(key);
    
    string textfull = Ftext(path, name);
    
    string str = name + ' ';
    pNode* current = data.table[hashFunction(key)];
    
    while (current) {
        str += to_string(current->key) + ' ';
        current = current->next;
    }
    
    textfull += str;
    write(path, textfull);
}

bool SETHAS(string& name, string& path, string& value) {
    Set data = setReadFile(path, name); // Читаем множество из файла
    int key = stoi(value); // Преобразование строки в int
    return data.haveElement(key); // Проверяем наличие элемента
}

void SETPRINT( string& name,  string& filename) {
  Set data = setReadFile(filename, name);

  if (data.elementCount != 0) {
    data.print();
  } else {
      throw out_of_range("Ошибка, нет такого списка или он пуст");
  }
}

void setMenu(string& command, string& path) {
  string name, value;

  if (command.substr(0, 7) == "SETADD ") {
    string cons = command.substr(7);
    stringstream stream(cons);
    stream >> name >> value;
    SETADD(name, value, path);
  } else if (command.substr(0, 7) == "SETDEL ") {
    string cons = command.substr(7);
    stringstream stream(cons);
    stream >> name >> value;
    SETDEL(name, path, value);
  } else if (command.substr(0, 7) == "SETHAS ") {
    string cons = command.substr(7);
    stringstream stream(cons);
    stream >> name >> value;
    bool hasElement = SETHAS(name, path, value); // Получаем результат
    cout << (hasElement ? "Элемент найден." : "Элемент не найден.") << endl; // Выводим результат
  } else if (command.substr(0, 9) == "SETPRINT ") {
    string cons = command.substr(9);
    stringstream stream(cons);
    stream >> name;
    SETPRINT(name, path);
  } else {
    throw out_of_range("Ошибка: нет такой команды");
  }
}

int main(int argc, char* argv[]) {
   if (argc != 5) {
        printUsage(argv[0]);
        return 1;
    }

    string filename; // Разбор аргументов командной строки
    string query;

    for (int i = 1; i < argc; i++) {
        if (string(argv[i]) == "--file") {
            if (++i < argc) {
                filename = argv[i];
            } else {
                printUsage(argv[0]);
                return 1;
            }
        } else if (string(argv[i]) == "--query") {
            if (++i < argc) {
                query = argv[i];
            } else {
                printUsage(argv[0]);
                return 1;
            }
        }
    }

    // Обработка команды
    if (query.empty()) {
        cout << "Ошибка: Должна быть указана команда." << endl;
        return 1;
    }

    switch (query[0]) {
        case 'S':
            setMenu(query, filename);
            break;
        default:
            cout << "Ошибка: Неизвестная структура данных." << endl;
            return 1;
    }

    return 0;
}