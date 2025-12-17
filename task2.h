#ifndef TASK2_H
#define TASK2_H

#include <iostream>
#include <fstream>
#include <string>
#include "dictionary.h"

void solveTask2() {
    std::cout << "=== ЗАДАНИЕ 2: Мониторинг цен на сметану ===\n\n";

    // Путь к файлу по умолчанию
    std::string filename = "C:\\Users\\a987o\\Desktop\\c++\\6lub_c+++\\data.txt";

    // Открываем файл
    std::ifstream file(filename);
    if (!file.is_open()) {
        // Если файл не открылся, пробуем текущую директорию
        filename = "data.txt";
        file.open(filename);

        if (!file.is_open()) {
            std::cout << "Ошибка! Файл data.txt не найден.\n";
            std::cout << "Убедитесь, что файл находится в одной из папок:\n";
            std::cout << "1. C:\\Users\\a987o\\Desktop\\c++\\6lub_c+++\\data.txt\n";
            std::cout << "2. Текущая директория программы (data.txt)\n";
            return;
        }
    }

    // Чтение количества магазинов
    int N;
    if (!(file >> N)) {
        std::cout << "Ошибка чтения количества магазинов из файла.\n";
        file.close();
        return;
    }

    if (N <= 0) {
        std::cout << "Ошибка! Количество магазинов должно быть положительным числом.\n";
        file.close();
        return;
    }

    file.ignore(); // Пропускаем перевод строки

    Dictionary<int, int> minPrices;
    Dictionary<int, int> minPriceCount;

    int validRecords = 0;
    int invalidRecords = 0;

    // Чтение данных о магазинах
    for (int i = 0; i < N; i++) {
        std::string firm, street;
        int fat, price;

        if (!(file >> firm >> street >> fat >> price)) {
            std::cout << "Ошибка чтения данных магазина " << i + 1 << " из файла.\n";
            invalidRecords++;
            continue;
        }

        // Проверка корректности данных
        if (fat != 15 && fat != 20 && fat != 25) {
            invalidRecords++;
            continue;
        }

        if (price < 20 || price > 500) {
            invalidRecords++;
            continue;
        }

        validRecords++;

        // Обработка цены
        int currentMinPrice;
        if (minPrices.TryGetValue(fat, currentMinPrice)) {
            if (price < currentMinPrice) {
                minPrices.Add(fat, price);
                minPriceCount.Add(fat, 1);
            }
            else if (price == currentMinPrice) {
                int count;
                minPriceCount.TryGetValue(fat, count);
                minPriceCount.Add(fat, count + 1);
            }
        }
        else {
            minPrices.Add(fat, price);
            minPriceCount.Add(fat, 1);
        }
    }

    file.close();

    // Получение результатов
    int results[3] = { 0, 0, 0 };
    int fatLevels[] = { 15, 20, 25 };

    for (int i = 0; i < 3; i++) {
        int count;
        if (minPriceCount.TryGetValue(fatLevels[i], count)) {
            results[i] = count;
        }
    }

    // Вывод результатов
    std::cout << results[0] << " " << results[1] << " " << results[2] << std::endl;
}

#endif // TASK2_H
