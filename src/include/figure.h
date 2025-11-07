#pragma once
#include <iostream>
#include <memory>
#include "point.h"

template <Scalar T>
class Figure {
protected:
    std::unique_ptr<Point<T>[]> points;
    std::size_t size = 0;

    virtual double getArea() const = 0;

public:
    virtual ~Figure() = default;

    virtual operator double() const {
        return getArea();
    }

    std::size_t getSize() const {
        return size;
    }

    const Point<T>* getPoints() const {
        return points.get();
    }

    virtual Point<T> getCenter() const = 0;
    virtual void print(std::ostream& os) const = 0;
    virtual void read(std::istream& is) = 0;

    Figure& operator=(const Figure& other) {
        if (this == &other)
            return *this;
        size = other.size;
        if (size > 0) {
            points = std::make_unique<Point<T>[]>(size);
            for (std::size_t i = 0; i < size; ++i)
                points[i] = other.points[i];
        } else {
            points.reset();
        }
        return *this;
    }

    Figure& operator=(Figure&& other) {
        if (this == &other)
            return *this;
        points = std::move(other.points);
        size = other.size;
        other.size = 0;
        return *this;
    }

    virtual bool operator==(const Figure<T>& other) const = 0;
    virtual std::unique_ptr<Figure<T>> clone() const = 0;

    friend std::istream& operator>>(std::istream& is, Figure& f) {
        f.read(is);
        return is;
    }

    friend std::ostream& operator<<(std::ostream& os, const Figure& f) {
        f.print(os);
        return os;
    }
};
