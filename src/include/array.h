#pragma once
#include <iostream>
#include <memory>
#include "figure.h"

template <Scalar T>
class Array {
private:
    std::shared_ptr<Figure<T>>* figures;
    size_t size;
    size_t capacity;

    void resize(size_t new_capacity) {
        auto* new_figures = new std::shared_ptr<Figure<T>>[new_capacity];
        for (size_t i = 0; i < size; ++i)
            new_figures[i] = figures[i];
        delete[] figures;
        figures = new_figures;
        capacity = new_capacity;
    }

public:
    explicit Array(size_t capacity = 2) : size(0), capacity(capacity) {
        figures = new std::shared_ptr<Figure<T>>[capacity];
    }

    ~Array() {
        delete[] figures;
    }

    Array(const Array& other) : size(other.size), capacity(other.capacity) {
        figures = new std::shared_ptr<Figure<T>>[capacity];
        for (size_t i = 0; i < size; ++i)
            figures[i] = other.figures[i]->clone();
    }

    Array(Array&& other) 
        : figures(other.figures), size(other.size), capacity(other.capacity) {
        other.figures = nullptr;
        other.size = 0;
        other.capacity = 0;
    }

    Array& operator=(Array other) {
        std::swap(figures, other.figures);
        std::swap(size, other.size);
        std::swap(capacity, other.capacity);
        return *this;
    }

    Array& operator=(Array&& other) {
        std::swap(figures, other.figures);
        std::swap(size, other.size);
        std::swap(capacity, other.capacity);
        return *this;
    }

    void addFigure(const std::shared_ptr<Figure<T>>& figure) {
        if (size >= capacity)
            resize(capacity * 2);
        figures[size++] = figure;
    }

    void removeFigure(size_t index) {
        if (index >= size)
            return;
        for (size_t i = index; i < size - 1; ++i)
            figures[i] = figures[i + 1];
        --size;
    }

    std::shared_ptr<Figure<T>> getFigure(size_t index) const {
        if (index >= size)
            return nullptr;
        return figures[index];
    }

    size_t getSize() const {
        return size;
    }

    size_t getCapacity() const {
        return capacity;
    }

    double getAllArea() const {
        double area = 0;
        for (size_t i = 0; i < size; ++i)
            area += static_cast<double>(*figures[i]);
        return area;
    }

    void printFigures() const {
        for (size_t i = 0; i < size; ++i) {
            std::cout << "Figure " << i + 1 << ": ";
            figures[i]->print(std::cout);
            auto center = figures[i]->getCenter();
            std::cout << "Center=(" << center.x << "," << center.y << ") ";
            std::cout << "Area=" << static_cast<double>(*figures[i]) << std::endl;
        }
    }

    std::shared_ptr<Figure<T>> operator[](size_t index) const {
        if (index >= size)
            return nullptr;
        return figures[index];
    }
};