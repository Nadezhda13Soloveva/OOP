#ifndef FIGURES_H
#define FIGURES_H

#include "point.h"
#include <memory>
#include <cmath>
#include <stdexcept>
#include <iostream>

// FIGURE
template<IsScalar T>
class Figure {
public:
    virtual ~Figure() = default;
    virtual Point<T> center() const = 0;
    virtual double area() const = 0;
    virtual void print(std::ostream& os) const = 0;
    virtual bool operator==(const Figure& other) const = 0;
    virtual std::unique_ptr<Figure<T>> clone() const = 0;
};

template<IsScalar T>
std::ostream& operator<<(std::ostream& os, const Figure<T>& fig) {
    fig.print(os);
    return os;
}



template<IsScalar T>
bool isCollinear(const Point<T>& a, const Point<T>& b, const Point<T>& c) {
    return (b.y - a.y) * (c.x - b.x) == (c.y - b.y) * (b.x - a.x);
}

template<IsScalar T>
double distance(const Point<T>& a, const Point<T>& b) {
    return std::sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

template<IsScalar T>
bool isRightAngle(const Point<T>& a, const Point<T>& b, const Point<T>& c) {
    double ab2 = distance(a, b) * distance(a, b);
    double bc2 = distance(b, c) * distance(b, c);
    double ac2 = distance(a, c) * distance(a, c);
    return std::abs(ab2 + bc2 - ac2) < 1e-6 || std::abs(bc2 + ac2 - ab2) < 1e-6 || std::abs(ac2 + ab2 - bc2) < 1e-6;
}


// TRIANGLE
template<IsScalar T>
class Triangle : public Figure<T> {
private:
    std::unique_ptr<Point<T>> a, b, c;

    void validate() const {
        if (isCollinear(*a, *b, *c)) throw std::invalid_argument("Triangle points are collinear");
    }

public:
    Triangle(const Point<T>& a, const Point<T>& b, const Point<T>& c)
        : a(std::make_unique<Point<T>>(a)), b(std::make_unique<Point<T>>(b)), c(std::make_unique<Point<T>>(c)) {
        validate();
    }
    Triangle(const Triangle& other)
        : a(std::make_unique<Point<T>>(*other.a)), b(std::make_unique<Point<T>>(*other.b)), c(std::make_unique<Point<T>>(*other.c)) {}
    Triangle(Triangle&& other) noexcept
        : a(std::move(other.a)), b(std::move(other.b)), c(std::move(other.c)) {}
    Triangle& operator=(Triangle other) {
        std::swap(a, other.a);
        std::swap(b, other.b);
        std::swap(c, other.c);
        return *this;
    }

    Point<T> center() const override {
        return Point<T>((a->x + b->x + c->x) / 3, (a->y + b->y + c->y) / 3);
    }

    double area() const override {
        return std::abs((a->x * (b->y - c->y) + b->x * (c->y - a->y) + c->x * (a->y - b->y)) / 2.0);
    }

    void print(std::ostream& os) const override {
        os << "Triangle: " << *a << " " << *b << " " << *c;
    }

    bool operator==(const Figure<T>& other) const override {
        const Triangle* t = dynamic_cast<const Triangle*>(&other);
        return t && a->x == t->a->x && a->y == t->a->y &&
               b->x == t->b->x && b->y == t->b->y &&
               c->x == t->c->x && c->y == t->c->y;
    }

    std::unique_ptr<Figure<T>> clone() const override {
        return std::make_unique<Triangle>(*this);
    }
};


// SQUARE
template<IsScalar T>
class Square : public Figure<T> {
private:
    std::unique_ptr<Point<T>> a, b, c, d;
    void validate() const {
        double side1 = distance(*a, *b);
        double side2 = distance(*b, *c);
        double side3 = distance(*c, *d);
        double side4 = distance(*d, *a);

        if (!(std::abs(side1 - side2) < 1e-6 && std::abs(side2 - side3) < 1e-6 && std::abs(side3 - side4) < 1e-6)) {
            throw std::invalid_argument("All sides of the square must be equal");
        }

        if (!(isRightAngle(*a, *b, *c) && isRightAngle(*b, *c, *d) && isRightAngle(*c, *d, *a) && isRightAngle(*d, *a, *b))) {
            throw std::invalid_argument("All angles of the square must be right angles");
        }
    }

public:
    Square(const Point<T>& a, const Point<T>& b, const Point<T>& c, const Point<T>& d)
        : a(std::make_unique<Point<T>>(a)), b(std::make_unique<Point<T>>(b)), c(std::make_unique<Point<T>>(c)), d(std::make_unique<Point<T>>(d)) {
        validate();
    }
    Square(const Square& other)
        : a(std::make_unique<Point<T>>(*other.a)), b(std::make_unique<Point<T>>(*other.b)), c(std::make_unique<Point<T>>(*other.c)), d(std::make_unique<Point<T>>(*other.d)) {}
    Square(Square&& other) noexcept
        : a(std::move(other.a)), b(std::move(other.b)), c(std::move(other.c)), d(std::move(other.d)) {}
    Square& operator=(Square other) {
        std::swap(a, other.a);
        std::swap(b, other.b);
        std::swap(c, other.c);
        std::swap(d, other.d);
        return *this;
    }

    Point<T> center() const override {
        return Point<T>((a->x + b->x + c->x + d->x) / 4, (a->y + b->y + c->y + d->y) / 4);
    }

    double area() const override {
        double side = distance(*a, *b);
        return side * side;
    }

    void print(std::ostream& os) const override {
        os << "Square: " << *a << " " << *b << " " << *c << " " << *d;
    }

    bool operator==(const Figure<T>& other) const override {
        const Square* s = dynamic_cast<const Square*>(&other);
        return s && a->x == s->a->x && a->y == s->a->y &&
               b->x == s->b->x && b->y == s->b->y &&
               c->x == s->c->x && c->y == s->c->y &&
               d->x == s->d->x && d->y == s->d->y;
    }

    std::unique_ptr<Figure<T>> clone() const override {
        return std::make_unique<Square>(*this);
    }
};


// OCTAGON
template<IsScalar T>
class Octagon : public Figure<T> {
private:
    std::unique_ptr<Point<T>> vertices[8];
    void validate() const {
        for (int i = 0; i < 8; ++i) {
            for (int j = i + 1; j < 8; ++j) {
                for (int k = j + 1; k < 8; ++k) {
                    if (isCollinear(*vertices[i], *vertices[j], *vertices[k])) {
                        throw std::invalid_argument("Three points of an octagon cannot be collinear");
                    }
                }
            }
        }
    }

public:
    Octagon(const Point<T> v[8]) {
        for (int i = 0; i < 8; ++i) vertices[i] = std::make_unique<Point<T>>(v[i]);
        validate();
    }
    Octagon(const Octagon& other) {
        for (int i = 0; i < 8; ++i) vertices[i] = std::make_unique<Point<T>>(*other.vertices[i]);
    }
    Octagon(Octagon&& other) noexcept {
        for (int i = 0; i < 8; ++i) vertices[i] = std::move(other.vertices[i]);
    }
    Octagon& operator=(Octagon other) {
        for (int i = 0; i < 8; ++i) {
            std::swap(vertices[i], other.vertices[i]);
        }
        return *this;
    }

    Point<T> center() const override {
        double cx = 0.0, cy = 0.0;
        for (int i = 0; i < 8; ++i) {
            cx += vertices[i]->x;
            cy += vertices[i]->y;
        }
        return Point<T>(cx / 8, cy / 8);
    }

    double area() const override {
        double sum = 0.0;
        for (int i = 0; i < 8; ++i) {
            int j = (i + 1) % 8;
            sum += (vertices[i]->x * vertices[j]->y - vertices[j]->x * vertices[i]->y);
        }
        return std::abs(sum) / 2.0;
    }

    void print(std::ostream& os) const override {
        os << "Octagon: ";
        for (int i = 0; i < 8; ++i) os << *vertices[i] << " ";
    }

    bool operator==(const Figure<T>& other) const override {
        const Octagon* o = dynamic_cast<const Octagon*>(&other);
        if (!o) return false;
        for (int i = 0; i < 8; ++i) {
            if (vertices[i]->x != o->vertices[i]->x || vertices[i]->y != o->vertices[i]->y)
                return false;
        }
        return true;
    }

    std::unique_ptr<Figure<T>> clone() const override {
        return std::make_unique<Octagon>(*this);
    }
};

#endif // FIGURES_H

