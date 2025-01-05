#include <cassert>
#include <iostream>
#include "../point3d.h"
#include "../geometry_utils.h"


void testPoint3D() {
    // Test du constructeur par défaut
    Point3D p1;
    assert(std::abs(p1.getX()) < TOLERANCE && std::abs(p1.getY()) < TOLERANCE && std::abs(p1.getZ()) < TOLERANCE);

    // Test du constructeur avec paramètres
    Point3D p2(1.0f, 2.0f, 3.0f);
    assert(std::abs(p2.getX() - 1.0f) < TOLERANCE && std::abs(p2.getY() - 2.0f) < TOLERANCE && std::abs(p2.getZ() - 3.0f) < TOLERANCE);

    // Test de la distance entre deux points
    Point3D p3(5.0f, 6.0f, 7.0f);
    float dist = p3.distance(p2);
    float expectedDist = std::sqrt(std::pow(5.0f - 1.0f, 2) + std::pow(6.0f - 2.0f, 2) + std::pow(7.0f - 3.0f, 2));
    assert(std::abs(dist - expectedDist) < TOLERANCE);

    // Test de la distance statique
    float staticDist = Point3D::distance(p3, p2);
    assert(std::abs(staticDist - expectedDist) < TOLERANCE);

    // Test du produit scalaire
    Point3D p4(2.0f, 3.0f, 4.0f);
    float dot = p2.dotProduct(p4);
    float expectedDot = 1.0f * 2.0f + 2.0f * 3.0f + 3.0f * 4.0f;
    assert(std::abs(dot - expectedDot) < TOLERANCE);

    // Test du produit vectoriel
    Point3D cross = p2.crossProduct(p4);
    Point3D expectedCross(-1.0f, 2.0f, -1.0f);
    assert(std::abs(cross.getX() - expectedCross.getX()) < TOLERANCE);
    assert(std::abs(cross.getY() - expectedCross.getY()) < TOLERANCE);
    assert(std::abs(cross.getZ() - expectedCross.getZ()) < TOLERANCE);

    // Test de la norme
    float norm = p2.norm();
    float expectedNorm = std::sqrt(1.0f * 1.0f + 2.0f * 2.0f + 3.0f * 3.0f);
    assert(std::abs(norm - expectedNorm) < TOLERANCE);

    // Test de colinéarité
    Point3D p5(2.0f, 4.0f, 6.0f);
    assert(Point3D::areCollinear(p1, p2, p5) == true);
    assert(Point3D::areCollinear(Point3D(1, 2, 3), Point3D(2, 4, 6), Point3D(3, 6, 9)) == true);

    // Test des opérateurs
    Point3D sum = p2 + p4;
    Point3D expectedSum(3.0f, 5.0f, 7.0f);
    assert(sum == expectedSum);

    Point3D diff = p4 - p2;
    Point3D expectedDiff(1.0f, 1.0f, 1.0f);
    assert(diff == expectedDiff);

    Point3D scaled = p2 * 2.0f;
    Point3D expectedScaled(2.0f, 4.0f, 6.0f);
    assert(scaled == expectedScaled);

    Point3D divided = p4 / 2.0f;
    Point3D expectedDivided(1.0f, 1.5f, 2.0f);
    assert(std::abs(divided.getX() - expectedDivided.getX()) < TOLERANCE);
    assert(std::abs(divided.getY() - expectedDivided.getY()) < TOLERANCE);
    assert(std::abs(divided.getZ() - expectedDivided.getZ()) < TOLERANCE);

    std::cout << "All Point3D tests passed!" << std::endl;
}

int main() {
    testPoint3D();
    return 0;
}