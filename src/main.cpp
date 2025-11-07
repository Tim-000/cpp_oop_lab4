#include "include/array.h"
#include "include/point.h"
#include "include/pentagon.h"
#include "include/hexagon.h"
#include "include/octagon.h"

int main()
{
    Pentagon<int> p({0, 0}, {2, 1}, {3, 3}, {1, 4}, {-1, 2});
    Hexagon<int> h({0, 0}, {1, 0}, {3, 1}, {3, 3}, {1, 4}, {-1, 2});
    Octagon<int> o({0, 0}, {1, 0}, {2, 1}, {3, 2}, {3, 3}, {2, 4}, {1, 3}, {0, 2});

    std::cout << "Pentagon: ";
    p.print(std::cout);
    std::cout << "Center: (" << p.getCenter().x << ", " << p.getCenter().y << ") ";
    std::cout << "Area: " << static_cast<double>(p) << std::endl;

    std::cout << "Hexagon: ";
    h.print(std::cout);
    std::cout << "Center: (" << h.getCenter().x << ", " << h.getCenter().y << ") ";
    std::cout << "Area: " << static_cast<double>(h) << std::endl;

    std::cout << "Octagon: ";
    o.print(std::cout);
    std::cout << "Center: (" << o.getCenter().x << ", " << o.getCenter().y << ") ";
    std::cout << "Area: " << static_cast<double>(o) << std::endl
              << std::endl;

    Array<int> arr(3);
    arr.addFigure(std::make_shared<Pentagon<int>>(p));
    arr.addFigure(std::make_shared<Hexagon<int>>(h));
    arr.addFigure(std::make_shared<Octagon<int>>(o));

    arr.printFigures();

    std::cout << "Total area: " << arr.getAllArea() << std::endl;

    auto figure = arr[1];
    std::cout << "Figure at index 1: ";
    figure->print(std::cout);
    std::cout << "Area: " << static_cast<double>(*figure) << std::endl;

    return 0;
}