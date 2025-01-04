#include <cassert>
#include <iostream>
#include "scene3d.h"
#include "../geometry/pave3d.h"
#include "../geometry/sphere3d.h"
#include "../geometry/quad3d.h"
#include "../geometry/point3d.h"
#include "../geometry/triangle2d.h"

void testScene3D() {
    // Configuration initiale
    Point3D eye(0, 0, 10); // Position de l'œil
    Point3D look_at(0, 0, 0); // Point visé
    float projection_plane_distance = 5.0f;

    Scene3D scene(eye, look_at, projection_plane_distance);
    assert(scene.getEye() == eye);
    assert(scene.getLookAt() == look_at);
    std::cout << "check1: Scène initialisée avec succès.\n";

    // Création d'un cube
    Point3D p1(-1, -1, 9);
    Point3D p2(1, -1, 9);
    Point3D p3(1, 1, 9);
    Point3D p4(-1, 1, 9);
    Point3D p5(-1, -1, 8);
    Point3D p6(1, -1, 8);
    Point3D p7(1, 1, 8);
    Point3D p8(-1, 1, 8);

    Quad3D frontFace(p1, p2, p3, p4, Couleur(255, 0, 0));
    Quad3D backFace(p5, p6, p7, p8, Couleur(0, 255, 0));
    Quad3D leftFace(p1, p4, p8, p5, Couleur(0, 0, 255));
    Quad3D rightFace(p2, p3, p7, p6, Couleur(255, 255, 0));
    Quad3D topFace(p4, p3, p7, p8, Couleur(0, 255, 255));
    Quad3D bottomFace(p1, p2, p6, p5, Couleur(255, 0, 255));

    Pave3D cube(frontFace, backFace, leftFace, rightFace, topFace, bottomFace);
    scene.addCube(cube);
    assert(scene.hasCube());
    std::cout << "check2: Cube ajouté avec succès.\n";

    // Vérification des faces du cube
    for (int i = 0; i < 6; ++i) {
        auto face = cube.getFace(i);
        assert(!Point3D::areCollinear(face.getFirstTriangle().getP1(),
                                      face.getFirstTriangle().getP2(),
                                      face.getFirstTriangle().getP3()));
    }
    std::cout << "check3: Les faces du cube sont valides.\n";

    // Création d'une sphère
    Sphere3D sphere(Point3D(0, 0, 9), 1.0f, 4);
    scene.addSphere(sphere);
    assert(scene.hasSphere());
    std::cout << "check4: Sphère ajoutée avec succès.\n";

    // Vérification des quadrilatères de la sphère
    const auto& quads = sphere.getQuads();
    assert(!quads.empty());
    for (const auto& quad : quads) {
        assert(!Point3D::areCollinear(quad.getFirstTriangle().getP1(),
                                      quad.getFirstTriangle().getP2(),
                                      quad.getFirstTriangle().getP3()));
    }
    std::cout << "check5: Quadrilatères de la sphère vérifiés.\n";

    // Projections des triangles
    auto projectedTriangles = scene.getProjectedTriangles();
    assert(!projectedTriangles.empty());
    std::cout << "check6: Triangles projetés avec succès.\n";

    // Vérification des projections
    for (const auto& triangle : projectedTriangles) {
        assert(triangle.getDepth() > 0); // Les triangles doivent être devant l'œil
    }
    std::cout << "check7: Projections vérifiées avec succès.\n";

    // Modification de l'œil
    Point3D newEye(0, 0, 15);
    scene.setEye(newEye);
    assert(scene.getEye() == newEye);
    std::cout << "check8: Position de l'œil mise à jour avec succès.\n";

    // Vérification après déplacement de l'œil
    auto updatedTriangles = scene.getProjectedTriangles();
    assert(!updatedTriangles.empty());
    std::cout << "check9: Triangles projetés après déplacement de l'œil validés avec succès.\n";

    // Nettoyage de la scène
    scene.clear();
    assert(!scene.hasCube());
    assert(!scene.hasSphere());
    std::cout << "check10: Scène nettoyée avec succès.\n";

    std::cout << "Tous les tests pour Scene3D ont réussi !\n";
}

int main() {
    testScene3D();
    return 0;
}
