// Обратная польская запись — форма записи математических и логических выражений, в которой операнды расположены перед знаками операций

#include <cctype>
#include <iostream>
#include <vector>

int main() {
  std::string s;
  getline(std::cin, s);
  std::vector<int> stack;

  for (char c : s) {
    if (isdigit(c) != 0) {
      stack.push_back(c - '0');
    } else if (c != ' ') {
      if (stack.size() < 2) {
        std::cerr << "Недопустимое постфиксное выражение. Недостаточно операндов." << std::endl;
        return 1;
      }
      int y = stack.back();
      stack.pop_back();
      int x = stack.back();
      stack.pop_back();

      if (c == '+') {
        stack.push_back(x + y);
      } else if (c == '-') {
        stack.push_back(x - y);
      } else if (c == '*') {
        stack.push_back(x * y);
      } else if (c == '/') {
        if (y == 0) {
            std::cerr << "Деление на ноль не осуществляется." << std::endl;
          return 1;
        }
        stack.push_back(x / y);
      } else {
        std::cerr << "Неверный оператор: " << c << std::endl;
        return 1;
      }
    }
  }

  if (stack.size() != 1) {
    std::cerr << "Недопустимое постфиксное выражение. Слишком много операндов." << std::endl;
    return 1;
  }

  std::cout << stack.back() << "\n";
  return 0;
}
