// VAR 5
#include "array.cpp"

bool hasCorrectWord(const string& word, Array& dictionary) {
    for (size_t i = 0; i < dictionary.getSize(); ++i) {
        if (dictionary.getIndex(i) == word) {
            return true; // Слово найдено в словаре
        }
    }
    return false; // Слово не найдено в словаре
}

int countWord(const string& word) {
    int count = 0;
    for (char symbol : word) { // Цикл который перебирает каждый символ в строчке 
        if (symbol >= 'A' && symbol <= 'Z') {
            count++;
        }
    }
    return count;
}

int main() {
    int N;
    cout << "Введите количество слов в словаре: ";
    cin >> N;
    cin.ignore(); // Игнорируем остаток строки после ввода числа

    Array dictionary;
    
    for (int i = 0; i < N; ++i) { // Считываем слова в словаре
        string word;
        cout << "Введите слово: ";
        getline(cin, word);
        dictionary.addToEnd(word);
    }

    string text;
    cout << "Введите текст: ";
    getline(cin, text);

    int errorCount = 0;
    stringstream ss(text);
    string word;

    while (ss >> word) {
        int wordCount = countWord(word);
        
        if (hasCorrectWord(word, dictionary)) {
            if (wordCount != 1) { // Слово есть в словаре, проверяем его ударения
                errorCount++; // Ошибка: неправильное количество ударений
            }
        } else {
            if (wordCount != 1) { // Слово отсутствует в словаре
                errorCount++; // Ошибка: либо нет ударений, либо их больше одного
            }
        }
    }
    cout << "Количество ошибок: " << errorCount << endl;

    return 0;
}