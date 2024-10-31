#ifndef ARRAY_H
#define ARRAY_H

#include <memory>
#include <stdexcept>
#include "figures.h" 

class Array {
private:
    std::unique_ptr<Figure>* data;
    size_t size;
    size_t capacity;

    void resize();

public:
    Array();
    ~Array();

    void push_back(std::unique_ptr<Figure> value);
    void remove(size_t index);
    std::unique_ptr<Figure>& operator[](size_t index);
    const std::unique_ptr<Figure>& operator[](size_t index) const;

    size_t getSize() const;
    bool isEmpty() const;
    void clear();
};

#endif // ARRAY_H
