#include "quad3d.h"
#include <iostream>
#include <stdexcept>
#include <cmath>

Quad3D::Quad3D(const Triangle3D& firstT, const Triangle3D& secondT) {
    triangles_[0] = firstT;
    triangles_[1] = secondT;
}

Quad3D::Quad3D(const Point3D& p1, const Point3D& p2, const Point3D& p3, const Point3D& p4) {
    triangles_[0] = Triangle3D(p1, p2, p3);
    triangles_[1] = Triangle3D(p1, p3, p4);

    Point3D u = p2 - p1;
    Point3D v = p3 - p1;
    Point3D w = p4 - p1;

    Point3D cross1 = u.crossProduct(v);
    float dot = cross1.dotProduct(w);

    if (std::fabs(dot) > 1e-6) {
        throw std::runtime_error("Les points ne sont pas coplanaires.");
    }
}

const Triangle3D& Quad3D::getFirstTriangle() const noexcept {
    return triangles_[0];
}

const Triangle3D& Quad3D::getSecondTriangle() const noexcept {
    return triangles_[1];
}

float Quad3D::surface() const {
    return triangles_[0].area() + triangles_[1].area();
}

bool Quad3D::isVertex(const Point3D& p) const {
    return triangles_[0].isVertex(p) || triangles_[1].isVertex(p);
}

bool Quad3D::hasCommonSide(const Quad3D& other) const {
    return triangles_[0].hasCommonSide(other.getFirstTriangle()) ||
           triangles_[0].hasCommonSide(other.getSecondTriangle()) ||
           triangles_[1].hasCommonSide(other.getFirstTriangle()) ||
           triangles_[1].hasCommonSide(other.getSecondTriangle());
}

bool Quad3D::hasCommonSide(const Quad3D& q1, const Quad3D& q2) {
    return q1.hasCommonSide(q2);
}

bool Quad3D::sameSurface(const Quad3D& other) const {
    return std::fabs(surface() - other.surface()) < 1e-6;
}

bool Quad3D::equals(const Quad3D& other) const {
    return triangles_[0].equals(other.getFirstTriangle()) &&
           triangles_[1].equals(other.getSecondTriangle());
}

bool Quad3D::operator==(const Quad3D& other) const {
    return equals(other);
}

std::ostream& operator<<(std::ostream& os, const Quad3D& quad) {
    os << "Quad3D:\n";
    os << "  Triangle 1: " << quad.getFirstTriangle() << "\n";
    os << "  Triangle 2: " << quad.getSecondTriangle() << "\n";
    return os;
}
