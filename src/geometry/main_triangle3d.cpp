#include <cassert>
#include <iostream>
#include "triangle3d.h"
#include "geometry_utils.h"

void testTriangle3D() {
    // Points pour les tests
    Point3D p1(0, 0, 0);
    Point3D p2(3, 0, 0);
    Point3D p3(0, 4, 0);
    Point3D p4(1, 1, 1); // Point hors du plan de p1, p2, p3

    // Test du constructeur par défaut
    Triangle3D defaultTriangle;
    assert(defaultTriangle.getP1() == Point3D(0, 0, 0));
    assert(defaultTriangle.getP2() == Point3D(0, 0, 0));
    assert(defaultTriangle.getP3() == Point3D(0, 0, 0));
    assert(defaultTriangle.getColor() == Couleur(255, 255, 255));
    std::cout<<"check1"<<std::endl;

    // Test du constructeur avec trois sommets et une couleur
    Triangle3D triangle1(p1, p2, p3, 255, 0, 0);
    assert(triangle1.getP1() == p1);
    assert(triangle1.getP2() == p2);
    assert(triangle1.getP3() == p3);
    assert(triangle1.getColor() == Couleur(255, 0, 0));
    std::cout<<"check2"<<std::endl;

    // Test du constructeur avec objet Couleur
    Couleur color(0, 255, 0);
    Triangle3D triangle2(p1, p2, p3, color);
    assert(triangle2.getColor() == color);
    std::cout<<"check3"<<std::endl;

    // Test de la modification de la couleur
    triangle2.setColor(0, 0, 255);
    assert(triangle2.getColor() == Couleur(0, 0, 255));

    triangle2.setColor(color);
    assert(triangle2.getColor() == color);
        std::cout<<"check4"<<std::endl;

    // Test du périmètre
    float perimeter = triangle1.perimeter();
    float expectedPerimeter = p1.distance(p2) + p2.distance(p3) + p3.distance(p1);
    assert(std::abs(perimeter - expectedPerimeter) < TOLERANCE);
    std::cout<<"check5"<<std::endl;

    // Test de l'aire
    float area = triangle1.area();
    float expectedArea = 0.5f * 3.0f * 4.0f; // Base * Hauteur / 2
    assert(std::abs(area - expectedArea) < TOLERANCE);
    std::cout<<"check6"<<std::endl;

    // Test de `isVertex`
    assert(triangle1.isVertex(p1) == true);
    assert(triangle1.isVertex(p4) == false);
    std::cout<<"check7"<<std::endl;

    // Test de colinéarité (areCollinear)
    assert(Point3D::areCollinear(p1, p2, Point3D(6, 0, 0)) == true);
    assert(Point3D::areCollinear(p1, p2, p3) == false);
    std::cout << "check7.5" << std::endl;

    // Test de colinéarité (triangle dégénéré)
    Triangle3D notDegenerateTriangle(p1, p2, p3);
    assert(notDegenerateTriangle.isDegenerate() == false);
    std::cout<<"check8"<<std::endl;

    // Test de la normale
    Point3D normal = triangle1.getNormale();
    Point3D expectedNormal(0, 0, 12); // Produit vectoriel des vecteurs (p2 - p1) et (p3 - p1)
    assert(std::abs(normal.getX() - expectedNormal.getX()) < TOLERANCE);
    assert(std::abs(normal.getY() - expectedNormal.getY()) < TOLERANCE);
    assert(std::abs(normal.getZ() - expectedNormal.getZ()) < TOLERANCE);
    std::cout<<"check9"<<std::endl;

    // Test du centroïde
    Point3D centroid = triangle1.getCentroid();
    Point3D expectedCentroid(1.0f, 4.0f / 3.0f, 0);
    assert(std::abs(centroid.getX() - expectedCentroid.getX()) < TOLERANCE);
    assert(std::abs(centroid.getY() - expectedCentroid.getY()) < TOLERANCE);
    assert(std::abs(centroid.getZ() - expectedCentroid.getZ()) < TOLERANCE);
    std::cout<<"check10"<<std::endl;

    // Test de translation
    triangle1.translate(Point3D(1, 1, 1));
    assert(triangle1.getP1() == Point3D(1, 1, 1));
    assert(triangle1.getP2() == Point3D(4, 1, 1));
    assert(triangle1.getP3() == Point3D(1, 5, 1));
    std::cout<<"check11"<<std::endl;

    // Test de visibilité (colinéarité)
    assert(triangle1.isValid() == true);
    assert(notDegenerateTriangle.isValid() == true);
    std::cout<<"check12"<<std::endl;

    // Test de la méthode orient
    Point3D eye(0, 0, 5); // Position de la caméra (point de vue)
    triangle2.orient(eye);

    // Vérification des sommets dans le sens antihoraire
    Point3D direction = eye - triangle2.getCentroid();
    assert(normal.dotProduct(direction) > 0); // Vérifie que la normale pointe vers l'œil
    std::cout << "check13 (orient test passed)" << std::endl;

    Triangle3D triangle(p1, p2, p3);
    // Vérification initiale
    assert(triangle.getP1() == p1);
    assert(triangle.getP2() == p2);
    assert(triangle.getP3() == p3);

    // Échange de p1 et p2
    triangle.swapVertices(1, 2);
    assert(triangle.getP1() == p2); // p1 et p2 échangés
    assert(triangle.getP2() == p1);
    assert(triangle.getP3() == p3); // p3 inchangé

    // Échange de p2 et p3
    triangle.swapVertices(2, 3);
    assert(triangle.getP1() == p2); // p1 inchangé
    assert(triangle.getP2() == p3); // p2 et p3 échangés
    assert(triangle.getP3() == p1);

    // Échange de p1 et p3
    triangle.swapVertices(1, 3);
    assert(triangle.getP1() == p1); // p1 et p3 échangés
    assert(triangle.getP2() == p3);
    assert(triangle.getP3() == p2);

    // Pas de changement si i == j
    triangle.swapVertices(2, 2);
    assert(triangle.getP1() == p1);
    assert(triangle.getP2() == p3);
    assert(triangle.getP3() == p2);

    std::cout << "check14 testSwapVertices passed!" << std::endl;

    // Test de l'opérateur de flux
    std::cout << triangle1 << std::endl;

    std::cout << "All Triangle3D tests passed!" << std::endl;
}

int main() {
    testTriangle3D();
    return 0;
}
