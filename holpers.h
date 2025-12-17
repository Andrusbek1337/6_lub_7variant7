#ifndef HELPERS_H
#define HELPERS_H

#include <iostream>
#include <limits>

void clearInputBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int getPositiveInt(const std::string& prompt) {
    int value;
    while (true) {
        std::cout << prompt;
        std::cin >> value;

        if (std::cin.fail() || value < 0) {
            std::cout << "Ошибка! Введите целое положительное число.\n";
            clearInputBuffer();
        }
        else {
            clearInputBuffer();
            return value;
        }
    }
}

#endif // HELPERS_H
