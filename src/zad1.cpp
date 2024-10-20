// VAR_3
#include "stack.cpp"

int priority(char arif) { //Функия для определения приоритета оператора
    if (arif == '+' || arif == '-') return 1;
    if (arif == '*' || arif == '/') return 2;
    return 0;
}

string infixToPostfix(const string& infix) { //Функция для преобразования инфиксного в постфиксное выражение
    Stack stack;
    string output;

    for(char token : infix) {
        if((token >= '0' && token <= '9') || (token >= 'a' && token <= 'z') || (token >= 'A' && token <= 'Z')) { //Проверяем если операнд цифра или буква, то добавляем его в строку
            output += token;
        } else if (token == '('){
            stack.push(string(1, token));
        } else if(token == ')') {
            while(!stack.isEmpty() && stack.peek() != "(") {
                output +=stack.pop();
            }
            stack.pop();
        } else {
            while(!stack.isEmpty() && priority(stack.peek()[0]) >= priority(token)) {
                output += stack.pop();
            }
            stack.push(string(1, token));
        } 
    }

    while(!stack.isEmpty()) {
        output += stack.pop();
    }
    return output;
}

int main() {
    string infixRecord;
    cout <<  "Ввод префиксной записи: ";
    cin >> infixRecord; cout << endl;
    string postfixRecord = infixToPostfix(infixRecord);
    cout << "Постфиксное выражение: " << postfixRecord << endl;
    
    return 0;
}