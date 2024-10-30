#include "vector.h"

template<typename T>
Vector<T>::Vector() : data(nullptr), size(0), capacity(0) {}

template<typename T>
Vector<T>::~Vector() {
    delete[] data;
}

template<typename T>
void Vector<T>::push_back(T value) {
    if (size >= capacity) {
        resize();
    }
    data[size++] = std::move(value);
}

template<typename T>
void Vector<T>::remove(size_t index) {
    if (index >= size) throw std::out_of_range("Index out of range");
    for (size_t i = index; i < size - 1; ++i) {
        data[i] = std::move(data[i + 1]);
    }
    --size;
}

template<typename T>
T& Vector<T>::operator[](size_t index) {
    if (index >= size) throw std::out_of_range("Index out of range");
    return data[index];
}

template<typename T>
const T& Vector<T>::operator[](size_t index) const {
    if (index >= size) throw std::out_of_range("Index out of range");
    return data[index];
}

template<typename T>
size_t Vector<T>::getSize() const {
    return size;
}

template<typename T>
bool Vector<T>::isEmpty() const {
    return size == 0;
}

template<typename T>
void Vector<T>::clear() {
    delete[] data;
    data = nullptr;
    size = 0;
    capacity = 0;
}

template<typename T>
void Vector<T>::resize() {
    capacity = capacity * 2 + 1;
    T* newData = new T[capacity];
    for (size_t i = 0; i < size; ++i) {
        newData[i] = std::move(data[i]);
    }
    delete[] data;
    data = newData;
}

