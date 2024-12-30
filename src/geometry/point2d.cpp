#include "point2d.h"
#include <cmath>

Point2D::Point2D(float x, float y) {
    this->x = x;
    this->y = y;
}

Point2D::Point2D(const Point2D& other){
    Point2D(other.getX(), other.getY());
}

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

std::ostream& operator<<(std::ostream& os, const Point2D& point) {
    os << "(" << point.getX() << ", " << point.getY() << ")";
    return os;
}