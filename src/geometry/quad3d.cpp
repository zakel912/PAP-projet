#include "quad3d.h"
#include <iostream>
#include <stdexcept>
#include <cmath>

Quad3D::Quad3D(){
    Quad3D(Triangle3D(), Triangle3D(Point3D(1,1), Point3D(0,1), Point3D(1,0)));
}

// Constructeur avec deux triangles et des composantes RVB
Quad3D::Quad3D(const Triangle3D& firstT, const Triangle3D& secondT, int rouge, int vert, int bleu)
    : triangles_{firstT, secondT} {
    setColor(rouge, vert, bleu);
}

// Constructeur avec deux triangles et un objet Couleur
Quad3D::Quad3D(const Triangle3D& firstT, const Triangle3D& secondT, const Couleur& color)
    : triangles_{firstT, secondT} {
    setColor(color);
}

// Constructeur avec quatre sommets et des composantes RVB
Quad3D::Quad3D(const Point3D& p1, const Point3D& p2, const Point3D& p3, const Point3D& p4, int rouge, int vert, int bleu)
    : triangles_{Triangle3D(p1, p2, p3, rouge, vert, bleu),
                 Triangle3D(p1, p3, p4, rouge, vert, bleu)} {
}

const Triangle3D& Quad3D::getFirstTriangle() const noexcept {
    return triangles_[0];
}

const Triangle3D& Quad3D::getSecondTriangle() const noexcept {
    return triangles_[1];
}

// Accesseur pour la couleur
Couleur Quad3D::getColor() const {
    return triangles_[0].getColor();
}

// Modificateur pour la couleur avec un objet Couleur
void Quad3D::setColor(const Couleur& color) {
    triangles_[0].setColor(color);
    triangles_[1].setColor(color);
}

// Modificateur pour la couleur avec des composantes RVB
void Quad3D::setColor(int rouge, int vert, int bleu) {
    triangles_[0].setColor(rouge, vert, bleu);
    triangles_[1].setColor(rouge, vert, bleu);
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
