#include "triangle2d.h"
#include <cmath>
#include <stdexcept>

// Constructeur par défaut
Triangle2D::Triangle2D() : p1_(Point2D()), p2_(Point2D()), p3_(Point2D()) {}

// Constructeur avec trois sommets
Triangle2D::Triangle2D(const Point2D& p1, const Point2D& p2, const Point2D& p3) : p1_(p1), p2_(p2), p3_(p3) {
    // Vérification que les trois points ne sont pas colinéaires
    float areaValue = std::fabs((p1_.getX() * (p2_.getY() - p3_.getY()) +
                                 p2_.getX() * (p3_.getY() - p1_.getY()) +
                                 p3_.getX() * (p1_.getY() - p2_.getY())) / 2.0f);
    if (areaValue < 1e-6) {
        throw std::runtime_error("Les trois points sont colinéaires. Impossible de former un triangle.");
    }
}

// Accesseurs
Point2D Triangle2D::getP1() const {
    return p1_;
}

Point2D Triangle2D::getP2() const {
    return p2_;
}

Point2D Triangle2D::getP3() const {
    return p3_;
}

// Calcul du périmètre
float Triangle2D::perimeter() const {
    return p1_.distance(p2_) + p2_.distance(p3_) + p3_.distance(p1_);
}

// Calcul de l'aire
float Triangle2D::area() const {
    return std::fabs((p1_.getX() * (p2_.getY() - p3_.getY()) +
                      p2_.getX() * (p3_.getY() - p1_.getY()) +
                      p3_.getX() * (p1_.getY() - p2_.getY())) / 2.0f);
}

// Vérifie si un point est à l'intérieur du triangle
bool Triangle2D::contains(const Point2D& point) const {
    float totalArea = area();

    float area1 = std::fabs((point.getX() * (p2_.getY() - p3_.getY()) +
                             p2_.getX() * (p3_.getY() - point.getY()) +
                             p3_.getX() * (point.getY() - p2_.getY())) / 2.0f);

    float area2 = std::fabs((p1_.getX() * (point.getY() - p3_.getY()) +
                             point.getX() * (p3_.getY() - p1_.getY()) +
                             p3_.getX() * (p1_.getY() - point.getY())) / 2.0f);

    float area3 = std::fabs((p1_.getX() * (p2_.getY() - point.getY()) +
                             p2_.getX() * (point.getY() - p1_.getY()) +
                             point.getX() * (p1_.getY() - p2_.getY())) / 2.0f);

    // Le point est à l'intérieur si la somme des sous-aires est égale à l'aire totale
    return std::fabs(totalArea - (area1 + area2 + area3)) < 1e-6;
}

// Surcharge de l'opérateur <<
std::ostream& operator<<(std::ostream& os, const Triangle2D& triangle) {
    os << "Triangle2D["
       << "P1: " << triangle.getP1() << ", "
       << "P2: " << triangle.getP2() << ", "
       << "P3: " << triangle.getP3()
       << "]";
    return os;
}