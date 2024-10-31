#include "figures.h"
#include "array.h"
#include <iostream>
#include <memory>

void printFigures(const Array& figures) {
    for (size_t i = 0; i < figures.getSize(); ++i) {
        std::cout << *figures[i] << " Center: " << figures[i]->center() << " Area: " << figures[i]->area() << "\n";
    }
}

double totalArea(const Array& figures) {
    double sum = 0.0;
    for (size_t i = 0; i < figures.getSize(); ++i) {
        sum += figures[i]->area();
    }
    return sum;
}

int main() {
    Array figures;

    while (true) {
        std::cout << "Enter command (t - triangle, s - square, o - octagon, i - info, d - delete, q - quit): ";
        std::string command;
        std::cin >> command;

        if (command == "q") {
            break;
        } else if (command == "t") {
            Point a, b, c;
            std::cout << "Enter 3 points for the triangle (x y for each point): ";
            std::cin >> a >> b >> c;
            try {
                figures.push_back(std::make_unique<Triangle>(a, b, c));
            } catch (const std::invalid_argument& e) {
                std::cerr << "Error: " << e.what() << "\n";
            }
        } else if (command == "s") {
            Point a, b, c, d;
            std::cout << "Enter 4 points for the square (x y for each point): ";
            std::cin >> a >> b >> c >> d;
            try {
                figures.push_back(std::make_unique<Square>(a, b, c, d));
            } catch (const std::invalid_argument& e) {
                std::cerr << "Error: " << e.what() << "\n";
            }
        } else if (command == "o") {
            Point vertices[8];
            std::cout << "Enter 8 points for the octagon (x y for each point): ";
            for (int i = 0; i < 8; ++i) {
                std::cin >> vertices[i];
            }
            try {
                figures.push_back(std::make_unique<Octagon>(vertices));
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
