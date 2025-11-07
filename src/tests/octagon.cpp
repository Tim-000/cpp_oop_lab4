#include "../include/octagon.h"
#include <gtest/gtest.h>
#include <sstream>

TEST(OctagonTest, DefaultConstructor) {
    Octagon<int> octagon;
    EXPECT_EQ(octagon.getSize(), 0);
}

TEST(OctagonTest, ParameterConstructor) {
    Point<int> p1{0, 0}, p2{1, 0}, p3{2, 1}, p4{2, 2}, p5{1, 3}, p6{0, 3}, p7{-1, 2}, p8{-1, 1};
    Octagon<int> octagon(p1, p2, p3, p4, p5, p6, p7, p8);

    EXPECT_EQ(octagon.getSize(), 8);

    const Point<int>* points = octagon.getPoints();
    EXPECT_EQ(points[0], p1);
    EXPECT_EQ(points[1], p2);
    EXPECT_EQ(points[2], p3);
    EXPECT_EQ(points[3], p4);
    EXPECT_EQ(points[4], p5);
    EXPECT_EQ(points[5], p6);
    EXPECT_EQ(points[6], p7);
    EXPECT_EQ(points[7], p8);
}

TEST(OctagonTest, CopyConstructor) {
    Point<int> p1{0, 0}, p2{1, 0}, p3{2, 1}, p4{2, 2}, p5{1, 3}, p6{0, 3}, p7{-1, 2}, p8{-1, 1};
    Octagon<int> octagon1(p1, p2, p3, p4, p5, p6, p7, p8);
    Octagon<int> octagon2(octagon1);

    EXPECT_EQ(octagon1.getSize(), octagon2.getSize());
    EXPECT_TRUE(octagon1 == octagon2);
}

TEST(OctagonTest, GetCenter) {
    Octagon<double> octagon(Point<double>(0, 0), Point<double>(1, 0), Point<double>(2, 1),
                            Point<double>(2, 2), Point<double>(1, 3), Point<double>(0, 3),
                            Point<double>(-1, 2), Point<double>(-1, 1));
    Point<double> center = octagon.getCenter();

    EXPECT_DOUBLE_EQ(center.x, (0 + 1 + 2 + 2 + 1 + 0 + -1 + -1) / 8.0);
    EXPECT_DOUBLE_EQ(center.y, (0 + 0 + 1 + 2 + 3 + 3 + 2 + 1) / 8.0);
}

TEST(OctagonTest, GetArea) {
    Octagon<int> octagon(Point<int>(0, 0), Point<int>(1, 0), Point<int>(2, 1), Point<int>(2, 2),
                         Point<int>(1, 3), Point<int>(0, 3), Point<int>(-1, 2), Point<int>(-1, 1));

    double area = octagon.getArea();
    EXPECT_NEAR(area, 7.0, 1e-6);
}

TEST(OctagonTest, Print) {
    Octagon<int> octagon(Point<int>(0, 0), Point<int>(1, 0), Point<int>(2, 1), Point<int>(2, 2),
                         Point<int>(1, 3), Point<int>(0, 3), Point<int>(-1, 2), Point<int>(-1, 1));
    std::ostringstream os;

    octagon.print(os);
    std::string output = os.str();

    EXPECT_NE(output.find("Area"), std::string::npos);
    EXPECT_NE(output.find("(0,0)"), std::string::npos);
}

TEST(OctagonTest, Read) {
    Octagon<int> octagon;
    std::istringstream is("0 0 1 0 2 1 2 2 1 3 0 3 -1 2 -1 1");
    octagon.read(is);

    Point<int> p1{0, 0}, p2{1, 0}, p3{2, 1}, p4{2, 2}, p5{1, 3}, p6{0, 3}, p7{-1, 2}, p8{-1, 1};
    const Point<int>* points = octagon.getPoints();
    EXPECT_EQ(points[0], p1);
    EXPECT_EQ(points[1], p2);
    EXPECT_EQ(points[2], p3);
    EXPECT_EQ(points[3], p4);
    EXPECT_EQ(points[4], p5);
    EXPECT_EQ(points[5], p6);
    EXPECT_EQ(points[6], p7);
    EXPECT_EQ(points[7], p8);
}

TEST(OctagonTest, OperatorEquals) {
    Octagon<int> octagon1(Point<int>(0, 0), Point<int>(1, 0), Point<int>(2, 1), Point<int>(2, 2),
                          Point<int>(1, 3), Point<int>(0, 3), Point<int>(-1, 2), Point<int>(-1, 1));
    Octagon<int> octagon2(octagon1);
    Octagon<int> octagon3(Point<int>(1, 1), Point<int>(2, 1), Point<int>(3, 2), Point<int>(3, 3),
                          Point<int>(2, 4), Point<int>(1, 4), Point<int>(0, 3), Point<int>(0, 2));

    EXPECT_TRUE(octagon1 == octagon2);
    EXPECT_FALSE(octagon1 == octagon3);
}

TEST(OctagonTest, Clone) {
    Octagon<int> octagon1(Point<int>(0, 0), Point<int>(1, 0), Point<int>(2, 1), Point<int>(2, 2),
                          Point<int>(1, 3), Point<int>(0, 3), Point<int>(-1, 2), Point<int>(-1, 1));
    auto octagon2 = octagon1.clone();
    EXPECT_TRUE(dynamic_cast<Octagon<int>*>(octagon2.get()) != nullptr);
    EXPECT_TRUE(octagon1 == *octagon2);
}