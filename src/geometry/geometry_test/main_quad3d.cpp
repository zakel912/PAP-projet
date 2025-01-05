#include <cassert>
#include <iostream>
#include "../quad3d.h"

void testQuad3D() {
    // Points pour les tests
    Point3D p1(0, 0, 0);
    Point3D p2(1, 0, 0);
    Point3D p3(1, 1, 0);
    Point3D p4(0, 1, 0);

    // Test du constructeur par défaut
    Quad3D defaultQuad;
    assert(defaultQuad.getFirstTriangle().isDegenerate() == true);
    assert(defaultQuad.getSecondTriangle().isDegenerate() == true);
    std::cout << "check1" << std::endl;

    // Test du constructeur avec quatre points
    Quad3D quad1(p1, p2, p3, p4, 255, 0, 0);
    assert(quad1.getFirstTriangle().getColor() == Couleur(255, 0, 0));
    assert(quad1.getSecondTriangle().getColor() == Couleur(255, 0, 0));
    std::cout << "check2" << std::endl;

    // Test du constructeur avec deux triangles
    Triangle3D t1(p1, p2, p3, 0, 255, 0);
    Triangle3D t2(p1, p3, p4, 0, 255, 0);
    Quad3D quad2(t1, t2, 0, 255, 0);
    assert(quad2.getFirstTriangle().getColor() == Couleur(0, 255, 0));
    assert(quad2.getSecondTriangle().getColor() == Couleur(0, 255, 0));
    std::cout << "check3" << std::endl;

    // Test de la surface
    float surface = quad1.surface();
    float expectedSurface = t1.area() + t2.area();
    assert(std::abs(surface - expectedSurface) < TOLERANCE);
    std::cout << "check4" << std::endl;

    // Test des couleurs
    quad1.setColor(0, 0, 255);
    assert(quad1.getFirstTriangle().getColor() == Couleur(0, 0, 255));
    assert(quad1.getSecondTriangle().getColor() == Couleur(0, 0, 255));
    quad1.setColor(Couleur(128, 128, 128));
    assert(quad1.getFirstTriangle().getColor() == Couleur(128, 128, 128));
    std::cout << "check5" << std::endl;

    // Test des sommets
    auto vertices = quad1.getVertices();
    assert(vertices.size() == 4);
    assert(vertices[0] == p1);
    assert(vertices[1] == p2);
    assert(vertices[2] == p3);
    assert(vertices[3] == p4);
    std::cout << "check6" << std::endl;

    // Test de translation
    quad1.translate(Point3D(1, 1, 1));
    assert(quad1.getVertices()[0] == Point3D(1, 1, 1));
    assert(quad1.getVertices()[1] == Point3D(2, 1, 1));
    assert(quad1.getVertices()[2] == Point3D(2, 2, 1));
    assert(quad1.getVertices()[3] == Point3D(1, 2, 1));
    std::cout << "check7" << std::endl;

    // Test du centre
    Point3D center = quad1.center();
    Point3D expectedCenter(1.5, 1.5, 1);
    assert(std::abs(center.getX() - expectedCenter.getX()) < TOLERANCE);
    assert(std::abs(center.getY() - expectedCenter.getY()) < TOLERANCE);
    assert(std::abs(center.getZ() - expectedCenter.getZ()) < TOLERANCE);
    std::cout << "check8" << std::endl;

    // Test de la méthode `isVertex`
    assert(quad1.isVertex(Point3D(1, 1, 1)) == true);
    assert(quad1.isVertex(Point3D(3, 3, 3)) == false);
    std::cout << "check9" << std::endl;

    // Test de la méthode `equals`
    Quad3D quad3 = quad1;
    assert(quad1.equals(quad3) == true);
    std::cout << "check10" << std::endl;

    // Test de `hasCommonSide`
    Quad3D quad4(Point3D(1, 1, 1), Point3D(2, 1, 1), Point3D(2, 2, 1), Point3D(1, 2, 1), 255, 255, 0);
    assert(quad1.hasCommonSide(quad4) == true);
    std::cout << "check11" << std::endl;

    // Test de la méthode `orient`
    Point3D eye(0, 0, 1); // Point de vue au-dessus du quadrilatère
    quad1.orient(eye);

    // Vérification que les sommets sont orientés correctement pour chaque triangle
    auto t1o = quad1.getFirstTriangle();
    auto t2o = quad1.getSecondTriangle();

    Point3D normal1 = t1o.getNormale();
    Point3D normal2 = t2o.getNormale();
    Point3D direction1 = t1o.getCentroid() - eye;
    Point3D direction2 = t2o.getCentroid() - eye;

    assert(normal1.dotProduct(direction1) > -TOLERANCE); // Vérifie que la normale de t1 pointe vers l'œil
    assert(normal2.dotProduct(direction2) > -TOLERANCE); // Vérifie que la normale de t2 pointe vers l'œil

    std::cout << "check12 (orient test passed)" << std::endl;

    std::cout << quad1 << std::endl;
    std::cout << "All Quad3D tests passed!" << std::endl;
}

int main() {
    testQuad3D();
    return 0;
}