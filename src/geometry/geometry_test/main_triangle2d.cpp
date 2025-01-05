#include <cassert>
#include <iostream>
#include "../triangle2d.h"
#include "../geometry_utils.h"

void testTriangle2D() {
    // Points pour les tests
    Point2D p1(0, 0);
    Point2D p2(4, 0);
    Point2D p3(0, 3);

    // Test du constructeur par défaut
    Triangle2D defaultTriangle;
    assert(defaultTriangle.getP1() == Point2D(0, 0));
    assert(defaultTriangle.getP2() == Point2D(0, 0));
    assert(defaultTriangle.getP3() == Point2D(0, 0));
    assert(defaultTriangle.getColor() == Couleur(255, 255, 255));
    assert(std::abs(defaultTriangle.getDepth()) < TOLERANCE);

    // Test du constructeur avec points, couleur et profondeur
    Triangle2D triangle1(p1, p2, p3, 255, 0, 0, 5.0f);
    assert(triangle1.getP1() == p1);
    assert(triangle1.getP2() == p2);
    assert(triangle1.getP3() == p3);
    assert(triangle1.getColor() == Couleur(255, 0, 0));
    assert(std::abs(triangle1.getDepth() - 5.0f) < TOLERANCE);

    // Test du constructeur avec couleur (objet `Couleur`) et profondeur
    Couleur color(0, 255, 0);
    Triangle2D triangle2(p1, p2, p3, color, 10.0f);
    assert(triangle2.getColor() == color);
    assert(std::abs(triangle2.getDepth() - 10.0f) < TOLERANCE);

    // Test de modification de la couleur
    triangle2.setColor(0, 0, 255);
    assert(triangle2.getColor() == Couleur(0, 0, 255));

    triangle2.setColor(color);
    assert(triangle2.getColor() == color);

    // Test du périmètre
    float perimeter = triangle1.perimeter();
    float expectedPerimeter = 5.0f + 4.0f + 3.0f;
    assert(std::abs(perimeter - expectedPerimeter) < TOLERANCE);

    // Test de l'aire
    float area = triangle1.area();
    float expectedArea = 0.5f * 4.0f * 3.0f; // Base * Hauteur / 2
    assert(std::abs(area - expectedArea) < TOLERANCE);

    // Test de `contains` (point à l'intérieur du triangle)
    Point2D insidePoint(1, 1);
    assert(triangle1.contains(insidePoint) == true);

    // Test de `contains` (point à l'extérieur du triangle)
    Point2D outsidePoint(5, 5);
    assert(triangle1.contains(outsidePoint) == false);

    // Test de translation
    Point2D translation(1, 1);
    triangle1.translate(translation);
    assert(triangle1.getP1() == Point2D(1, 1));
    assert(triangle1.getP2() == Point2D(5, 1));
    assert(triangle1.getP3() == Point2D(1, 4));

    // Test de l'opérateur de flux (affichage)
    std::cout << triangle1 << std::endl;

    std::cout << "All Triangle2D tests passed!" << std::endl;
}

int main() {
    testTriangle2D();
    return 0;
}