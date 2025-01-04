#include <cassert>
#include <iostream>
#include "pave3d.h"
#include "geometry_utils.h"

void testPave3D() {
    // Points pour les tests
    Point3D p1(0, 0, 0);
    Point3D p2(1, 0, 0);
    Point3D p3(1, 1, 0);
    Point3D p4(0, 1, 0);
    Point3D p5(0, 0, 1);
    Point3D p6(1, 0, 1);
    Point3D p7(1, 1, 1);
    Point3D p8(0, 1, 1);

    // Couleurs pour les faces
    Couleur red(255, 0, 0);
    Couleur green(0, 255, 0);
    Couleur blue(0, 0, 255);
    Couleur yellow(255, 255, 0);
    Couleur cyan(0, 255, 255);
    Couleur magenta(255, 0, 255);

    // Faces du pavé
    Quad3D frontFace(p1, p2, p3, p4, red);
    Quad3D backFace(p5, p6, p7, p8, green);
    Quad3D leftFace(p1, p4, p8, p5, blue);
    Quad3D rightFace(p2, p3, p7, p6, yellow);
    Quad3D topFace(p4, p3, p7, p8, cyan);
    Quad3D bottomFace(p1, p2, p6, p5, magenta);

    // Test du constructeur par défaut
    Pave3D defaultPave;
    assert(defaultPave.getFace(0).getColor() == Couleur(255, 255, 255));
    std::cout << "check1" << std::endl;

    // Test du constructeur avec six faces
    std::array<Quad3D, 6> faces = {frontFace, backFace, leftFace, rightFace, topFace, bottomFace};
    Pave3D pave1(faces);
    assert(pave1.getFace(0).getColor() == red);
    assert(pave1.getFace(1).getColor() == green);
    assert(pave1.getFace(2).getColor() == blue);
    assert(pave1.getFace(3).getColor() == yellow);
    assert(pave1.getFace(4).getColor() == cyan);
    assert(pave1.getFace(5).getColor() == magenta);
    std::cout << "check2" << std::endl;

    // Test du constructeur avec faces individuelles
    Pave3D pave2(frontFace, backFace, leftFace, rightFace, topFace, bottomFace);
    assert(pave2.getFace(0).getColor() == red);
    assert(pave2.getFace(1).getColor() == green);
    assert(pave2.getFace(2).getColor() == blue);
    assert(pave2.getFace(3).getColor() == yellow);
    assert(pave2.getFace(4).getColor() == cyan);
    assert(pave2.getFace(5).getColor() == magenta);
    std::cout << "check3" << std::endl;

    // Test de la surface totale
    float surface = pave1.surfaceArea();
    float expectedSurface = 2 * (frontFace.surface() + leftFace.surface() + topFace.surface());
    assert(std::abs(surface - expectedSurface) < TOLERANCE);
    std::cout << "check4" << std::endl;

    // Test du volume
    float volume = pave1.volume();
    float expectedVolume = 1.0f; // Le pavé est un cube de côté 1
    assert(std::abs(volume - expectedVolume) < TOLERANCE);
    std::cout << "check5" << std::endl;

    // Test de translation

    pave1.translate(Point3D(1, 1, 1));
    assert(pave1.getFace(0).getFirstTriangle().getP1() == Point3D(1, 1, 1));
    assert(pave1.getFace(5).getSecondTriangle().getP3() == Point3D(1, 1, 2));
    std::cout << "check6" << std::endl;

    // Test des couleurs individuelles
    pave1.setFaceColor(0, Couleur(128, 128, 128));
    assert(pave1.getFaceColor(0) == Couleur(128, 128, 128));
    std::cout << "check7" << std::endl;

    // Test d'égalité
    Pave3D pave3 = pave2;
    assert(pave3.equals(pave2) == true);
    std::cout << "check8" << std::endl;

    std::cout << pave1 << std::endl;
    std::cout << "All Pave3D tests passed!" << std::endl;
}

int main() {
    testPave3D();
    return 0;
}