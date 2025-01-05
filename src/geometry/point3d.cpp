#include "point3d.h"
#include <cmath>
#include "geometry_utils.h"

Point3D::Point3D(float x, float y, float z) : x(x), y(y), z(z) {}

Point3D::Point3D(const Point3D& other){
    x = other.getX();
    y = other.getY();
    z = other.getZ();
}

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
    return std::sqrt((other.x - x) * (other.x - x) +
                     (other.y - y) * (other.y - y) +
                     (other.z - z) * (other.z - z));
}


float Point3D::distance(const Point3D& p1, const Point3D& p2){
    return p1.distance(p2);
}

Point3D Point3D::crossProduct(const Point3D& other) const {
    return Point3D(
        y * other.z - z * other.y,
        z * other.x - x * other.z,
        x * other.y - y * other.x
    );
}

Point3D Point3D::crossProduct(const Point3D& p1, const Point3D& p2){
    return p1.crossProduct(p2);
}

float Point3D::dotProduct(const Point3D& other) const{
    return getX() * other.getX() + getY() * other.getY() + getZ() * other.getZ();
}

bool Point3D::areCollinear(const Point3D& p1, const Point3D& p2, const Point3D& p3) {
    Point3D v1 = p2 - p1;
    Point3D v2 = p3 - p1;

    return v1.crossProduct(v2).norm() < TOLERANCE;
}

bool Point3D::equals(const Point3D& other) const {
    return std::fabs(x - other.x) < TOLERANCE &&
           std::fabs(y - other.y) < TOLERANCE &&
           std::fabs(z - other.z) < TOLERANCE;
}

bool operator==(const Point3D& lhs, const Point3D& rhs) {
    return lhs.equals(rhs);
}

bool operator!=(const Point3D& p1, const Point3D& p2) {
    return !(p1 == p2);
}

Point3D Point3D::normalize() const {
    float magnitude = norm();
    if (magnitude < TOLERANCE) {
        return Point3D(0, 0, 0);
    }
    return *this / magnitude;
}

Point3D Point3D::adjustedTranslation(const Point3D& offset, float projectionDistance) const {
    float depthFactor = projectionDistance / (projectionDistance + this->getZ());
    return *this + offset * depthFactor;
}

std::ostream& operator<<(std::ostream& os, const Point3D& point) {
    os << "(" << point.getX() << ", " << point.getY() << ", " << point.getZ() << ")";
    return os;
}