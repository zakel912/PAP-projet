#include <iostream>
#include <vector>
#include "scene3d.h"
#include "sdl/renderer.h"

int main() {
    try {
        // Dimensions de la fenêtre
        const int windowWidth = 800;
        const int windowHeight = 600;

        // Initialisation de la scène avec un œil plus proche et une cible ajustée
        Scene3D scene(Point3D(0, 0, 20), Point3D(-20, -20, 30), 5.0f);
        std::cout << "Scène initialisée avec :\n"
                  << "  Oeil : (0, 0, 20)\n"
                  << "  Point cible : (0, 0, 30)\n"
                  << "  Distance du plan de projection : 5.0\n";

        // Ajout d'un cube rouge plus grand et centré pour bien remplir la scène
        auto redCube = std::make_shared<Pave3D>(
            std::array<Quad3D, 6>{
                Quad3D(Point3D(-10, -10, 40), Point3D(10, -10, 40), Point3D(10, 10, 40), Point3D(-10, 10, 40), Couleur(255, 0, 0)),
                Quad3D(Point3D(-10, -10, 30), Point3D(10, -10, 30), Point3D(10, 10, 30), Point3D(-10, 10, 30), Couleur(255, 0, 0)),
                Quad3D(Point3D(-10, -10, 40), Point3D(-10, 10, 40), Point3D(-10, 10, 30), Point3D(-10, -10, 30), Couleur(255, 0, 0)),
                Quad3D(Point3D(10, -10, 40), Point3D(10, 10, 40), Point3D(10, 10, 30), Point3D(10, -10, 30), Couleur(255, 0, 0)),
                Quad3D(Point3D(-10, 10, 40), Point3D(10, 10, 40), Point3D(10, 10, 30), Point3D(-10, 10, 30), Couleur(255, 0, 0)),
                Quad3D(Point3D(-10, -10, 40), Point3D(10, -10, 40), Point3D(10, -10, 30), Point3D(-10, -10, 30), Couleur(255, 0, 0))
            },
            Couleur(255, 0, 0)
        );
        scene.addCube(redCube);
        std::cout << "Cube rouge ajouté à la scène.\n";

        // Ajout d'une sphère verte bien visible et plus grande
        auto greenSphere = std::make_shared<Sphere3D>(Point3D(0, 0, 35), Couleur(0, 255, 0), 5.0f, 8);
        scene.addSphere(greenSphere);
        std::cout << "Sphère verte ajoutée à la scène.\n";

        // Récupération des triangles projetés
        std::vector<Triangle2D> projectedTriangles = scene.getProjectedTriangles();

        // Initialisation du renderer SDL
        Renderer renderer(windowWidth, windowHeight);

        // Rendu de la scène
        renderer.renderScene(projectedTriangles);

        // Pause avant de quitter
        SDL_Delay(5000);

    } catch (const std::exception& e) {
        std::cerr << "Erreur : " << e.what() << "\n";
        return 1;
    }

    return 0;
}