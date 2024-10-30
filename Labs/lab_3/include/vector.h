#ifndef VECTOR_H
#define VECTOR_H

#include <cstddef>
#include <stdexcept>
#include <utility>

template<typename T>
class Vector {
public:
    Vector();
    ~Vector();
    void push_back(T value);
    void remove(size_t index);
    T& operator[](size_t index);
    const T& operator[](size_t index) const;
    size_t getSize() const;
    bool isEmpty() const;
    void clear();

private:
    T* data;
    size_t size;
    size_t capacity;
    void resize();
};

#include "../src/vector.tpp"

#endif // VECTOR_H
