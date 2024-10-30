#ifndef FIGURES_H
#define FIGURES_H

#include "point.h"
#include <memory>
#include <ostream>

class Figure {
public:
    virtual ~Figure() = default;
    virtual Point center() const = 0;
    virtual double area() const = 0;
    virtual void print(std::ostream& os) const = 0;
    virtual bool operator==(const Figure& other) const = 0;
    virtual std::unique_ptr<Figure> clone() const = 0;
};

std::ostream& operator<<(std::ostream& os, const Figure& fig);

bool isCollinear(const Point& a, const Point& b, const Point& c);
double distance(const Point& a, const Point& b);
bool isRightAngle(const Point& a, const Point& b, const Point& c);

class Triangle : public Figure {
public:
    Triangle(const Point& a, const Point& b, const Point& c);
    Point center() const override;
    double area() const override;
    void print(std::ostream& os) const override;
    bool operator==(const Figure& other) const override;
    std::unique_ptr<Figure> clone() const override;

private:
    Point a, b, c;
    void validate() const;
};

class Square : public Figure {
public:
    Square(const Point& a, const Point& b, const Point& c, const Point& d);
    Point center() const override;
    double area() const override;
    void print(std::ostream& os) const override;
    bool operator==(const Figure& other) const override;
    std::unique_ptr<Figure> clone() const override;

private:
    Point a, b, c, d;
    void validate() const;
};

class Octagon : public Figure {
public:
    Octagon(const Point v[8]);
    Point center() const override;
    double area() const override;
    void print(std::ostream& os) const override;
    bool operator==(const Figure& other) const override;
    std::unique_ptr<Figure> clone() const override;

private:
    Point vertices[8];
    void validate() const;
};

#endif // FIGURES_H
