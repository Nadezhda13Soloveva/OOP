#include "array.h"

Array::Array() : data(nullptr), size(0), capacity(0) {}

Array::~Array() {
    delete[] data;
}

void Array::resize() {
    capacity = capacity * 2 + 1;
    auto newData = new std::unique_ptr<Figure>[capacity];
    for (size_t i = 0; i < size; ++i) {
        newData[i] = std::move(data[i]);
    }
    delete[] data;
    data = newData;
}

void Array::push_back(std::unique_ptr<Figure> value) {
    if (size >= capacity) {
        resize();
    }
    data[size++] = std::move(value);
}

void Array::remove(size_t index) {
    if (index >= size) throw std::out_of_range("Index out of range");
    for (size_t i = index; i < size - 1; ++i) {
        data[i] = std::move(data[i + 1]);
    }
    --size;
}

std::unique_ptr<Figure>& Array::operator[](size_t index) {
    if (index >= size) throw std::out_of_range("Index out of range");
    return data[index];
}

const std::unique_ptr<Figure>& Array::operator[](size_t index) const {
    if (index >= size) throw std::out_of_range("Index out of range");
    return data[index];
}

size_t Array::getSize() const {
    return size;
}

bool Array::isEmpty() const {
    return size == 0;
}

void Array::clear() {
    delete[] data;
    data = nullptr;
    size = 0;
    capacity = 0;
}
