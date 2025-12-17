#ifndef HASHSET_H
#define HASHSET_H

#include <vector>
#include <algorithm>

template<typename T>
class HashSet {
private:
    std::vector<T> elements;

    // Приватный вспомогательный метод для поиска индекса элемента
    int findIndex(const T& item) const {
        auto it = std::find(elements.begin(), elements.end(), item);
        if (it != elements.end()) {
            return static_cast<int>(std::distance(elements.begin(), it));
        }
        return -1;
    }

public:
    // Конструктор по умолчанию
    HashSet() = default;

    // Конструктор из списка инициализации
    HashSet(std::initializer_list<T> init) {
        for (const auto& item : init) {
            Add(item);
        }
    }

    // Добавление элемента (если он уникален)
    void Add(const T& item) {
        if (!Contains(item)) {
            elements.push_back(item);
        }
    }

    // Удаление элемента
    void Remove(const T& item) {
        int index = findIndex(item);
        if (index != -1) {
            elements.erase(elements.begin() + index);
        }
    }

    // Объединение двух коллекций
    HashSet<T> Union(const HashSet<T>& other) const {
        HashSet<T> result = *this;
        for (const auto& item : other.elements) {
            result.Add(item);
        }
        return result;
    }

    // Разность коллекций (элементы из this, которых нет в other)
    HashSet<T> Except(const HashSet<T>& other) const {
        HashSet<T> result;
        for (const auto& item : elements) {
            if (!other.Contains(item)) {
                result.Add(item);
            }
        }
        return result;
    }

    // Пересечение коллекций
    HashSet<T> Intersect(const HashSet<T>& other) const {
        HashSet<T> result;
        for (const auto& item : elements) {
            if (other.Contains(item)) {
                result.Add(item);
            }
        }
        return result;
    }

    // Проверка наличия элемента
    bool Contains(const T& item) const {
        return findIndex(item) != -1;
    }

    // Получение размера коллекции
    size_t Size() const {
        return elements.size();
    }

    // Получение всех элементов (для вывода)
    std::vector<T> GetElements() const {
        return elements;
    }

    // Очистка коллекции
    void Clear() {
        elements.clear();
    }
};

#endif // HASHSET_H
