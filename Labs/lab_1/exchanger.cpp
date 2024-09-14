#include "exchanger.h"
#include <iostream>

std::string exchanger(std::string input) {
    int len = input.length();
    if (len == 0) {
        return "\nОшибка: Введена пустая строка.";  
    }

    std::string result; 
    for (int i = 0; i < len; i++) {
        if (input[i] != 'a' && input[i] != 'b' && input[i] != 'c' 
        && input[i] != 'A' && input[i] != 'B' && input[i] != 'C') {
            return "\nОшибка: строка содержит недопустимый символ. Используйте только a, b и c.";  // Возвращаем сообщение об ошибке
        } else {
            if (input[i] == 'a') {
                result += 'b';  
            } else if (input[i] == 'b') {
                result += 'a';  
            } else if (input[i] == 'A') {
                result += 'B';  
            } else if (input[i] == 'B') {
                result += 'A';  
            } else if (input[i] == 'C') {
                result += 'C';  
            } else {
                result += 'c';  
            }
        }
    }
    return result;  
}