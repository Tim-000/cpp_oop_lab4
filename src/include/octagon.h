#pragma once
#include <cmath>
#include <iostream>
#include "figure.h"

template <Scalar T>
class Octagon : public Figure<T> {
public:
    Octagon(const Point<T>& p1, const Point<T>& p2, const Point<T>& p3,
            const Point<T>& p4, const Point<T>& p5, const Point<T>& p6,
            const Point<T>& p7, const Point<T>& p8)
    {
        this->size = 8;
        this->points = std::make_unique<Point<T>[]>(8);
        this->points[0] = p1;
        this->points[1] = p2;
        this->points[2] = p3;
        this->points[3] = p4;
        this->points[4] = p5;
        this->points[5] = p6;
        this->points[6] = p7;
        this->points[7] = p8;
    }

    Octagon() = default;

    Octagon(const Octagon& other) {
        this->size = other.size;
        this->points = std::make_unique<Point<T>[]>(this->size);
        for (size_t i = 0; i < this->size; ++i)
            this->points[i] = other.points[i];
    }

    Point<T> getCenter() const override {
        T x_c = 0, y_c = 0;
        for (size_t i = 0; i < this->size; ++i) {
            x_c += this->points[i].x;
            y_c += this->points[i].y;
        }
        return Point<T>(x_c / this->size, y_c / this->size);
    }

    double getArea() const override {
        double area = 0.0;
        for (size_t i = 0; i < this->size; ++i) {
            const Point<T>& a = this->points[i];
            const Point<T>& b = this->points[(i + 1) % this->size];
            area += (a.x * b.y - b.x * a.y);
        }
        return std::abs(area) / 2.0;
    }

    void print(std::ostream& os) const override {
        for (size_t i = 0; i < this->size; ++i)
            os << "(" << this->points[i].x << "," << this->points[i].y << ") ";
        os << "Area=" << getArea() << " ";
        os << "Center=(" << getCenter().x << "," << getCenter().y << ")" << std::endl;
    }

    void read(std::istream& is) override {
        this->size = 8;
        this->points = std::make_unique<Point<T>[]>(8);
        for (size_t i = 0; i < this->size; ++i)
            is >> this->points[i].x >> this->points[i].y;
    }

    bool operator==(const Octagon<T>& other) const {
        if (this->size != other.size)
            return false;

        for (size_t i = 0; i < this->size; ++i)
            if (!(this->points[i] == other.points[i]))
                return false;
        return true;
    }

    bool operator==(const Figure<T>& other) const override {
        const Octagon<T>* oct = dynamic_cast<const Octagon<T>*>(&other);
        if (!oct || this->size != oct->size)
            return false;
        return *this == *oct;
    }

    std::unique_ptr<Figure<T>> clone() const override {
        return std::make_unique<Octagon<T>>(*this);
    }
};