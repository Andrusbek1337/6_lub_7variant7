#ifndef TASK1_H
#define TASK1_H

#include <iostream>
#include <string>
#include <vector>
#include "hashset.h"
#include "helpers.h"

void solveTask1() {
    std::cout << "=== ЗАДАНИЕ 1: Анализ предпочтений сладкоежек ===\n\n";

    // Ввод количества сладкоежек
    int n = getPositiveInt("Введите количество сладкоежек: ");

    // Создаем массивы HashSet для каждого сладкоежки
    std::vector<HashSet<std::string>> likedChocolates(n);
    std::vector<HashSet<std::string>> dislikedChocolates(n);
    
    // Множество всех упомянутых видов шоколада
    HashSet<std::string> allMentionedChocolates;

    // Ввод данных для каждого сладкоежки
    for (int i = 0; i < n; i++) {
        std::cout << "\n=== Сладкоежка " << (i + 1) << " ===\n";
        
        // Ввод ЛЮБИМОГО шоколада
        int m_liked = getPositiveInt("Введите количество ЛЮБИМЫХ видов шоколада: ");

        if (m_liked > 0) {
            std::cout << "Введите названия ЛЮБИМОГО шоколада:\n";
            for (int j = 0; j < m_liked; j++) {
                std::string chocolate;
                std::cout << "  " << j + 1 << ": ";
                std::getline(std::cin, chocolate);
                
                if (chocolate.empty()) {
                    std::cout << "Ошибка! Название не может быть пустым. Попробуйте снова.\n";
                    j--;
                    continue;
                }
                
                likedChocolates[i].Add(chocolate);
                allMentionedChocolates.Add(chocolate);
            }
        }

        // Ввод НЕЛЮБИМОГО шоколада
        int m_disliked = getPositiveInt("\nВведите количество НЕЛЮБИМЫХ видов шоколада: ");

        if (m_disliked > 0) {
            std::cout << "Введите названия НЕЛЮБИМОГО шоколада:\n";
            for (int j = 0; j < m_disliked; j++) {
                std::string chocolate;
                std::cout << "  " << j + 1 << ": ";
                std::getline(std::cin, chocolate);
                
                if (chocolate.empty()) {
                    std::cout << "Ошибка! Название не может быть пустым. Попробуйте снова.\n";
                    j--;
                    continue;
                }
                
                dislikedChocolates[i].Add(chocolate);
                allMentionedChocolates.Add(chocolate);
                
                // Автоматически удаляем из любимых, если был добавлен туда же
                likedChocolates[i].Remove(chocolate);
            }
        }
    }

    // ШАГ 1: Находим шоколад, который нравится ВСЕМ
    HashSet<std::string> likedByAll;
    if (n > 0) {
        likedByAll = likedChocolates[0];
        for (int i = 1; i < n; i++) {
            likedByAll = likedByAll.Intersect(likedChocolates[i]);
        }
        
        // Исключаем те, что кто-то не любит
        for (int i = 0; i < n; i++) {
            likedByAll = likedByAll.Except(dislikedChocolates[i]);
        }
    }

    // ШАГ 2: Находим шоколад, который нравится НЕКОТОРЫМ
    // Это все шоколады, которые кто-то любит (хотя бы один), но не все
    HashSet<std::string> likedBySome;
    
    // Собираем все шоколады, которые кто-то любит
    for (const auto& chocolate : allMentionedChocolates.GetElements()) {
        bool someoneLikes = false;
        
        for (int i = 0; i < n; i++) {
            if (likedChocolates[i].Contains(chocolate)) {
                someoneLikes = true;
                break;
            }
        }
        
        if (someoneLikes) {
            likedBySome.Add(chocolate);
        }
    }
    
    // Исключаем те, что нравятся всем
    likedBySome = likedBySome.Except(likedByAll);

    // ШАГ 3: Находим шоколад, который НЕ нравится НИКОМУ
    HashSet<std::string> dislikedByAll;
    
    if (n > 0) {
        dislikedByAll = dislikedChocolates[0];
        for (int i = 1; i < n; i++) {
            dislikedByAll = dislikedByAll.Intersect(dislikedChocolates[i]);
        }
    }

    // ШАГ 5: Вывод результатов
    std::cout << "\n=== РЕЗУЛЬТАТЫ ===\n";
    
    // 1. Шоколад, который нравится ВСЕМ
    std::cout << "\n1. Шоколад, который нравится ВСЕМ:\n";
    auto allLiked = likedByAll.GetElements();
    if (allLiked.empty()) {
        std::cout << "   нет\n";
    } else {
        for (const auto& chocolate : allLiked) {
            std::cout << "   " << chocolate << std::endl;
        }
    }
    
    // 2. Шоколад, который нравится НЕКОТОРЫМ
    std::cout << "\n2. Шоколад, который нравится НЕКОТОРЫМ:\n";
    auto someLiked = likedBySome.GetElements();
    if (someLiked.empty()) {
        std::cout << "   нет\n";
    } else {
        for (const auto& chocolate : someLiked) {
            std::cout << "   " << chocolate << std::endl;
        }
    }
    
    // 3. Шоколад, который НЕ нравится НИКОМУ
    std::cout << "\n3. Шоколад, который НЕ нравится НИКОМУ:\n";
    auto noneLiked = dislikedByAll.GetElements();
    if (noneLiked.empty()) {
        std::cout << "   нет\n";
    } else {
        for (const auto& chocolate : noneLiked) {
            std::cout << "   " << chocolate << std::endl;
        }
    }
    
    std::cout << std::endl;
}

#endif
