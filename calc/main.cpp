#include <iostream>
#include <stack>
#include <string>
#include <sstream>

using namespace std;

double calculate(const string& expression) {
  stack<double> numbers;
  stringstream ss(expression);
  string token;

  while (getline(ss, token, ' ')) {
    if (isdigit(token[0])) { // Проверяем, является ли первый символ цифрой
      numbers.push(stod(token)); // Преобразуем строку в число и кладём в стек
    } else {
      double operand2 = numbers.top(); // Взять верхнее число из стека (второе число)
      numbers.pop(); // Удалить верхнее число
      double operand1 = numbers.top(); // Взять число, которое было под верхним (первое число)
      numbers.pop(); // Удалить это число

      switch (token[0]) {
        case '+':
          numbers.push(operand1 + operand2);
          break;
        case '-':
          numbers.push(operand1 - operand2);
          break;
        case '*':
          numbers.push(operand1 * operand2);
          break;
        case '/':
          if (operand2 == 0) {
            throw runtime_error("Деление на ноль!");
          }
          numbers.push(operand1 / operand2);
          break;
        default:
          throw runtime_error("Неверный оператор: " + token);
      }
    }
  }

  return numbers.top(); // Вернуть верхнее число (результат)
}

int main() {
  string expression;
  cout << "Введите выражение в польской нотации (числа и операторы разделены пробелами): ";
  getline(cin, expression);

  try {
    double result = calculate(expression);
    cout << "Результат: " << result << endl;
  } catch (const runtime_error& e) {
    cerr << "Ошибка: " << e.what() << endl;
    return 1;
  }

  return 0;
}
