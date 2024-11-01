#include <gtest/gtest.h>
#include "figures.h"
#include "array.h"

// Вспомогательные из main
void printFigures(const Array& figures) {
    for (size_t i = 0; i < figures.getSize(); ++i) {
        std::cout << *figures[i] << " Center: " << figures[i]->center() << " Area: " << figures[i]->area() << "\n";
    }
}

double totalArea(const Array& figures) {
    double sum = 0.0;
    for (size_t i = 0; i < figures.getSize(); ++i) {
        sum += figures[i]->area();
    }
    return sum;
}

// Point
TEST(PointTest, DefaultConstructor) {
    Point p;
    EXPECT_EQ(p.x, 0.0);
    EXPECT_EQ(p.y, 0.0);
}

TEST(PointTest, ParameterizedConstructor) {
    Point p(1.0, 2.0);
    EXPECT_EQ(p.x, 1.0);
    EXPECT_EQ(p.y, 2.0);
}

// Distance
TEST(UtilityTest, DistanceCalculation) {
    Point a(0.0, 0.0), b(3.0, 4.0);
    EXPECT_DOUBLE_EQ(distance(a, b), 5.0);
}

// isCollinear
TEST(UtilityTest, CollinearPoints) {
    Point a(0.0, 0.0), b(1.0, 1.0), c(2.0, 2.0);
    EXPECT_TRUE(isCollinear(a, b, c));
}

TEST(UtilityTest, NonCollinearPoints) {
    Point a(0.0, 0.0), b(1.0, 1.0), c(1.0, 2.0);
    EXPECT_FALSE(isCollinear(a, b, c));
}

// Triangle
TEST(TriangleTest, ValidTriangle) {
    Point a(0.0, 0.0), b(1.0, 0.0), c(0.0, 1.0);
    Triangle t(a, b, c);
    EXPECT_DOUBLE_EQ(t.area(), 0.5);
    EXPECT_EQ(t.center().x, 1.0/3.0);
    EXPECT_EQ(t.center().y, 1.0/3.0);
}

TEST(TriangleTest, InvalidTriangle) {
    Point a(0.0, 0.0), b(1.0, 1.0), c(2.0, 2.0);
    EXPECT_THROW(Triangle(a, b, c), std::invalid_argument);
}

// Square
TEST(SquareTest, ValidSquare) {
    Point a(0.0, 0.0), b(0.0, 1.0), c(1.0, 1.0), d(1.0, 0.0);
    Square s(a, b, c, d);
    EXPECT_DOUBLE_EQ(s.area(), 1.0);
    EXPECT_EQ(s.center().x, 0.5);
    EXPECT_EQ(s.center().y, 0.5);
}

TEST(SquareTest, InvalidSquare) {
    Point a(0.0, 0.0), b(0.0, 1.0), c(1.0, 1.0), d(2.0, 0.0);
    EXPECT_THROW(Square(a, b, c, d), std::invalid_argument);
}

// Octagon
TEST(OctagonTest, ValidOctagon) {
    Point v[8] = {
        {0.0, 0.0}, {0.0, 1.0}, {1.0, 2.0}, {2.0, 2.0},
        {3.0, 1.0}, {3.0, 0.0}, {2.0, -1.0}, {1.0, -1.0}
    };
    Octagon o(v);
    EXPECT_NEAR(o.area(), 7.0, 0.1);
    EXPECT_EQ(o.center().x, 1.5);
    EXPECT_EQ(o.center().y, 0.5);
}

// Array
TEST(ArrayTest, PushBackAndAccess) {
    Array figures;
    figures.push_back(std::make_unique<Triangle>(Point(0, 0), Point(1, 0), Point(0, 1)));
    figures.push_back(std::make_unique<Square>(Point(0, 0), Point(0, 1), Point(1, 1), Point(1, 0)));
    EXPECT_DOUBLE_EQ(figures[0]->area(), 0.5);
    EXPECT_DOUBLE_EQ(figures[1]->area(), 1.0);
}

TEST(ArrayTest, Remove) {
    Array figures;
    figures.push_back(std::make_unique<Triangle>(Point(0, 0), Point(1, 0), Point(0, 1)));
    figures.push_back(std::make_unique<Square>(Point(0, 0), Point(0, 1), Point(1, 1), Point(1, 0)));
    figures.remove(0);
    EXPECT_DOUBLE_EQ(figures[0]->area(), 1.0);
    EXPECT_EQ(figures.getSize(), 1);
}

TEST(ArrayTest, OutOfRange) {
    Array figures;
    EXPECT_THROW(figures[0], std::out_of_range);
}

// printFigures
TEST(FigureTest, PrintFigures) {
    Array figures;
    figures.push_back(std::make_unique<Triangle>(Point(0, 0), Point(1, 0), Point(0, 1)));
    
    testing::internal::CaptureStdout();
    printFigures(figures);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("Triangle"), std::string::npos);
}

// totalArea
TEST(FigureTest, TotalArea) {
    Array figures;
    figures.push_back(std::make_unique<Triangle>(Point(0, 0), Point(1, 0), Point(0, 1)));
    EXPECT_DOUBLE_EQ(totalArea(figures), 0.5);
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
