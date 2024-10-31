#ifndef ARRAY_H
#define ARRAY_H

#include <memory>
#include <stdexcept>

template<class K>
class Array {
private:
    std::shared_ptr<K[]> data;
    size_t size;
    size_t capacity;

    void resize();

public:
    Array();

    void push_back(K value);
    void remove(size_t index);
    K& operator[](size_t index);
    const K& operator[](size_t index) const;
    size_t getSize() const;
    bool isEmpty() const;
    void clear();
};



template<class K>
void Array<K>::resize() {
    capacity = capacity * 2 + 1;
    std::shared_ptr<K[]> newData(new K[capacity]);
    for (size_t i = 0; i < size; ++i) {
        newData[i] = std::move(data[i]);
    }
    data = std::move(newData);
}

template<class K>
Array<K>::Array() : data(nullptr), size(0), capacity(0) {}

template<class K>
void Array<K>::push_back(K value) {
    if (size >= capacity) {
        resize();
    }
    data[size++] = std::move(value);
}

template<class K>
void Array<K>::remove(size_t index) {
    if (index >= size) throw std::out_of_range("Index out of range");
    for (size_t i = index; i < size - 1; ++i) {
        data[i] = std::move(data[i + 1]);
    }
    --size;
}

template<class K>
K& Array<K>::operator[](size_t index) {
    if (index >= size) throw std::out_of_range("Index out of range");
    return data[index];
}

template<class K>
const K& Array<K>::operator[](size_t index) const {
    if (index >= size) throw std::out_of_range("Index out of range");
    return data[index];
}

template<class K>
size_t Array<K>::getSize() const {
    return size;
}

template<class K>
bool Array<K>::isEmpty() const {
    return size == 0;
}

template<class K>
void Array<K>::clear() {
    data.reset();
    size = 0;
    capacity = 0;
}

#endif // ARRAY_H