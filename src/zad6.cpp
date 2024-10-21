#include "hash_table.cpp"

pair<int, string> lengthOfLongestSubstring(const string& s) {
    Hash_table hashTable;
    int maxLength = 0;
    int start = 0; // Начало текущей подстроки
    int startIndex = 0; // Начало самой длинной подстроки

    for (int i = 0; i < s.length(); ++i) {
        string currentChar(1, s[i]);
        string indexStr;

        if (hashTable.get(currentChar, indexStr)) { // Проверяем, есть ли текущий символ в хеш-таблице
            int prevIndex = stoi(indexStr); 
            start = max(start, prevIndex + 1); // Сдвигаем начало подстроки
        }

        hashTable.insert(currentChar, to_string(i)); // Вставляем текущий символ и его индекс в хеш-таблицу
        if (i - start + 1 > maxLength) { // Обновляем максимальную длину подстроки
            maxLength = i - start + 1;
            startIndex = start; // Обновляем начало самой длинной подстроки
        }
    }

    string longestSubstring = s.substr(startIndex, maxLength); // Получаем самую длинную подстроку
    return {maxLength, longestSubstring}; // Возвращаем длину и подстроку
}

int main() {
    string input;
    cout << "Введите строку: ";
    cin >> input;

    auto [result, substring] = lengthOfLongestSubstring(input);
    cout << "Максимальная длина подстроки с уникальными символами: " << result << " (" << substring << ")" << endl;

    return 0;
}