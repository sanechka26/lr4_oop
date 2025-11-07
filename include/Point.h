#pragma once

#include <iostream>
#include <concepts>

template <typename T>
concept Scalar = std::is_arithmetic_v<T>;

template <Scalar T>
class Point
{
private:
    T x;
    T y;

public:
    Point(T x = 0, T y = 0);
    Point(const Point& other) = default;
    ~Point() = default;

    Point& operator=(const Point& other);
    bool operator==(const Point& other) const;

    T getX() const;
    T getY() const;
};



template <Scalar T>
Point<T>::Point(T x, T y) : x(x), y(y) {};

template <Scalar T>
Point<T>& Point<T>::operator=(const Point& other){
    if (this != &other)
    {
        x = other.x;
        y = other.y;
    }
    return *this;
};

template <Scalar T>
bool Point<T>::operator==(const Point& other) const {
    return x == other.x && y == other.y;
};

template <Scalar T>
T Point<T>::getX() const {return x; }

template <Scalar T>
T Point<T>::getY() const {return y; }

template <Scalar T>
std::ostream& operator<<(std::ostream& os, const Point<T>& p) {
    return os << "(" << p.getX() << ", " << p.getY() << ")";
}

template <Scalar T>
std::istream& operator>>(std::istream& is, Point<T>& p) {
    char ch;
    T x, y;
    is >> ch;  // '('
    if (ch != '(') {
        is.setstate(std::ios::failbit);
        return is;
    }
    is >> x;
    is >> ch;  // ','
    is >> y;
    is >> ch;  // ')'
    if (ch != ')') {
        is.setstate(std::ios::failbit);
        return is;
    }
    p = Point<T>(x, y);
    return is;
}