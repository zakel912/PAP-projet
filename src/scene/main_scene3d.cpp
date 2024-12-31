#include "scene3d.h"
#include "../geometry/pave3d.h"
#include "../geometry/sphere3d.h"
#include "../geometry/triangle2d.h"
#include "../geometry/point3d.h"
#include "../geometry/point2d.h"
#include <iostream>
#include <memory>
#include <vector>

int main() {
    try {
        // Initialiser la scène avec une position de l'œil, un point de visée et une distance de projection
        Scene3D scene(Point3D(0, 0, 10), Point3D(0, 0, 20), 5.0f);
        std::cout << "Scène initialisée avec :\n"
                << "  Oeil : (0, 0, 10)\n"
                << "  Point cible : (0, 0, 20)\n"
                << "  Distance du plan de projection : 5.0\n";

        // Ajouter un cube rouge à la scène
        auto redCube = std::make_shared<Pave3D>(
            std::array<Quad3D, 6>{
                Quad3D(Point3D(-5, -5, 15), Point3D(5, -5, 15), Point3D(5, 5, 15), Point3D(-5, 5, 15), Couleur(255, 0, 0)),
                Quad3D(Point3D(-5, -5, 20), Point3D(5, -5, 20), Point3D(5, 5, 20), Point3D(-5, 5, 20), Couleur(255, 0, 0)),
                Quad3D(Point3D(-5, -5, 15), Point3D(-5, 5, 15), Point3D(-5, 5, 20), Point3D(-5, -5, 20), Couleur(255, 0, 0)),
                Quad3D(Point3D(5, -5, 15), Point3D(5, 5, 15), Point3D(5, 5, 20), Point3D(5, -5, 20), Couleur(255, 0, 0)),
                Quad3D(Point3D(-5, 5, 15), Point3D(5, 5, 15), Point3D(5, 5, 20), Point3D(-5, 5, 20), Couleur(255, 0, 0)),
                Quad3D(Point3D(-5, -5, 15), Point3D(5, -5, 15), Point3D(5, -5, 20), Point3D(-5, -5, 20), Couleur(255, 0, 0))
            },
            Couleur(255, 0, 0)
        );
        scene.addCube(redCube);
        std::cout << "Cube rouge ajouté à la scène.\n";

        auto greenSphere = std::make_shared<Sphere3D>(Point3D(0, 0, 18), Couleur(0, 255, 0), 3.0f, 6);
        scene.addSphere(greenSphere);
        std::cout << "Sphère verte ajoutée à la scène.\n";


        // Récupérer les triangles projetés
        std::vector<Triangle2D> projectedTriangles = scene.getProjectedTriangles();
        std::cout << "Triangles projetés :\n";
        if (projectedTriangles.empty()) {
            std::cout << "Aucun triangle projeté.\n";
        } else {
            for (const auto& triangle : projectedTriangles) {
                std::cout << triangle << "\n";
            }
        }

    } catch (const std::exception& e) {
        std::cerr << "Erreur : " << e.what() << "\n";
        return 1;
    }

    return 0;
}