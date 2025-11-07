#include "../include/pentagon.h"
#include <gtest/gtest.h>
#include <sstream>

TEST(PentagonTest, DefaultConstructor) {
    Pentagon<int> pentagon;
    EXPECT_EQ(pentagon.getSize(), 0);
}

TEST(PentagonTest, ParameterConstructor) {
    Point<int> p1{0, 0}, p2{2, 0}, p3{3, 2}, p4{1, 3}, p5{-1, 2};
    Pentagon<int> pentagon(p1, p2, p3, p4, p5);

    EXPECT_EQ(pentagon.getSize(), 5);

    const Point<int>* points = pentagon.getPoints();
    EXPECT_EQ(points[0], p1);
    EXPECT_EQ(points[1], p2);
    EXPECT_EQ(points[2], p3);
    EXPECT_EQ(points[3], p4);
    EXPECT_EQ(points[4], p5);
}

TEST(PentagonTest, CopyConstructor) {
    Point<int> p1{0, 0}, p2{2, 0}, p3{3, 2}, p4{1, 3}, p5{-1, 2};
    Pentagon<int> pentagon1(p1, p2, p3, p4, p5);
    Pentagon<int> pentagon2(pentagon1);

    EXPECT_EQ(pentagon1.getSize(), pentagon2.getSize());
    EXPECT_TRUE(pentagon1 == pentagon2);
}

TEST(PentagonTest, GetCenter) {
    Pentagon<double> pentagon(Point<double>(0, 0), Point<double>(2, 0), Point<double>(3, 2),
                              Point<double>(1, 3), Point<double>(-1, 2));
    Point<double> center = pentagon.getCenter();
    EXPECT_DOUBLE_EQ(center.x, (0 + 2 + 3 + 1 - 1) / 5.0);
    EXPECT_DOUBLE_EQ(center.y, (0 + 0 + 2 + 3 + 2) / 5.0);
}

TEST(PentagonTest, GetArea) {
    Pentagon<int> pentagon(Point<int>(0, 0), Point<int>(3, 0), Point<int>(4, 2),
                           Point<int>(2, 4), Point<int>(-1, 2));
    double area = pentagon.getArea();
    EXPECT_DOUBLE_EQ(area, 13);
}

TEST(PentagonTest, Print) {
    Pentagon<int> pentagon(Point<int>(0, 0), Point<int>(2, 0), Point<int>(3, 2),
                           Point<int>(1, 3), Point<int>(-1, 2));
    std::ostringstream os;

    pentagon.print(os);
    std::string output = os.str();

    EXPECT_NE(output.find("Area"), std::string::npos);
    EXPECT_NE(output.find("(0,0)"), std::string::npos);
}

TEST(PentagonTest, Read) {
    Pentagon<int> pentagon;
    std::istringstream is("0 0 2 0 3 2 1 3 -1 2");
    pentagon.read(is);

    Point<int> p1{0, 0}, p2{2, 0}, p3{3, 2}, p4{1, 3}, p5{-1, 2};
    const Point<int>* points = pentagon.getPoints();
    EXPECT_EQ(points[0], p1);
    EXPECT_EQ(points[1], p2);
    EXPECT_EQ(points[2], p3);
    EXPECT_EQ(points[3], p4);
    EXPECT_EQ(points[4], p5);
}

TEST(PentagonTest, OperatorEquals) {
    Pentagon<int> pentagon1(Point<int>(0, 0), Point<int>(2, 0), Point<int>(3, 2),
                             Point<int>(1, 3), Point<int>(-1, 2));
    Pentagon<int> pentagon2(pentagon1);
    Pentagon<int> pentagon3(Point<int>(1, 1), Point<int>(3, 1), Point<int>(4, 3),
                             Point<int>(2, 4), Point<int>(0, 3));

    EXPECT_TRUE(pentagon1 == pentagon2);
    EXPECT_FALSE(pentagon1 == pentagon3);
}

TEST(PentagonTest, Clone) {
    Pentagon<int> pentagon1(Point<int>(0, 0), Point<int>(2, 0), Point<int>(3, 2),
                             Point<int>(1, 3), Point<int>(-1, 2));
    auto pentagon2 = pentagon1.clone();
    EXPECT_TRUE(dynamic_cast<Pentagon<int>*>(pentagon2.get()) != nullptr);
    EXPECT_TRUE(pentagon1 == *pentagon2);
}