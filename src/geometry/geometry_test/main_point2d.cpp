#include <cassert>
#include <iostream>
#include "../point2d.h"

void testPoint2D() {
    // Test du constructeur par défaut
    Point2D p1(0, 0); // Appelle explicitement le constructeur avec `int`.
    assert(p1.getX() == 0 && p1.getY() == 0);

    // Test du constructeur avec paramètres
    Point2D p2(3, 4);
    assert(p2.getX() == 3 && p2.getY() == 4);

    // Test du constructeur par copie
    Point2D p3(p2);
    assert(p3.getX() == p2.getX() && p3.getY() == p2.getY());

    // Test de la distance entre deux points
    Point2D p4(0, 0);
    float dist = p4.distance(p2);
    float expectedDist = std::sqrt(3 * 3 + 4 * 4);
    assert(std::abs(dist - expectedDist) < 1e-6);

    // Test de la distance statique
    float staticDist = Point2D::distance(p4, p2);
    assert(std::abs(staticDist - expectedDist) < 1e-6);

    // Test de colinéarité
    Point2D p5(6, 8); // Multiples scalaires de (3, 4)
    assert(Point2D::areCollinear(p4, p2, p5) == true);
    Point2D p6(1, 2);
    assert(Point2D::areCollinear(p4, p2, p6) == false);

    // Test des opérateurs
    Point2D sum = p2 + p5;
    Point2D expectedSum(9, 12);
    assert(sum == expectedSum);

    Point2D diff = p5 - p2;
    Point2D expectedDiff(3, 4);
    assert(diff == expectedDiff);

    // Test des opérateurs d'égalité
    assert(p2 == p3);
    assert(p2 != p4);

    // Test des setters
    p1.setX(10);
    p1.setY(20);
    assert(p1.getX() == 10 && p1.getY() == 20);

    // Test de l'opérateur d'affichage
    std::cout << "Testing Point2D output operator:" << std::endl;
    std::cout << "Point: " << p2 << std::endl;

    std::cout << "All Point2D tests passed!" << std::endl;
}

int main() {
    testPoint2D();
    return 0;
}