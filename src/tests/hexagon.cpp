#include "../include/hexagon.h"
#include <gtest/gtest.h>
#include <sstream>

TEST(HexagonTest, DefaultConstructor) {
    Hexagon<int> hexagon;
    EXPECT_EQ(hexagon.getSize(), 0);
}

TEST(HexagonTest, ParameterConstructor) {
    Point<int> p1{0, 0}, p2{1, 0}, p3{2, 1}, p4{1, 2}, p5{0, 2}, p6{-1, 1};
    Hexagon<int> hexagon(p1, p2, p3, p4, p5, p6);

    EXPECT_EQ(hexagon.getSize(), 6);

    const Point<int>* points = hexagon.getPoints();
    EXPECT_EQ(points[0], p1);
    EXPECT_EQ(points[1], p2);
    EXPECT_EQ(points[2], p3);
    EXPECT_EQ(points[3], p4);
    EXPECT_EQ(points[4], p5);
    EXPECT_EQ(points[5], p6);
}

TEST(HexagonTest, CopyConstructor) {
    Point<int> p1{0, 0}, p2{1, 0}, p3{2, 1}, p4{1, 2}, p5{0, 2}, p6{-1, 1};
    Hexagon<int> hexagon1(p1, p2, p3, p4, p5, p6);
    Hexagon<int> hexagon2(hexagon1);

    EXPECT_EQ(hexagon1.getSize(), hexagon2.getSize());
    EXPECT_TRUE(hexagon1 == hexagon2);
}

TEST(HexagonTest, GetCenter) {
    Hexagon<double> hexagon(Point<double>(0, 0), Point<double>(1, 0), Point<double>(2, 1),
                            Point<double>(1, 2), Point<double>(0, 2), Point<double>(-1, 1));
    Point<double> center = hexagon.getCenter();

    EXPECT_DOUBLE_EQ(center.x, (0 + 1 + 2 + 1 + 0 + (-1)) / 6.0);
    EXPECT_DOUBLE_EQ(center.y, (0 + 0 + 1 + 2 + 2 + 1) / 6.0);
}

TEST(HexagonTest, GetArea) {
    Hexagon<int> hexagon(Point<int>(0, 0), Point<int>(1, 0), Point<int>(2, 1),
                         Point<int>(1, 2), Point<int>(0, 2), Point<int>(-1, 1));
    double area = hexagon.getArea();
    EXPECT_NEAR(area, 4.0, 1e-6);
}

TEST(HexagonTest, Print) {
    Hexagon<int> hexagon(Point<int>(0, 0), Point<int>(1, 0), Point<int>(2, 1),
                         Point<int>(1, 2), Point<int>(0, 2), Point<int>(-1, 1));
    std::ostringstream os;

    hexagon.print(os);
    std::string output = os.str();

    EXPECT_NE(output.find("Area"), std::string::npos);
    EXPECT_NE(output.find("(0,0)"), std::string::npos);
}

TEST(HexagonTest, Read) {
    Hexagon<int> hexagon;
    std::istringstream is("0 0 1 0 2 1 1 2 0 2 -1 1");
    hexagon.read(is);

    Point<int> p1{0, 0}, p2{1, 0}, p3{2, 1}, p4{1, 2}, p5{0, 2}, p6{-1, 1};
    const Point<int>* points = hexagon.getPoints();
    EXPECT_EQ(points[0], p1);
    EXPECT_EQ(points[1], p2);
    EXPECT_EQ(points[2], p3);
    EXPECT_EQ(points[3], p4);
    EXPECT_EQ(points[4], p5);
    EXPECT_EQ(points[5], p6);
}

TEST(HexagonTest, OperatorEquals) {
    Hexagon<int> hexagon1(Point<int>(0, 0), Point<int>(1, 0), Point<int>(2, 1),
                          Point<int>(1, 2), Point<int>(0, 2), Point<int>(-1, 1));
    Hexagon<int> hexagon2(hexagon1);
    Hexagon<int> hexagon3(Point<int>(1, 1), Point<int>(2, 1), Point<int>(3, 2),
                          Point<int>(2, 3), Point<int>(1, 3), Point<int>(0, 2));

    EXPECT_TRUE(hexagon1 == hexagon2);
    EXPECT_FALSE(hexagon1 == hexagon3);
}

TEST(HexagonTest, Clone) {
    Hexagon<int> hexagon1(Point<int>(0, 0), Point<int>(1, 0), Point<int>(2, 1),
                          Point<int>(1, 2), Point<int>(0, 2), Point<int>(-1, 1));
    auto hexagon2 = hexagon1.clone();
    EXPECT_TRUE(dynamic_cast<Hexagon<int>*>(hexagon2.get()) != nullptr);
    EXPECT_TRUE(hexagon1 == *hexagon2);
}