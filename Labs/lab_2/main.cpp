#include <iostream>
#include "five.h"

int main() {
    try {
        
        Five num1("1234");
        std::cout << "Number 1: " << num1 << std::endl;

        Five num2(5, 3); 
        std::cout << "Number 2: " << num2 << std::endl;

        Five num3 = {1, 2, 3, 4};
        std::cout << "Number 3: " << num3 << std::endl;

        Five num4 = num1;
        std::cout << "Number 4 (copy of Number 1): " << num4 << std::endl;

        Five num5 = std::move(num2); // num2 теперь не должен использоваться
        std::cout << "Number 5 (moved from Number 2): " << num5 << std::endl;
        std::cout << "Number 2 (deleted): " << num2 << std::endl;


        Five sum = num1 + num3;
        std::cout << "Sum of Number 1 and Number 3: " << sum << std::endl;

        try {
            Five diff = num3 - num1;
            std::cout << "Difference of Number 3 and Number 1: " << diff << std::endl;
        } catch (const std::invalid_argument &e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }

        if (num1 < num3) {
            std::cout << "Number 1 is less than Number 3" << std::endl;
        } else if (num1 > num3) {
            std::cout << "Number 1 is greater than Number 3" << std::endl;
        } else {
            std::cout << "Number 1 is equal to Number 3" << std::endl;
        }

    } catch (const std::exception &e) {
        std::cerr << "An error occurred: " << e.what() << std::endl;
    }

    return 0;
}
