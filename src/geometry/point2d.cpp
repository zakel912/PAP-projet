#include "point2d.h"
#include <cmath>

Point2D::Point2D(int x, int y) : x(x), y(y) {}

Point2D::Point2D(float x, float y) : x(static_cast<int>(x)), y(static_cast<int>(y)) {}

Point2D::Point2D(const Point2D& other) : x(other.x), y(other.y) {}

int Point2D::getX() const{
    return x;
}

int Point2D::getY() const{
    return y;
}

float Point2D::distance(const Point2D& other) const {
    return std::sqrt(std::pow(other.x - x, 2) + std::pow(other.y - y, 2));
}

float Point2D::distance(const Point2D& p1, const Point2D& p2) {
    return p1.distance(p2);
}

bool Point2D::areCollinear(const Point2D& p1, const Point2D& p2, const Point2D& p3) {
   return (static_cast<float>(p2.getX() - p1.getX()) * (p3.getY() - p1.getY())) ==
       (static_cast<float>(p2.getY() - p1.getY()) * (p3.getX() - p1.getX()));
}

std::ostream& operator<<(std::ostream& os, const Point2D& point) {
    os << "(" << point.getX() << ", " << point.getY() << ")";
    return os;
}