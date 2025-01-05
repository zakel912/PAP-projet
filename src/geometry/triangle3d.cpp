#include "triangle3d.h"
#include <stdexcept>
#include <cmath>
#include "geometry_utils.h"

// Constructeur par défaut
Triangle3D::Triangle3D() : p1(Point3D(0,0,0)), p2(Point3D(0,0,0)), p3(Point3D(0,0,0)), color(Couleur()) {}

// Constructeur avec trois sommets et une couleur RGB
Triangle3D::Triangle3D(const Point3D& p1, const Point3D& p2, const Point3D& p3, int rouge, int vert, int bleu)
    : p1(p1), p2(p2), p3(p3), color(rouge, vert, bleu) {
    if (rouge < 0 || rouge > 255 || vert < 0 || vert > 255 || bleu < 0 || bleu > 255) {
        throw std::runtime_error("Les valeurs RGB doivent être comprises entre 0 et 255.");
    }
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
    Point3D u = p2 - p1;
    Point3D v = p3 - p1;

    // Norme du produit vectoriel divisé par 2
    Point3D cross = u.crossProduct(v);
    return std::sqrt(cross.dotProduct(cross)) / 2.0f;
}

// Vérifie si un point est un sommet du triangle
bool Triangle3D::isVertex(const Point3D& p) const {
    return p1.equals(p) || p2.equals(p) || p3.equals(p);
}

bool Triangle3D::isDegenerate() const {
    // Si deux sommets sont identiques ou si les trois sommets sont colinéaires
    return p1 == p2 || p2 == p3 || p1 == p3 ||
           area() < TOLERANCE; // Norme du produit vectoriel proche de zéro
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

    Point3D u = p2 - p1;
    Point3D v = p3 - p1;

    Point3D normale = u.crossProduct(v);

    if (normale.dotProduct(normale) < TOLERANCE) { // Norme² proche de zéro
        std::cout << "Triangle dégénéré : impossible de calculer la normale.\n";
    }
    return normale;
}

void Triangle3D::swapVertices(int i, int j) {
    if (i < 1 || i > 3 || j < 1 || j > 3) {
        throw std::invalid_argument("Les indices doivent être compris entre 1 et 3.");
    }

    if (i == j) return;

    Point3D* points[] = {&p1, &p2, &p3};

    std::swap(*points[i - 1], *points[j - 1]);
}

void Triangle3D::orient(const Point3D& pointOfView) {
    Point3D normale = getNormale();
    Point3D viewVector = pointOfView - getCentroid();

    // Si le produit scalaire entre la normale et le vecteur de vue est négatif, les sommets sont dans le sens horaire
    if (normale.dotProduct(viewVector) < 0) {
        std::swap(p2, p3);
    }
}

Point3D Triangle3D::getCentroid() const {
    float x = (p1.getX() + p2.getX() + p3.getX()) / 3.0f;
    float y = (p1.getY() + p2.getY() + p3.getY()) / 3.0f;
    float z = (p1.getZ() + p2.getZ() + p3.getZ()) / 3.0f;

    return Point3D(x, y, z);
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

void Triangle3D::rotate(float angle, char axis, const Point3D& center) {

    auto rotatePoint = [&](const Point3D& point) -> Point3D {
        float x = point.getX() - center.getX();
        float y = point.getY() - center.getY();
        float z = point.getZ() - center.getZ();

        float cosAngle = std::cos(angle);
        float sinAngle = std::sin(angle);

        float newX = x, newY = y, newZ = z;

        switch (axis) {
            case 'x':
                newY = y * cosAngle - z * sinAngle;
                newZ = y * sinAngle + z * cosAngle;
                break;
            case 'y':
                newX = x * cosAngle + z * sinAngle;
                newZ = -x * sinAngle + z * cosAngle;
                break;
            case 'z':
                newX = x * cosAngle - y * sinAngle;
                newY = x * sinAngle + y * cosAngle;
                break;
            default:
                throw std::invalid_argument("Axe invalide. Utilisez 'x', 'y' ou 'z'.");
        }

        return Point3D(newX + center.getX(), newY + center.getY(), newZ + center.getZ());
    };

    p1 = rotatePoint(p1);
    p2 = rotatePoint(p2);
    p3 = rotatePoint(p3);
}