#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <vector>

template<typename K, typename V>
class Dictionary {
public:
    // Конструктор по умолчанию
    Dictionary() = default;

    // Добавление или обновление элемента
    void Add(const K& key, const V& value) {
        int index = findIndexByKey_(key);
        if (index != -1) {
            items_[index].value = value; // Обновляем значение
        }
        else {
            items_.push_back(KeyValuePair(key, value));
        }
    }

    // Удаление элемента по ключу
    void Remove(const K& key) {
        int index = findIndexByKey_(key);
        if (index != -1) {
            items_.erase(items_.begin() + index);
        }
    }

    // Проверка наличия ключа
    bool ContainsKey(const K& key) const {
        return findIndexByKey_(key) != -1;
    }

    // Получение значения по ключу (с проверкой)
    bool TryGetValue(const K& key, V& value) const {
        int index = findIndexByKey_(key);
        if (index != -1) {
            value = items_[index].value;
            return true;
        }
        return false;
    }

    // Получение количества элементов
    size_t Count() const {
        return items_.size();
    }

    // Очистка словаря
    void Clear() {
        items_.clear();
    }

    // Получение всех ключей
    std::vector<K> Keys() const {
        std::vector<K> keys;
        for (const auto& item : items_) {
            keys.push_back(item.key);
        }
        return keys;
    }

private:
    // Приватная структура для хранения пар ключ-значение
    struct KeyValuePair {
        K key;
        V value;
        KeyValuePair(const K& k, const V& v) : key(k), value(v) {}
    };

    // Приватный вспомогательный метод для поиска индекса по ключу
    int findIndexByKey_(const K& key) const {
        for (size_t i = 0; i < items_.size(); i++) {
            if (items_[i].key == key) {
                return static_cast<int>(i);
            }
        }
        return -1;
    }

    // Приватное поле с элементами словаря
    std::vector<KeyValuePair> items_;
};

#endif
