#include "point.h"
#include "figures.h"
#include "array.h"
#include <iostream>
#include <string>

template class Triangle<double>;
template class Square<double>;
template class Octagon<double>;
template class Array<std::shared_ptr<Figure<double>>>;

template<typename T>
void printFigures(const Array<std::shared_ptr<Figure<T>>>& figures) {
    for (size_t i = 0; i < figures.getSize(); ++i) {
        std::cout << *figures[i] << " Center: " << figures[i]->center() << " Area: " << figures[i]->area() << "\n";
    }
}

template<typename T>
double totalArea(const Array<std::shared_ptr<Figure<T>>>& figures) {
    double sum = 0.0;
    for (size_t i = 0; i < figures.getSize(); ++i) {
        sum += figures[i]->area();
    }
    return sum;
}


int main() {
    Array<std::shared_ptr<Figure<double>>> figures;

    while (true) {
        std::cout << "Enter command (t - triangle, s - square, o - octagon, i - info, d - delete, q - quit): ";
        std::string command;
        std::cin >> command;

        if (command == "q") {
            break;
        } else if (command == "t") {
            Point<double> a, b, c;
            std::cout << "Enter 3 points for the triangle (x y for each point): ";
            std::cin >> a >> b >> c;
            try {
                figures.push_back(std::make_shared<Triangle<double>>(a, b, c));
            } catch (const std::invalid_argument& e) {
                std::cerr << "Error: " << e.what() << "\n";
            }
        } else if (command == "s") {
            Point<double> a, b, c, d;
            std::cout << "Enter 4 points for the square (x y for each point): ";
            std::cin >> a >> b >> c >> d;
            try {
                figures.push_back(std::make_shared<Square<double>>(a, b, c, d));
            } catch (const std::invalid_argument& e) {
                std::cerr << "Error: " << e.what() << "\n";
            }
        } else if (command == "o") {
            Point<double> vertices[8];
            std::cout << "Enter 8 points for the octagon (x y for each point): ";
            for (int i = 0; i < 8; ++i) {
                std::cin >> vertices[i];
            }
            try {
                figures.push_back(std::make_shared<Octagon<double>>(vertices));
            } catch (const std::invalid_argument& e) {
                std::cerr << "Error: " << e.what() << "\n";
            }
        } else if (command == "i") {
            std::cout << "\nAll figures:\n";
            printFigures(figures);
            std::cout << "Total area of all figures: " << totalArea(figures) << "\n";
        } else if (command == "d") {
            std::cout << "Enter index of figure to remove: ";
            int index;
            std::cin >> index;

            if (index >= 0 && index < figures.getSize()) {
                figures.remove(index);
                std::cout << "Figure at index " << index << " removed.\n";
            } else {
                std::cerr << "Index out of range. Please try again.\n";
            }
        } else {
            std::cerr << "Unknown command. Please try again.\n";
        }
    }

    figures.clear();
    return 0;
}
