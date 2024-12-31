#include <iostream>
#include "quad3d.h"
#include "point3d.h"
#include "triangle3d.h"
#include "../couleur.h"

int main() {
    try {
        // === Création de points 3D ===
        Point3D p1(0, 0, 0);
        Point3D p2(4, 0, 0);
        Point3D p3(4, 3, 0);
        Point3D p4(0, 3, 0);

        // === TEST DES CONSTRUCTEURS ===
        std::cout << "=== TEST DES CONSTRUCTEURS ===" << std::endl;

        // Constructeur par défaut
        Quad3D defaultQuad;
        std::cout << "Quadrilatère par défaut : " << defaultQuad << std::endl;

        // Constructeur avec deux triangles
        Triangle3D t1(p1, p2, p3, 255, 0, 0);
        Triangle3D t2(p1, p3, p4, 255, 0, 0);
        Quad3D quad1(t1, t2, 255, 0, 0);
        std::cout << "Quadrilatère quad1 (avec deux triangles) : " << quad1 << std::endl;

        // Constructeur avec quatre points
        Quad3D quad2(p1, p2, p3, p4, 0, 255, 0);
        std::cout << "Quadrilatère quad2 (avec quatre points) : " << quad2 << std::endl;

        // Constructeur avec couleur via `Couleur`
        Couleur blue(0, 0, 255);
        Quad3D quad3(p1, p2, p3, p4, blue);
        std::cout << "Quadrilatère quad3 (avec couleur Couleur) : " << quad3 << std::endl;

        // === TEST DES MÉTHODES ===
        std::cout << "\n=== TEST DES MÉTHODES ===" << std::endl;

        // Test des accesseurs
        std::cout << "Premier triangle de quad1 : " << quad1.getFirstTriangle() << std::endl;
        std::cout << "Deuxième triangle de quad1 : " << quad1.getSecondTriangle() << std::endl;

        // Couleur et modification
        std::cout << "Couleur initiale de quad1 : " << quad1.getColor() << std::endl;
        quad1.setColor(128, 128, 0);
        std::cout << "Couleur modifiée de quad1 : " << quad1.getColor() << std::endl;
        quad1.setColorBleu(255);
        std::cout << "Bleu modifié de quad1 : " << quad1.getColor() << std::endl;

        // Surface totale
        std::cout << "Surface de quad1 : " << quad1.surface() << std::endl;

        // Vérifications des sommets
        std::cout << "p1 est un sommet de quad1 : " << (quad1.isVertex(p1) ? "Oui" : "Non") << std::endl;
        Point3D p5(5, 5, 5);
        std::cout << "p5 est un sommet de quad1 : " << (quad1.isVertex(p5) ? "Oui" : "Non") << std::endl;

        // Comparaisons entre quadrilatères
        std::cout << "quad1 et quad2 ont un côté en commun : " << (quad1.hasCommonSide(quad2) ? "Oui" : "Non") << std::endl;
        std::cout << "quad1 et quad2 ont la même surface : " << (quad1.sameSurface(quad2) ? "Oui" : "Non") << std::endl;

        // Égalité entre quadrilatères
        Quad3D quad4 = quad1; // Constructeur par copie
        std::cout << "quad1 et quad4 sont égaux : " << (quad1 == quad4 ? "Oui" : "Non") << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Erreur : " << e.what() << std::endl;
    }

    return 0;
}