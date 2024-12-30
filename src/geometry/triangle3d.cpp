#include "triangle3d.h"
#include <stdexcept>



Triangle3D::Triangle3D() : p1(), p2(), p3() {}

Triangle3D::Triangle3D(const Point3D& p1, const Point3D& p2, const Point3D& p3){

    // Vérifier que les trois sommets ne sont pas alignés
    if (p1.areCollinear(p1, p2, p3)) {
        throw std::runtime_error("Les trois sommets ne doivent pas être alignés.");
    }
    this->p1 = p1;
    this->p2 = p2;
    this->p3 = p3;
}

Triangle3D::Triangle3D(const Triangle3D& other)
    : p1(other.p1), p2(other.p2), p3(other.p3) {}

Triangle3D::~Triangle3D() {}

const Point3D& Triangle3D::getP1() const {
    return p1;
}

const Point3D& Triangle3D::getP2() const {
    return p2;
}

const Point3D& Triangle3D::getP3() const {
    return p3;
}

float Triangle3D::area() const {
    float a = p1.distance(p2);
    float b = p2.distance(p3);
    float c = p3.distance(p1);
    float s = (a + b + c) / 2; // Semi-périmètre
    return std::sqrt(s * (s - a) * (s - b) * (s - c));
}

float Triangle3D::perimeter() const {
    return p1.distance(p2) + p2.distance(p3) + p3.distance(p1);
}

bool Triangle3D::isDegenerate() const {
    return area() < 1e-6; // Une petite tolérance pour les erreurs de précision flottante
}

bool Triangle3D::isVertex(const Point3D& p) const{
    return p1.equals(p) || p2.equals(p) || p3.equals(p);
}

bool Triangle3D::hasCommonSide(const Triangle3D& other) const {
    int sharedVertices = 0;
    if (isVertex(other.getP1())) ++sharedVertices;
    if (isVertex(other.getP2())) ++sharedVertices;
    if (isVertex(other.getP3())) ++sharedVertices;
    return sharedVertices >= 2;
}

bool Triangle3D::hasCommonSide(const Triangle3D& t1, const Triangle3D& t2){
    return t1.hasCommonSide(t2);
}

bool Triangle3D::equals(const Triangle3D& other) const {
    return (p1 == other.getP1() && p2 == other.getP2() && p3 == other.getP3()) ||
           (p1 == other.getP2() && p2 == other.getP3() && p3 == other.getP1()) ||
           (p1 == other.getP3() && p2 == other.getP1() && p3 == other.getP2());
}

std::ostream& operator<<(std::ostream& os, const Triangle3D& triangle) {
    os << "Triangle3D("
       << triangle.getP1() << ", "
       << triangle.getP2() << ", "
       << triangle.getP3() << ")";
    return os;
}
