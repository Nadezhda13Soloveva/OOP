#ifndef POINT_H
#define POINT_H

#include <iostream>

class Point {
public:
    double x, y;
    Point(double x = 0.0, double y = 0.0);

    friend std::istream& operator>>(std::istream& is, Point& p);
    friend std::ostream& operator<<(std::ostream& os, const Point& p);
};

#endif // POINT_H
