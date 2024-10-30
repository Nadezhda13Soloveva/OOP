#include "figures.h"
#include <cmath>
#include <stdexcept>

std::ostream& operator<<(std::ostream& os, const Figure& fig) {
    fig.print(os);
    return os;
}

bool isCollinear(const Point& a, const Point& b, const Point& c) {
    return (b.y - a.y) * (c.x - b.x) == (c.y - b.y) * (b.x - a.x);
}

double distance(const Point& a, const Point& b) {
    return std::sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

bool isRightAngle(const Point& a, const Point& b, const Point& c) {
    double ab2 = distance(a, b) * distance(a, b);
    double bc2 = distance(b, c) * distance(b, c);
    double ac2 = distance(a, c) * distance(a, c);
    return std::abs(ab2 + bc2 - ac2) < 1e-6 || std::abs(bc2 + ac2 - ab2) < 1e-6 || std::abs(ac2 + ab2 - bc2) < 1e-6;
}

Triangle::Triangle(const Point& a, const Point& b, const Point& c) : a(a), b(b), c(c) {
    validate();
}

Point Triangle::center() const {
    return Point((a.x + b.x + c.x) / 3, (a.y + b.y + c.y) / 3);
}

double Triangle::area() const {
    return std::abs((a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y)) / 2.0);
}

void Triangle::print(std::ostream& os) const {
    os << "Triangle: " << a << " " << b << " " << c;
}

bool Triangle::operator==(const Figure& other) const {
    const Triangle* t = dynamic_cast<const Triangle*>(&other);
    return t && a.x == t->a.x && a.y == t->a.y && b.x == t->b.x && b.y == t->b.y && c.x == t->c.x && c.y == t->c.y;
}

std::unique_ptr<Figure> Triangle::clone() const {
    return std::make_unique<Triangle>(*this);
}

void Triangle::validate() const {
    if (isCollinear(a, b, c)) throw std::invalid_argument("Triangle points are collinear");
}

Square::Square(const Point& a, const Point& b, const Point& c, const Point& d) : a(a), b(b), c(c), d(d) {
    validate();
}

Point Square::center() const {
    return Point((a.x + b.x + c.x + d.x) / 4, (a.y + b.y + c.y + d.y) / 4);
}

double Square::area() const {
    double side = distance(a, b);
    return side * side;
}

void Square::print(std::ostream& os) const {
    os << "Square: " << a << " " << b << " " << c << " " << d;
}

bool Square::operator==(const Figure& other) const {
    const Square* s = dynamic_cast<const Square*>(&other);
    return s && a.x == s->a.x && a.y == s->a.y && b.x == s->b.x && b.y == s->b.y && c.x == s->c.x && c.y == s->c.y && d.x == s->d.x && d.y == s->d.y;
}

std::unique_ptr<Figure> Square::clone() const {
    return std::make_unique<Square>(*this);
}

void Square::validate() const {
    double side1 = distance(a, b);
    double side2 = distance(b, c);
    double side3 = distance(c, d);
    double side4 = distance(d, a);

    if (!(std::abs(side1 - side2) < 1e-6 && std::abs(side2 - side3) < 1e-6 && std::abs(side3 - side4) < 1e-6)) {
        throw std::invalid_argument("All sides of the square must be equal");
    }

    if (!(isRightAngle(a, b, c) && isRightAngle(b, c, d) && isRightAngle(c, d, a) && isRightAngle(d, a, b))) {
        throw std::invalid_argument("All angles of the square must be right angles");
    }
}

Octagon::Octagon(const Point v[8]) {
    for (int i = 0; i < 8; ++i) vertices[i] = v[i];
    validate();
}

Point Octagon::center() const {
    double cx = 0.0, cy = 0.0;
    for (int i = 0; i < 8; ++i) {
        cx += vertices[i].x;
        cy += vertices[i].y;
    }
    return Point(cx / 8, cy / 8);
}

double Octagon::area() const {
    double sum = 0.0;
    for (int i = 0; i < 8; ++i) {
        int j = (i + 1) % 8;
        sum += (vertices[i].x * vertices[j].y - vertices[j].x * vertices[i].y);
    }
    return std::abs(sum) / 2.0;
}

void Octagon::print(std::ostream& os) const {
    os << "Octagon: ";
    for (int i = 0; i < 8; ++i) os << vertices[i] << " ";
}

bool Octagon::operator==(const Figure& other) const {
    const Octagon* o = dynamic_cast<const Octagon*>(&other);
    if (!o) return false;
    for (int i = 0; i < 8; ++i) {
        if (vertices[i].x != o->vertices[i].x || vertices[i].y != o->vertices[i].y) return false;
    }
    return true;
}

std::unique_ptr<Figure> Octagon::clone() const {
    return std::make_unique<Octagon>(*this);
}

void Octagon::validate() const {
    for (int i = 0; i < 8; ++i) {
        for (int j = i + 1; j < 8; ++j) {
            for (int k = j + 1; k < 8; ++k) {
                if (isCollinear(vertices[i], vertices[j], vertices[k])) {
                    throw std::invalid_argument("Three points of an octagon cannot be collinear");
                }
            }
        }
    }
}
