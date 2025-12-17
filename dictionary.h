#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <vector>

template<typename K, typename V>
class Dictionary {
private:
    struct KeyValuePair {
        K key;
        V value;
        KeyValuePair(const K& k, const V& v) : key(k), value(v) {}
    };

    std::vector<KeyValuePair> items;

    // Приватный вспомогательный метод для поиска индекса по ключу
    int findIndexByKey(const K& key) const {
        for (size_t i = 0; i < items.size(); i++) {
            if (items[i].key == key) {
                return static_cast<int>(i);
            }
        }
        return -1;
    }

public:
    // Конструктор по умолчанию
    Dictionary() = default;

    // Добавление или обновление элемента
    void Add(const K& key, const V& value) {
        int index = findIndexByKey(key);
        if (index != -1) {
            items[index].value = value; // Обновляем значение
        }
        else {
            items.push_back(KeyValuePair(key, value));
        }
    }

    // Удаление элемента по ключу
    void Remove(const K& key) {
        int index = findIndexByKey(key);
        if (index != -1) {
            items.erase(items.begin() + index);
        }
    }

    // Проверка наличия ключа
    bool ContainsKey(const K& key) const {
        return findIndexByKey(key) != -1;
    }

    // Получение значения по ключу (с проверкой)
    bool TryGetValue(const K& key, V& value) const {
        int index = findIndexByKey(key);
        if (index != -1) {
            value = items[index].value;
            return true;
        }
        return false;
    }

    // Получение количества элементов
    size_t Count() const {
        return items.size();
    }

    // Очистка словаря
    void Clear() {
        items.clear();
    }

    // Получение всех ключей
    std::vector<K> Keys() const {
        std::vector<K> keys;
        for (const auto& item : items) {
            keys.push_back(item.key);
        }
        return keys;
    }
};

#endif // DICTIONARY_H
