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
    float dx = other.x - x;
    float dy = other.y - y;
    return std::sqrt(dx * dx + dy * dy);
}

float Point2D::distance(const Point2D& p1, const Point2D& p2) {
    return p1.distance(p2);
}

bool Point2D::areCollinear(const Point2D& p1, const Point2D& p2, const Point2D& p3) {
    int dx1 = p2.getX() - p1.getX();
    int dy1 = p2.getY() - p1.getY();
    int dx2 = p3.getX() - p1.getX();
    int dy2 = p3.getY() - p1.getY();
    return (dx1 * dy2 - dy1 * dx2) == 0;
}

std::ostream& operator<<(std::ostream& os, const Point2D& point) {
    os << "(" << point.getX() << ", " << point.getY() << ")";
    return os;
}