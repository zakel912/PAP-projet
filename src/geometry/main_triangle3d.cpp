#include <iostream>
#include "triangle3d.h"
#include "point3d.h"
#include "../couleur.h"

int main() {
    try {
        // Création de points 3D
        Point3D p1(0, 0, 0);
        Point3D p2(4, 0, 0);
        Point3D p3(0, 3, 0);

        // === TEST DES CONSTRUCTEURS ===
        std::cout << "=== TEST DES CONSTRUCTEURS ===" << std::endl;

        // Constructeur par défaut
        Triangle3D defaultTriangle;
        std::cout << "Triangle par défaut : " << defaultTriangle << std::endl;

        // Constructeur avec couleur RVB
        Triangle3D t1(p1, p2, p3, 255, 0, 0);
        std::cout << "Triangle t1 (avec couleur RVB) : " << t1 << std::endl;

        // Constructeur avec objet Couleur
        Couleur blue(0, 0, 255);
        Triangle3D t2(p1, p2, p3, blue);
        std::cout << "Triangle t2 (avec objet Couleur) : " << t2 << std::endl;

        // Constructeur par copie
        Triangle3D t3(t1);
        std::cout << "Triangle t3 (copie de t1) : " << t3 << std::endl;

        // === TEST DES MÉTHODES ===
        std::cout << "\n=== TEST DES MÉTHODES ===" << std::endl;

        // Accesseurs pour les sommets
        std::cout << "Sommet p1 de t1 : " << t1.getP1() << std::endl;
        std::cout << "Sommet p2 de t1 : " << t1.getP2() << std::endl;
        std::cout << "Sommet p3 de t1 : " << t1.getP3() << std::endl;

        // Accesseurs et mutateurs pour la couleur
        std::cout << "Couleur de t1 : " << t1.getColor() << std::endl;
        t1.setColor(0, 255, 0);
        std::cout << "Couleur modifiée de t1 : " << t1.getColor() << std::endl;

        // Vérification des composantes de couleur
        t1.setColorRouge(128);
        std::cout << "Rouge modifié de t1 : " << t1.getColor() << std::endl;

        // Calculs géométriques
        std::cout << "Périmètre de t1 : " << t1.perimeter() << std::endl;
        std::cout << "Aire de t1 : " << t1.area() << std::endl;

        // Méthode isVertex
        std::cout << "Le point p1 est un sommet de t1 : " << (t1.isVertex(p1) ? "Oui" : "Non") << std::endl;
        Point3D p4(1, 1, 1);
        std::cout << "Le point p4 est un sommet de t1 : " << (t1.isVertex(p4) ? "Oui" : "Non") << std::endl;

        // Méthode isDegenerate
        std::cout << "Le triangle t1 est dégénéré : " << (t1.isDegenerate() ? "Oui" : "Non") << std::endl;

        // Méthode hasCommonSide
        Triangle3D t4(Point3D(0, 0, 0), Point3D(4, 0, 0), Point3D(2, -3, 0), Couleur(128, 128, 128));
        std::cout << "t1 et t4 ont un côté en commun : " << (t1.hasCommonSide(t4) ? "Oui" : "Non") << std::endl;

        // Méthode equals
        std::cout << "t1 et t3 sont égaux : " << (t1.equals(t3) ? "Oui" : "Non") << std::endl;

        // Test de l'œil pour le rendu
        Triangle3D::setEyePosition(Point3D(1, 1, 1));
        std::cout << "Position de l'œil : " << Triangle3D::getEyePosition() << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Erreur : " << e.what() << std::endl;
    }

    return 0;
}