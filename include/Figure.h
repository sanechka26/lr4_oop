#pragma once

#include "Point.h"
#include <memory>
#include <array>
#include <iostream>

template <Scalar T>
class Figure
{
private:
    /* data */
public:
    virtual ~Figure() = default;

    virtual Point<T> getCenter() const = 0;

    virtual void print(std::ostream& out) const = 0;
    virtual void read(std::istream& in) = 0;

    virtual operator double() const = 0;

    virtual std::unique_ptr<Figure<T>> clone() const = 0;

    virtual bool operator==(const Figure& other) const = 0;
};


template <Scalar T>
std::istream& operator>>(std::istream& in, Figure<T>& fig) {
    fig.read(in);
    return in;
}
template <Scalar T>
std::ostream& operator<<(std::ostream& out, const Figure<T>& fig) {
    fig.print(out);
    return out;
}