#include "../include/set.h"

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

Set setReadFile(string& path, string& name) {
  Set nums; // Предполагается, что у вас есть конструктор по умолчанию для Set
  ifstream fin(path);
  if (!fin.is_open()) {
    cout << "Не удалось открыть файл для чтения" << endl;
    return nums; // Возвращаем пустое множество, если не удалось открыть файл
  }

  string str;
  while (getline(fin, str)) {
    stringstream ss(str);
    string tokens;
    getline(ss, tokens, ' ');
    if (tokens == name) { // Если строка соответствует имени структуры
      int key;
      while (ss >> key) { // Читаем все ключи из строки
        nums.add(key);
      }
      break; // Прерываем цикл после нахождения нужной структуры
    }
  }
  fin.close();
  return nums; // Возвращаем считанное множество
}

string printHashTable( Set& set, string& name) { // Функция для перебора всех элементов хеш-таблицы
  string str = name + ' ';
  bool first = true; // Флаг для управления запятыми
  for (int i = 0; i < SIZE; ++i) {
    pNode* current = set.table[i];
    while (current) {
      if (!first) {
        str += ' '; // Добавляем пробел перед элементом, если это не первый элемент
      }
      str += to_string(current->key);
      current = current->next;
      first = false; // После первого элемента флаг меняется
    }
  }
  return str;
}

void SETADD (string& name, string& value, string& path) {
  string textfull = Ftext(path, name);
  Set nums = setReadFile(path, name);

  int key = stoi(value);
  nums.add(key);
    
  textfull += printHashTable(nums, name); // Получаем строку со всеми элементами множества
  write(path, textfull); // Записываем обновленное состояние в файл
} 

void SETDEL (string& name, string& path, string& value) {
  Set data = setReadFile(path, name);

  if (data.elementCount == 0) {
    throw out_of_range("Ошибка: нет такого списка или он пуст");
  }
  int key = stoi(value);
  if (!data.remove(key)) { // Удаляем элемент из множества
    cerr << "Ошибка: элемент " << key << " не найден в множестве." << endl;
    return; // Если элемент не найден, просто выходим
  }

  string textfull = Ftext(path, name); // Формируем текст для записи в файл без удаленного элемента

  string str = name + ' '; // Добавляем обновленное множество в текст
  for (int i = 0; i < SIZE; ++i) {
    pNode* current = data.table[i];
      while (current) {
        str += to_string(current->key) + ' '; // Добавляем пробел между элементами
        current = current->next;
      }
    }
  textfull += str;
  write(path, textfull); // Записываем обновленное состояние в файл
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

  if (query.empty()) { // Обработка команды
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