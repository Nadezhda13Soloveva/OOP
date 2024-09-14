#include "exchanger.h"
#include <iostream>

int main() {
    std::string input;
    std::cout << "Введите строку, содержащую буквы a, b и/или c: ";
    std::getline(std::cin, input);
    std::string result = exchanger(input);
    
    std::cout << "Результат: " << result << std::endl;

    return 0;
}