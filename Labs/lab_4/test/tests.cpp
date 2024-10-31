#include <gtest/gtest.h>
#include "figures.h"
#include "array.h"

template class Triangle<double>;
template class Square<double>;
template class Octagon<double>;
template class Array<std::shared_ptr<Figure<double>>>;


// Вспомогательные из main
template<typename T>
void printFigures(const Array<std::shared_ptr<Figure<T>>>& figures) {
    for (size_t i = 0; i < figures.getSize(); ++i) {
        std::cout << *figures[i] << " Center: " << figures[i]->center() << " Area: " << figures[i]->area() << "\n";
    }
}

template<typename T>
double totalArea(const Array<std::shared_ptr<Figure<T>>>& figures) {
    double sum = 0.0;
    for (size_t i = 0; i < figures.getSize(); ++i) {
        sum += figures[i]->area();
    }
    return sum;
}


// Point
TEST(PointTest, DefaultConstructor) {
    Point<double> p;
    EXPECT_EQ(p.x, 0.0);
    EXPECT_EQ(p.y, 0.0);
}

TEST(PointTest, ParameterizedConstructor) {
    Point<double> p(3.0, 4.0);
    EXPECT_EQ(p.x, 3.0);
    EXPECT_EQ(p.y, 4.0);
}

// Triangle
TEST(TriangleTest, ValidTriangle) {
    Point<double> a(0.0, 0.0);
    Point<double> b(1.0, 0.0);
    Point<double> c(0.0, 1.0);
    Triangle<double> triangle(a, b, c);
    EXPECT_DOUBLE_EQ(triangle.area(), 0.5);
    EXPECT_EQ(triangle.center(), Point<double>(1.0/3.0, 1.0/3.0));
}

TEST(TriangleTest, CollinearPoints) {
    Point<double> a(0.0, 0.0);
    Point<double> b(1.0, 1.0);
    Point<double> c(2.0, 2.0);
    EXPECT_THROW(Triangle<double> triangle(a, b, c), std::invalid_argument);
}


// Square
TEST(SquareTest, ValidSquare) {
    Point<double> a(0.0, 0.0);
    Point<double> b(1.0, 0.0);
    Point<double> c(1.0, 1.0);
    Point<double> d(0.0, 1.0);
    Square<double> square(a, b, c, d);
    EXPECT_DOUBLE_EQ(square.area(), 1.0);
    EXPECT_EQ(square.center(), Point<double>(0.5, 0.5));
}

TEST(SquareTest, InvalidSquare) {
    Point<double> a(0.0, 0.0);
    Point<double> b(2.0, 0.0);
    Point<double> c(2.0, 1.0);
    Point<double> d(0.0, 1.0);
    EXPECT_THROW(Square<double> square(a, b, c, d), std::invalid_argument);
}


// Octagon
TEST(OctagonTest, ValidOctagon) {
    Point<double> vertices[8] = {
        Point<double>(1.0, 0.0),
        Point<double>(2.0, 0.0),
        Point<double>(3.0, 1.0),
        Point<double>(3.0, 2.0),
        Point<double>(2.0, 3.0),
        Point<double>(1.0, 3.0),
        Point<double>(0.0, 2.0),
        Point<double>(0.0, 1.0)
    };
    Octagon<double> octagon(vertices);
    EXPECT_NEAR(octagon.area(), 7.0, 1e-6);
}

TEST(OctagonTest, CollinearPointsInOctagon) {
    Point<double> vertices[8] = {
        Point<double>(0.0, 0.0),
        Point<double>(1.0, 1.0),
        Point<double>(2.0, 2.0),
        Point<double>(3.0, 3.0),
        Point<double>(4.0, 4.0),
        Point<double>(5.0, 5.0),
        Point<double>(6.0, 6.0),
        Point<double>(7.0, 7.0)
    };
    EXPECT_THROW(Octagon<double> octagon(vertices), std::invalid_argument);
}


// Array
TEST(ArrayTest, AddAndRemoveFigures) {
    Array<std::shared_ptr<Figure<double>>> figures;
    Point<double> a(0.0, 0.0);
    Point<double> b(1.0, 0.0);
    Point<double> c(0.0, 1.0);
    figures.push_back(std::make_shared<Triangle<double>>(a, b, c));
    EXPECT_EQ(figures.getSize(), 1);
    figures.remove(0);
    EXPECT_EQ(figures.getSize(), 0);
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
