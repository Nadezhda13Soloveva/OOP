#ifndef POINT_H
#define POINT_H

#include <iostream>

template<typename T>
class Point {
public:
    T x, y;
    Point(T x = 0, T y = 0) : x(x), y(y) {}

    bool operator==(const Point& other) const {
        return std::abs(x - other.x) < 1e-6 && std::abs(y - other.y) < 1e-6;
    }

    template<typename U>
    friend std::istream& operator>>(std::istream& is, Point<U>& p) {
        is >> p.x >> p.y;
        return is;
    }

    template<typename U>
    friend std::ostream& operator<<(std::ostream& os, const Point<U>& p) {
        os << "(" << p.x << ", " << p.y << ")";
        return os;
    }
};

#endif // POINT_H
