#pragma once

#include "Figure.h"


template <Scalar T>
class Pentagon : public Figure<T>
{
private:
    std::unique_ptr<Point<T>[]> vertices;
    size_t vertex_count;
    /* data */
public:
    Pentagon(const Point<T>& a, const Point<T>& b, const Point<T>& c, const Point<T>& d, const Point<T>& e);
    ~Pentagon() = default;

    Point<T> getCenter() const override;

    void print(std::ostream& out) const override;
    void read(std::istream& in) override;

    operator double() const override;

    bool operator==(const Figure<T>& other) const override;

    std::unique_ptr<Figure<T>> clone() const override;
};
 
template <Scalar T>
Pentagon<T>::Pentagon(const Point<T>& a, const Point<T>& b, const Point<T>& c, const Point<T>& d, const Point<T>& e) :
    vertex_count(5),
      vertices(std::make_unique<Point<T>[]>(5))
{
    vertices[0] = a;
    vertices[1] = b;
    vertices[2] = c;
    vertices[3] = d;
    vertices[4] = e;
}

template <Scalar T>
Point<T> Pentagon<T>::getCenter() const {
    T x_sum = 0, y_sum = 0;
    for (size_t i = 0; i < vertex_count; ++i) {
        x_sum += vertices[i].getX();
        y_sum += vertices[i].getY();
    }
    return Point<T>(x_sum / vertex_count, y_sum / vertex_count);
}

template <Scalar T>
void Pentagon<T>::print(std::ostream& out) const {
    for (size_t i = 0; i < vertex_count; ++i) {
        if (i > 0) out << " ";
        out << vertices[i].getX() << " " << vertices[i].getY();
    }
}

template <Scalar T>
void Pentagon<T>::read(std::istream& in) {
    for (size_t i = 0; i < vertex_count; ++i) {
        T x, y;
        in >> x >> y;
        vertices[i] = Point<T>(x, y);
    }
}

template <Scalar T>
Pentagon<T>::operator double() const {
    T area = 0.0;
    for (size_t i = 0; i < vertex_count; ++i) {
        const auto& p1 = vertices[i];
        const auto& p2 = vertices[(i + 1) % vertex_count];
        area += p1.getX() * p2.getY();
        area -= p2.getX() * p1.getY();
    }
    return std::abs(area) * 0.5;
}

template <Scalar T>
bool Pentagon<T>::operator==(const Figure<T>& other) const {
    const Pentagon<T>* rhs = dynamic_cast<const Pentagon<T>*>(&other);
    if (!rhs) return false;
    if (vertex_count != rhs->vertex_count) return false;

    for (size_t i = 0; i < vertex_count; ++i) {
        if (!(vertices[i] == rhs->vertices[i]))
            return false;
    }
    return true;
}

template <Scalar T>
std::unique_ptr<Figure<T>> Pentagon<T>::clone() const {
    auto new_vertices = std::make_unique<Point<T>[]>(vertex_count);
    for (size_t i = 0; i < vertex_count; ++i) {
        new_vertices[i] = vertices[i];
    }
    return std::make_unique<Pentagon<T>>(
        vertices[0], vertices[1], vertices[2], vertices[3], vertices[4]
    );
}