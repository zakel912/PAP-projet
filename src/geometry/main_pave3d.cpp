#include "pave3d.h"
#include "quad3d.h"
#include "point3d.h"
#include "../couleur.h"
#include <iostream>

int main() {
    try {
        // === TEST DES CONSTRUCTEURS ===
        std::cout << "=== TEST DES CONSTRUCTEURS ===\n";

        // Pavé par défaut
        Pave3D defaultPave;
        std::cout << "Pavé par défaut :\n" << defaultPave << "\n";

        // Définir les faces d'un pavé
        Quad3D front(Point3D(0, 0, 0), Point3D(4, 0, 0), Point3D(4, 3, 0), Point3D(0, 3, 0), Couleur(255, 0, 0));
        Quad3D back(Point3D(0, 0, -2), Point3D(4, 0, -2), Point3D(4, 3, -2), Point3D(0, 3, -2), Couleur(255, 0, 0));
        Quad3D left(Point3D(0, 0, 0), Point3D(0, 3, 0), Point3D(0, 3, -2), Point3D(0, 0, -2), Couleur(0, 255, 0));
        Quad3D right(Point3D(4, 0, 0), Point3D(4, 3, 0), Point3D(4, 3, -2), Point3D(4, 0, -2), Couleur(0, 255, 0));
        Quad3D top(Point3D(0, 3, 0), Point3D(4, 3, 0), Point3D(4, 3, -2), Point3D(0, 3, -2), Couleur(0, 0, 255));
        Quad3D bottom(Point3D(0, 0, 0), Point3D(4, 0, 0), Point3D(4, 0, -2), Point3D(0, 0, -2), Couleur(0, 0, 255));

        Pave3D redPave(front, back, left, right, top, bottom, Couleur(255, 0, 0));

        // Pavé avec faces définies
        Pave3D bluePave(front, back, left, right, top, bottom, Couleur(0, 0, 255));
        std::cout << "Pavé bleu :\n" << bluePave << "\n";

        // Pavé par copie
        Pave3D copyPave(bluePave);
        std::cout << "Copie du pavé bleu :\n" << copyPave << "\n";

        // === TEST DES MÉTHODES ===
        std::cout << "\n=== TEST DES MÉTHODES ===\n";

        // Surface totale
        std::cout << "Surface totale du pavé bleu : " << bluePave.surfaceArea() << "\n";

        // Volume
        std::cout << "Volume du pavé bleu : " << bluePave.volume() << "\n";

        // Modification de la couleur
        bluePave.setColor(128, 128, 0);
        std::cout << "Nouvelle couleur du pavé bleu : " << bluePave.getColor() << "\n";

        // Modification des faces
        Quad3D newFront(Point3D(1, 1, 0), Point3D(4, 1, 0), Point3D(4, 3, 0), Point3D(1, 3, 0), Couleur(128, 128, 128));
        bluePave = Pave3D(newFront, back, left, right, top, bottom, Couleur(128, 128, 128));
        std::cout << "Pavé modifié :\n" << bluePave << "\n";

        // Test d'égalité
        bool areEqual = bluePave.equals(copyPave);
        std::cout << "Les pavés sont-ils égaux ? " << (areEqual ? "Oui" : "Non") << "\n";

    } catch (const std::exception& e) {
        std::cerr << "Erreur : " << e.what() << "\n";
    }

    return 0;
}