#include "sphere3d.h"
#include "quad3d.h"
#include "point3d.h"
#include "../couleur.h"
#include <iostream>

int main() {
    try {
        // === TEST DES CONSTRUCTEURS ===
        std::cout << "=== TEST DES CONSTRUCTEURS ===\n";

        // Sphère par défaut
        Sphere3D defaultSphere(Point3D(0, 0, 0), 1.0f, 3, 255, 255, 255); // Subdivisions minimales pour éviter les problèmes
        std::cout << "Sphère par défaut :\n"
                  << "  Centre : " << defaultSphere.getCenter() << "\n"
                  << "  Rayon : " << defaultSphere.getRadius() << "\n"
                  << "  Couleur : " << defaultSphere.getColor() << "\n"
                  << "  Volume : " << defaultSphere.volume() << "\n"
                  << "  Surface : " << defaultSphere.surfaceArea() << "\n";

        // Sphère avec centre, rayon, subdivisions et couleur RVB
        Sphere3D redSphere(Point3D(1, 1, 1), 3.0f, 8, 255, 0, 0); // Plus de subdivisions pour éviter l'alignement des sommets
        std::cout << "Sphère rouge :\n"
                  << "  Centre : " << redSphere.getCenter() << "\n"
                  << "  Rayon : " << redSphere.getRadius() << "\n"
                  << "  Couleur : " << redSphere.getColor() << "\n"
                  << "  Volume : " << redSphere.volume() << "\n"
                  << "  Surface : " << redSphere.surfaceArea() << "\n";

        // Sphère avec centre, couleur, rayon et subdivisions
        Sphere3D greenSphere(Point3D(0, 0, 0), Couleur(0, 255, 0), 2.0f, 6);
        std::cout << "Sphère verte :\n"
                  << "  Centre : " << greenSphere.getCenter() << "\n"
                  << "  Rayon : " << greenSphere.getRadius() << "\n"
                  << "  Couleur : " << greenSphere.getColor() << "\n"
                  << "  Volume : " << greenSphere.volume() << "\n"
                  << "  Surface : " << greenSphere.surfaceArea() << "\n";

        // === TEST DES MÉTHODES ===
        std::cout << "\n=== TEST DES MÉTHODES ===\n";

        // Modification du centre
        greenSphere.setCenter(Point3D(5, 5, 5));
        std::cout << "Nouveau centre de la sphère verte : " << greenSphere.getCenter() << "\n";

        // Modification du rayon
        greenSphere.setRadius(4.0f);
        std::cout << "Nouveau rayon de la sphère verte : " << greenSphere.getRadius() << "\n";

        // Modification de la couleur
        greenSphere.setColor(128, 0, 128);
        std::cout << "Nouvelle couleur de la sphère verte : " << greenSphere.getColor() << "\n";

        // Modification des composantes RVB
        greenSphere.setColorRouge(200);
        greenSphere.setColorVert(50);
        greenSphere.setColorBleu(25);
        std::cout << "Couleur modifiée de la sphère verte : " << greenSphere.getColor() << "\n";

        // Affichage des quadrilatères
        const auto& quads = greenSphere.getQuads();
        std::cout << "\nNombre de quadrilatères dans la sphère verte : " << quads.size() << "\n";
        for (size_t i = 0; i < quads.size(); ++i) {
            std::cout << "Quadrilatère " << i + 1 << " :\n" << quads[i] << "\n";
        }

    } catch (const std::exception& e) {
        std::cerr << "Erreur : " << e.what() << "\n";
    }

    return 0;
}
