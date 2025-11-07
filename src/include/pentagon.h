#pragma once
#include <cmath>
#include <iostream>
#include "figure.h"

template <Scalar T>
class Pentagon : public Figure<T> {
public:
    Pentagon(const Point<T>& p1, const Point<T>& p2, const Point<T>& p3,
             const Point<T>& p4, const Point<T>& p5) 
    {
        this->size = 5;
        this->points = std::make_unique<Point<T>[]>(5);
        this->points[0] = p1;
        this->points[1] = p2;
        this->points[2] = p3;
        this->points[3] = p4;
        this->points[4] = p5;
    }

    Pentagon() = default;

    Pentagon(const Pentagon& other) {
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
        this->size = 5;
        this->points = std::make_unique<Point<T>[]>(5);
        for (size_t i = 0; i < this->size; ++i)
            is >> this->points[i].x >> this->points[i].y;
    }

    bool operator==(const Pentagon<T>& other) const {
        for (size_t i = 0; i < this->size; ++i)
            if (!(this->points[i] == other.points[i]))
                return false;
        return true;
    }

    bool operator==(const Figure<T>& other) const override {
        const Pentagon<T>* pent = dynamic_cast<const Pentagon<T>*>(&other);;
        return pent ? *this == *pent : false;
    }

    std::unique_ptr<Figure<T>> clone() const override {
        return std::make_unique<Pentagon<T>>(*this);
    }
};
