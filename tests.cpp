#include <gtest/gtest.h>
#include <memory>
#include <sstream>
#include <cmath>
#include "include/Point.h"
#include "include/Figure.h"
#include "include/Rhombus.h"
#include "include/Trapezoid.h"
#include "include/Pentagon.h"
#include "include/Array.h"

// ===== Тесты Point =====
TEST(PointTest, ConstructionAndAccess) {
    Point<int> p(3, -2);
    EXPECT_EQ(p.getX(), 3);
    EXPECT_EQ(p.getY(), -2);
}

TEST(PointTest, Equality) {
    Point<double> p1(1.5, 2.5);
    Point<double> p2(1.5, 2.5);
    Point<double> p3(1.5, 3.5);
    EXPECT_TRUE(p1 == p2);
    EXPECT_FALSE(p1 == p3);
}

// ===== Тесты Rhombus =====
TEST(RhombusTest, CenterAndArea) {
    Rhombus<double> r{
        Point<double>(0, 0),
        Point<double>(2, 0),
        Point<double>(1, 1),
        Point<double>(-1, 1)
    };

    Point<double> cen = r.getCenter();
    EXPECT_NEAR(cen.getX(), 0.5, 1e-6);
    EXPECT_NEAR(cen.getY(), 0.5, 1e-6);

    double area = static_cast<double>(r);
    EXPECT_NEAR(area, 2.0, 1e-6);
}

TEST(RhombusTest, CloneAndEquality) {
    Rhombus<int> r1{Point<int>(0,0), Point<int>(1,0), Point<int>(1,1), Point<int>(0,1)};
    auto r2 = r1.clone();
    EXPECT_TRUE(r1 == *r2);
}

TEST(RhombusTest, StreamIO) {
    Rhombus<double> r{Point<double>(1,2), Point<double>(3,4), Point<double>(5,6), Point<double>(7,8)};
    std::stringstream ss;
    ss << r;
    EXPECT_EQ(ss.str(), "1 2 3 4 5 6 7 8");

    Rhombus<double> r2{Point<double>(0,0), Point<double>(0,0), Point<double>(0,0), Point<double>(0,0)};
    ss >> r2;
    EXPECT_TRUE(static_cast<const Figure<double>&>(r) == r2);
}

// ===== Тесты Trapezoid =====
TEST(TrapezoidTest, Area) {
    Trapezoid<int> t{
        Point<int>(0, 0),
        Point<int>(4, 0),
        Point<int>(3, 2),
        Point<int>(1, 2)
    };
    EXPECT_NEAR(static_cast<double>(t), 6.0, 1e-6);
}

// ===== Тесты Pentagon =====
TEST(PentagonTest, CenterIsNearZero) {
    // Правильный пятиугольник на единичной окружности
    const double PI = std::acos(-1.0);
    Pentagon<double> p{
        Point<double>(std::cos(0),           std::sin(0)),
        Point<double>(std::cos(2*PI/5),      std::sin(2*PI/5)),
        Point<double>(std::cos(4*PI/5),      std::sin(4*PI/5)),
        Point<double>(std::cos(6*PI/5),      std::sin(6*PI/5)),
        Point<double>(std::cos(8*PI/5),      std::sin(8*PI/5))
    };
    Point<double> cen = p.getCenter();
    EXPECT_NEAR(cen.getX(), 0.0, 1e-10);
    EXPECT_NEAR(cen.getY(), 0.0, 1e-10);
}

// ===== Тесты Array =====
TEST(ArrayTest, PushBackAndAccess) {
    Array<int> arr;
    arr.push_back(std::make_shared<int>(10));
    arr.push_back(std::make_shared<int>(20));
    EXPECT_EQ(arr.getSize(), 2);
    EXPECT_EQ(arr[0], 10);
    EXPECT_EQ(arr[1], 20);
}

TEST(ArrayTest, RemoveAt) {
    Array<double> arr;
    arr.push_back(std::make_shared<double>(1.1));
    arr.push_back(std::make_shared<double>(2.2));
    arr.push_back(std::make_shared<double>(3.3));
    arr.remove_at(1);
    EXPECT_EQ(arr.getSize(), 2);
    EXPECT_DOUBLE_EQ(arr[0], 1.1);
    EXPECT_DOUBLE_EQ(arr[1], 3.3);
}

TEST(ArrayTest, PolymorphicFigures) {
    Array<Figure<double>> figs;
    figs.push_back(std::make_shared<Rhombus<double>>(
        Point<double>(0,0), Point<double>(1,0), Point<double>(1,1), Point<double>(0,1)
    ));
    figs.push_back(std::make_shared<Trapezoid<double>>(
        Point<double>(0,0), Point<double>(2,0), Point<double>(1.5,1), Point<double>(0.5,1)
    ));

    EXPECT_EQ(figs.getSize(), 2);
    EXPECT_NEAR(static_cast<double>(figs[0]), 1.0, 1e-6);  // площадь квадрата
    EXPECT_NEAR(static_cast<double>(figs[1]), 1.5, 1e-6);  // (2+1)/2 * 1 = 1.5
}