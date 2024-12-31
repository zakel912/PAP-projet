#include "triangle2d.h"
#include <cmath>
#include <stdexcept>

// Constructeur par défaut
Triangle2D::Triangle2D()
    : p1(Point2D(0, 0)), p2(Point2D(0, 0)), p3(Point2D(0, 0)), color(Couleur(0, 0, 0)), depth(0.0f) {}

// Constructeur avec trois sommets et une couleur RVB
Triangle2D::Triangle2D(const Point2D& point1, const Point2D& point2, const Point2D& point3, int rouge, int vert, int bleu, float depthValue)
    : p1(point1), p2(point2), p3(point3), color(Couleur(rouge, vert, bleu)), depth(depthValue) {
    if (Point2D::distance(p1, p2) == 0 || Point2D::distance(p1, p3) == 0 || Point2D::areCollinear(p1, p2, p3)) {
        throw std::runtime_error("Les trois points doivent former un triangle valide.");
    }
}

// Constructeur avec trois sommets et une couleur (objet Couleur)
Triangle2D::Triangle2D(const Point2D& p1, const Point2D& p2, const Point2D& p3, const Couleur& color, float depthValue)
    : Triangle2D(p1, p2, p3, color.getRouge(), color.getVert(), color.getBleu(), depthValue) {}

// Accesseurs pour les sommets
Point2D Triangle2D::getP1() const {
    return p1;
}

Point2D Triangle2D::getP2() const {
    return p2;
}

Point2D Triangle2D::getP3() const {
    return p3;
}

// Accesseur pour la couleur
Couleur Triangle2D::getColor() const {
    return color;
}

// Modificateur pour la couleur (objet Couleur)
void Triangle2D::setColor(const Couleur& color) {
    this->color = color;
}

// Modificateur pour la couleur (composantes RVB)
void Triangle2D::setColor(int rouge, int vert, int bleu) {
    color.setRouge(rouge);
    color.setVert(vert);
    color.setBleu(bleu);
}

// Calcul du périmètre
float Triangle2D::perimeter() const {
    return p1.distance(p2) + p2.distance(p3) + p3.distance(p1);
}

// Calcul de l'aire
float Triangle2D::area() const {
    return std::fabs((p1.getX() * (p2.getY() - p3.getY()) +
                      p2.getX() * (p3.getY() - p1.getY()) +
                      p3.getX() * (p1.getY() - p2.getY())) / 2.0f);
}

// Vérifie si un point est à l'intérieur du triangle
bool Triangle2D::contains(const Point2D& point) const {
    float totalArea = area();
    float area1 = Triangle2D(point, p2, p3, color, depth).area();
    float area2 = Triangle2D(p1, point, p3, color, depth).area();
    float area3 = Triangle2D(p1, p2, point, color, depth).area();

    return std::abs(totalArea - (area1 + area2 + area3)) < 1e-6;
}

// Surcharge de l'opérateur <<
std::ostream& operator<<(std::ostream& os, const Triangle2D& triangle) {
    os << "Triangle2D[" << "P1: " << triangle.getP1() 
       << ", P2: " << triangle.getP2() 
       << ", P3: " << triangle.getP3() 
       << ", Color: (" << triangle.getColor().getRouge() << ", " 
       << triangle.getColor().getVert() << ", " 
       << triangle.getColor().getBleu() << ")"
       << ", Depth: " << triangle.getDepth()
       << "]";
    return os;
}