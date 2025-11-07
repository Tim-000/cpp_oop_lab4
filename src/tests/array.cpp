#include "../include/array.h"
#include <gtest/gtest.h>
#include "../include/hexagon.h"
#include "../include/pentagon.h"
#include "../include/octagon.h"

template <Scalar T>
auto makePentagon() {
    return std::make_shared<Pentagon<T>>(Point<T>(0, 0), Point<T>(1, 2), Point<T>(2, 3),
                                         Point<T>(3, 2), Point<T>(2, 0));
}

template <Scalar T>
auto makeHexagon() {
    return std::make_shared<Hexagon<T>>(Point<T>(0, 0), Point<T>(1, 0), Point<T>(2, 1),
                                        Point<T>(2, 2), Point<T>(1, 3), Point<T>(0, 2));
}

template <Scalar T>
auto makeOctagon() {
    return std::make_shared<Octagon<T>>(Point<T>(0,0), Point<T>(1,0), Point<T>(2,1), Point<T>(2,2),
                                        Point<T>(1,3), Point<T>(0,3), Point<T>(-1,2), Point<T>(-1,1));
}

TEST(ArrayTest, AddAndGetFigures) {
    Array<int> array;
    auto pentagon = makePentagon<int>();
    auto hexagon = makeHexagon<int>();
    auto octagon = makeOctagon<int>();

    array.addFigure(pentagon);
    array.addFigure(hexagon);
    array.addFigure(octagon);

    EXPECT_EQ(array.getSize(), 3);
    EXPECT_EQ(array.getFigure(0), pentagon);
    EXPECT_EQ(array.getFigure(1), hexagon);
    EXPECT_EQ(array.getFigure(2), octagon);

    EXPECT_EQ(array[0], pentagon);
    EXPECT_EQ(array[1], hexagon);
    EXPECT_EQ(array[2], octagon);
}

TEST(ArrayTest, TotalArea) {
    Array<int> array;
    auto pentagon = makePentagon<int>();
    auto hexagon = makeHexagon<int>();
    auto octagon = makeOctagon<int>();

    array.addFigure(pentagon);
    array.addFigure(hexagon);
    array.addFigure(octagon);

    double expected_area = static_cast<double>(*pentagon) +
                           static_cast<double>(*hexagon) +
                           static_cast<double>(*octagon);

    EXPECT_DOUBLE_EQ(array.getAllArea(), expected_area);
}

TEST(ArrayTest, RemoveFigure) {
    Array<int> array;
    auto pentagon = makePentagon<int>();
    auto hexagon = makeHexagon<int>();
    auto octagon = makeOctagon<int>();

    array.addFigure(pentagon);
    array.addFigure(hexagon);
    array.addFigure(octagon);

    array.removeFigure(1);
    EXPECT_EQ(array.getSize(), 2);
    EXPECT_EQ(array.getFigure(0), pentagon);
    EXPECT_EQ(array.getFigure(1), octagon);

    array.removeFigure(0);
    EXPECT_EQ(array.getSize(), 1);
    EXPECT_EQ(array.getFigure(0), octagon);

    array.removeFigure(0);
    EXPECT_EQ(array.getSize(), 0);
}

TEST(ArrayTest, CopyArray) {
    Array<int> array1;
    auto pentagon = makePentagon<int>();
    array1.addFigure(pentagon);

    Array<int> array2 = array1;
    EXPECT_EQ(array2.getSize(), array1.getSize());
    EXPECT_NE(array2.getFigure(0), array1.getFigure(0)); 
    EXPECT_EQ(static_cast<double>(*array2.getFigure(0)), static_cast<double>(*array1.getFigure(0)));
}

TEST(ArrayTest, MoveArray) {
    Array<int> array1;
    auto pentagon = makePentagon<int>();
    array1.addFigure(pentagon);

    Array<int> array2 = std::move(array1);
    EXPECT_EQ(array2.getSize(), 1);
    EXPECT_EQ(array1.getSize(), 0);
}

TEST(ArrayTest, ResizeArray) {
    Array<int> array(2);
    auto pentagon = makePentagon<int>();
    auto hexagon = makeHexagon<int>();
    auto octagon = makeOctagon<int>();

    array.addFigure(pentagon);
    array.addFigure(hexagon);
    EXPECT_EQ(array.getCapacity(), 2);

    array.addFigure(octagon);
    EXPECT_GE(array.getCapacity(), 3);
    EXPECT_EQ(array.getSize(), 3);
}

TEST(ArrayTest, IndexOutOfBounds) {
    Array<int> array;
    auto pentagon = makePentagon<int>();
    array.addFigure(pentagon);

    EXPECT_EQ(array.getFigure(10), nullptr);
    EXPECT_EQ(array[10], nullptr);
}

TEST(ArrayTest, PrintFigures) {
    Array<int> array;
    auto pentagon = makePentagon<int>();
    array.addFigure(pentagon);

    EXPECT_NO_THROW(array.printFigures());
}