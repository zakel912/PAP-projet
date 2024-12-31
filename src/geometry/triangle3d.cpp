#include "triangle3d.h"
#include <stdexcept>
#include <cmath>

// Constructeur par défaut
Triangle3D::Triangle3D() : p1(Point3D()), p2(Point3D()), p3(Point3D()), color(Couleur()) {}

// Constructeur avec trois sommets et une couleur RGB
Triangle3D::Triangle3D(const Point3D& p1, const Point3D& p2, const Point3D& p3, int rouge, int vert, int bleu)
    : p1(p1), p2(p2), p3(p3), color(rouge, vert, bleu) {
    if (Point3D::areCollinear(p1, p2, p3)) {
        throw std::runtime_error("Les trois sommets ne doivent pas être alignés.");
    }
}

// Constructeur avec trois sommets et une couleur (objet Couleur)
Triangle3D::Triangle3D(const Point3D& p1, const Point3D& p2, const Point3D& p3, const Couleur& color)
    : p1(p1), p2(p2), p3(p3), color(color) {
    if (Point3D::areCollinear(p1, p2, p3)) {
        throw std::runtime_error("Les trois sommets ne doivent pas être alignés.");
    }
}

// Constructeur par copie
Triangle3D::Triangle3D(const Triangle3D& other) 
    : p1(other.p1), p2(other.p2), p3(other.p3), color(other.color) {}

// Accesseurs
const Point3D& Triangle3D::getP1() const { return p1; }
const Point3D& Triangle3D::getP2() const { return p2; }
const Point3D& Triangle3D::getP3() const { return p3; }

float Triangle3D::averageDepth() const {
    return (p1.getZ() + p2.getZ() + p3.getZ()) / 3.0f;
}

// Calcul du périmètre
float Triangle3D::perimeter() const {
    return p1.distance(p2) + p2.distance(p3) + p3.distance(p1);
}

// Calcul de l'aire
float Triangle3D::area() const {
    float a = p1.distance(p2);
    float b = p2.distance(p3);
    float c = p3.distance(p1);
    float s = (a + b + c) / 2; // Semi-périmètre
    return std::sqrt(s * (s - a) * (s - b) * (s - c));
}

// Vérifie si un point est un sommet du triangle
bool Triangle3D::isVertex(const Point3D& p) const {
    return p1.equals(p) || p2.equals(p) || p3.equals(p);
}

// Vérifie si le triangle est dégénéré
bool Triangle3D::isDegenerate() const {
    return area() < 1e-6; // Tolérance pour les erreurs de précision flottante
}

// Vérifie si deux triangles partagent un côté
bool Triangle3D::hasCommonSide(const Triangle3D& other) const {
    int sharedVertices = 0;
    if (isVertex(other.getP1())) ++sharedVertices;
    if (isVertex(other.getP2())) ++sharedVertices;
    if (isVertex(other.getP3())) ++sharedVertices;
    return sharedVertices >= 2;
}

// Comparaison de triangles
bool Triangle3D::equals(const Triangle3D& other) const {
    return (p1 == other.getP1() && p2 == other.getP2() && p3 == other.getP3()) ||
           (p1 == other.getP2() && p2 == other.getP3() && p3 == other.getP1()) ||
           (p1 == other.getP3() && p2 == other.getP1() && p3 == other.getP2());
}

Point3D Triangle3D::getNormale() const {
    // Vecteurs formés par les arêtes du triangle
    Point3D u = p2 - p1;
    Point3D v = p3 - p1;

    // Produit vectoriel pour obtenir la normale
    Point3D normale = u.crossProduct(v);

    // Vérification : si la longueur de la normale est nulle, le triangle est dégénéré
    if (normale.dotProduct(normale) < 1e-6) { // Norme² proche de zéro
        throw std::runtime_error("Triangle dégénéré : impossible de calculer la normale.");
    }

    return normale;
}

bool Triangle3D::isValid() const {
    return !Point3D::areCollinear(p1, p2, p3);
}


// Surcharge de l'opérateur <<
std::ostream& operator<<(std::ostream& os, const Triangle3D& triangle) {
    os << "Triangle3D[" 
       << "P1: " << triangle.getP1() 
       << ", P2: " << triangle.getP2() 
       << ", P3: " << triangle.getP3() 
       << ", Color: (" << triangle.getColor().getRouge() << ", " 
       << triangle.getColor().getVert() << ", " 
       << triangle.getColor().getBleu() << ")"
       << ", Average Depth: " << triangle.averageDepth()
       << "]";
    return os;
}
