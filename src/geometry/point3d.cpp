#include "point3d.h"
#include <cmath>

Point3D::Point3D(float x, float y, float z) : x(x), y(y), z(z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

Point3D::Point3D(const Point3D& other) : x(other.x), y(other.y), z(other.z) {}

Point3D::~Point3D() {}

float Point3D::getX() const{
    return x;
}

float Point3D::getY() const{
    return y;
}

float Point3D::getZ() const{
    return z;
}

float Point3D::distance(const Point3D& other) const {
    return std::sqrt(std::pow(other.x - x, 2) +
                     std::pow(other.y - y, 2) +
                     std::pow(other.z - z, 2));
}


float Point3D::distance(const Point3D& p1, const Point3D& p2){
    return p1.distance(p2);
}

Point3D Point3D::crossProduct(const Point3D& other) const{
    return Point3D(getY() * other.getZ() - getZ() * other.getY(), getZ() * other.getX() - getX() * other.getZ(), getX() * other.getY() - getY() * other.getX());
}

Point3D Point3D::crossProduct(const Point3D& p1, const Point3D& p2){
    return p1.crossProduct(p2);
}

float Point3D::dotProduct(const Point3D& other) const{
    return getX() * other.getX() + getY() * other.getY() + getZ() * other.getZ();
}

static constexpr float TOLERANCE = 1e-6;

bool Point3D::areCollinear(const Point3D& p1, const Point3D& p2, const Point3D& p3) {
    Point3D u(p2.x - p1.x, p2.y - p1.y, p2.z - p1.z);
    Point3D v(p3.x - p1.x, p3.y - p1.y, p3.z - p1.z);
    Point3D cross = crossProduct(u, v);
    return std::fabs(cross.x) < TOLERANCE &&
           std::fabs(cross.y) < TOLERANCE &&
           std::fabs(cross.z) < TOLERANCE;
}

bool Point3D::equals(const Point3D& other) const {
    return std::fabs(x - other.x) < TOLERANCE &&
           std::fabs(y - other.y) < TOLERANCE &&
           std::fabs(z - other.z) < TOLERANCE;
}

    bool operator==(const Point3D& lhs, const Point3D& rhs) {
        return lhs.equals(rhs);
    }

std::ostream& operator<<(std::ostream& os, const Point3D& point) {
    os << "(" << point.getX() << ", " << point.getY() << ", " << point.getZ() << ")";
    return os;
}