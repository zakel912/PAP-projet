#include "quad3d.h"
#include <iostream>
#include <stdexcept>
#include <cmath>
#include "geometry_utils.h"

// Constructeur par défaut
Quad3D::Quad3D() 
    : triangles_{Triangle3D(), Triangle3D()} {}

// Constructeur avec deux triangles et des composantes RVB
Quad3D::Quad3D(const Triangle3D& firstT, const Triangle3D& secondT, int rouge, int vert, int bleu)
    : triangles_{firstT, secondT} {
    if (!firstT.hasCommonSide(secondT)) {
        throw std::invalid_argument("The two triangles must share a common side to form a valid Quad3D.");
    }
    setColor(rouge, vert, bleu);
}

// Constructor with two triangles and a color object
Quad3D::Quad3D(const Triangle3D& firstT, const Triangle3D& secondT, const Couleur& color)
    : triangles_{firstT, secondT} {
    if (!firstT.hasCommonSide(secondT)) {
        throw std::invalid_argument("The two triangles must share a common side to form a valid Quad3D.");
    }
    setColor(color);
}

// Constructeur avec quatre sommets et des composantes RVB
Quad3D::Quad3D(const Point3D& p1, const Point3D& p2, const Point3D& p3, const Point3D& p4, int rouge, int vert, int bleu)
    : triangles_{Triangle3D(p1, p2, p3, rouge, vert, bleu),
                 Triangle3D(p1, p3, p4, rouge, vert, bleu)} {
    if (Point3D::areCollinear(p1, p2, p3) || Point3D::areCollinear(p1, p3, p4)) {
        throw std::runtime_error("Les sommets fournis ne forment pas un quadrilatère valide.");
    }
    if (!triangles_[0].hasCommonSide(triangles_[1])) {
        throw std::runtime_error("Les triangles générés doivent partager un côté.");
    }
}

// Constructeur avec quatre sommets et des composantes RVB
Quad3D::Quad3D(const Point3D& p1, const Point3D& p2, const Point3D& p3, const Point3D& p4, const Couleur& color)
    : triangles_{Triangle3D(p1, p2, p3, color),
                 Triangle3D(p1, p3, p4, color)} {
    if (Point3D::areCollinear(p1, p2, p3) || Point3D::areCollinear(p1, p3, p4)) {
        throw std::runtime_error("Les sommets fournis ne forment pas un quadrilatère valide.");
    }
    if (!triangles_[0].hasCommonSide(triangles_[1])) {
        throw std::runtime_error("Les triangles générés doivent partager un côté.");
    }
}

Quad3D::Quad3D(const Quad3D& other)
    : triangles_{other.triangles_[0], other.triangles_[1]}{}

// Accesseur pour le premier triangle
const Triangle3D& Quad3D::getFirstTriangle() const noexcept {
    return triangles_[0];
}

// Accesseur pour le deuxième triangle
const Triangle3D& Quad3D::getSecondTriangle() const noexcept {
    return triangles_[1];
}

// Accesseur pour la couleur
Couleur Quad3D::getColor() const {
    return triangles_[0].getColor();
}

std::vector<Point3D> Quad3D::getVertices() const {
    return {triangles_[0].getP1(), triangles_[0].getP2(), triangles_[0].getP3(),
            triangles_[1].getP3()};
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

// Calcul de la surface
float Quad3D::surface() const {
    return triangles_[0].area() + triangles_[1].area();
}

// Vérifie si un point est un sommet du quad
bool Quad3D::isVertex(const Point3D& p) const {
    return triangles_[0].isVertex(p) || triangles_[1].isVertex(p);
}

// Vérifie si deux quads partagent un côté
bool Quad3D::hasCommonSide(const Quad3D& other) const {
    return triangles_[0].hasCommonSide(other.getFirstTriangle()) ||
           triangles_[0].hasCommonSide(other.getSecondTriangle()) ||
           triangles_[1].hasCommonSide(other.getFirstTriangle()) ||
           triangles_[1].hasCommonSide(other.getSecondTriangle());
}

// Vérifie si deux quads ont la même surface
bool Quad3D::sameSurface(const Quad3D& other) const {
    return std::fabs(surface() - other.surface()) < TOLERANCE;
}

// Comparaison de quads
bool Quad3D::equals(const Quad3D& other) const {
    return (triangles_[0].equals(other.getFirstTriangle()) &&
            triangles_[1].equals(other.getSecondTriangle())) ||
           (triangles_[0].equals(other.getSecondTriangle()) &&
            triangles_[1].equals(other.getFirstTriangle()));
}

// Surcharge de l'opérateur ==
bool Quad3D::operator==(const Quad3D& other) const {
    return equals(other);
}

void Quad3D::orient(const Point3D& eye) {
    triangles_[0].orient(eye);
    triangles_[1].orient(eye);

    auto normal1 = triangles_[0].getNormale();
    auto normal2 = triangles_[1].getNormale();

    if (normal1.dotProduct(normal2) < 0) {
        triangles_[1].swapVertices(1, 3);
    }
}

Point3D Quad3D::center() const {
    auto vertices = getVertices();
    Point3D center;
    for (const auto& vertex : vertices) {
        center = center + vertex;
    }
    return center / static_cast<float>(vertices.size());
}

// Surcharge de l'opérateur <<
std::ostream& operator<<(std::ostream& os, const Quad3D& quad) {
    os << "Quad3D:\n";
    os << "  Triangle 1: " << quad.getFirstTriangle() << "\n";
    os << "  Triangle 2: " << quad.getSecondTriangle() << "\n";
    return os;
}

void Quad3D::rotate(float angle, char axis) {
    Point3D quadCenter = center();

    triangles_[0].rotate(angle, axis, quadCenter);
    triangles_[1].rotate(angle, axis, quadCenter);
}

void Quad3D::rotate(float angle, char axis, const Point3D& center) {
    triangles_[0].rotate(angle, axis, center);
    triangles_[1].rotate(angle, axis, center);
}

float Quad3D::averageDepth() const {
    return (triangles_[0].averageDepth() + triangles_[1].averageDepth()) / 2.0f;
}