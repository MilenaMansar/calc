#include <iostream>
#include <stack>
#include <string>
#include <sstream>

using namespace std;

double calculate(const string& expression) {
  stack<double> numbers; // Создаем стек, чтобы хранить числа
  stringstream ss(expression); // Разделяем выражение на части
  string token; // Временная переменная для хранения частей выражения

  while (getline(ss, token, ' ')) { // Проходим по частям выражения, разделенным пробелами
    if (isdigit(token[0])) { // Проверяем, является ли первый символ цифрой
      numbers.push(stod(token)); // Преобразуем строку в число и добавляем в стек
    } else {
      double operand2 = numbers.top(); // Берем верхнее число из стека (второе число)
      numbers.pop(); // Удаляем верхнее число из стека
      double operand1 = numbers.top(); // Берем число, которое было под верхним (первое число)
      numbers.pop(); // Удаляем это число

      switch (token[0]) { // Выполняем операцию в зависимости от символа
        case '+':
          numbers.push(operand1 + operand2); // Складываем числа
          break;
        case '-':
          numbers.push(operand1 - operand2); // Вычитаем числа
          break;
        case '*':
          numbers.push(operand1 * operand2); // Умножаем числа
          break;
        case '/':
          if (operand2 == 0) { // Проверяем, чтобы не делить на ноль
            throw runtime_error("Деление на ноль!"); // Ошибка!
          }
          numbers.push(operand1 / operand2); // Делим числа
          break;
        default:
          throw runtime_error("Неверный оператор: " + token); // Ошибка!
      }
    }
  }

  return numbers.top(); // Возвращаем результат, который остался в стеке
}

int main() {
  string expression;
  cout << "Введите выражение в польской нотации (числа и операторы разделены пробелами): ";
  getline(cin, expression); // Читаем выражение из консоли

  try {
    double result = calculate(expression); // Вычисляем выражение
    cout << "Результат: " << result << endl; // Выводим результат
  } catch (const runtime_error& e) {
    cerr << "Ошибка: " << e.what() << endl; // Выводим ошибку
    return 1; // Возвращаем код ошибки
  }

  return 0; // Возвращаем 0, если все прошло нормально
}
