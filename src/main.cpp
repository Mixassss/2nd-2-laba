#include "../include/atd.h"

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
        data.add(tokens); // Добавляем элементы в множество
      }
    }
  }
  fin.close();
  return data;
}

void SETADD (string& name, string& value, string& path) {
  string textfull = Ftext(path, name);
  Set data = setReadFile(path, name);

  if (!data.isEmpty()) {
    data.add(value);
    string str = name + ' ';
    pNode* current = data.getHead(); // Значение текущего элемента
    while (current) {
      str += current->data + ' ';
      current = current->next;
      }
    textfull += str;
    write(path, textfull);
  } else {
      string str = name + ' ' + value;
      write(path, str); // перезаписываем новый элемент
  }
}

void SETDEL (string& name, string& path, string& value) {
  Set data = setReadFile(path, name);
    
  if (data.isEmpty()) {
    throw out_of_range("Ошибка: нет такого списка или он пуст");
  }

  data.remove(value);
    
  string textfull = Ftext(path, name);
    
  string str = name + ' ';
  pNode* current = data.getHead();
  while (current) {
    str += current->data + ' ';
    current = current->next;
  }
    
  textfull += str;
  write(path, textfull);
}

bool SETHAS(string& name, string& path, string& value) {
    Set data = setReadFile(path, name); // Читаем множество из файла
    return data.haveElement(value); // Проверяем наличие элемента
}

void SETPRINT( string& name,  string& filename) {
  Set data = setReadFile(filename, name);

  if (!data.isEmpty()) {
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

  // Разбор аргументов командной строки
    for (int i = 1; i < argc; i++) {
        if (string(argv[i]) == "--file") {
            filename = argv[++i];
        } else if (string(argv[i]) == "--query") {
            query = argv[++i];
        }
    }

    try {
        setMenu(query, filename); // Вызываем меню с запросом
    } catch (const exception& e) {
        cerr << e.what() << endl; // Выводим ошибку
        return 1;
    }

    return 0;
}