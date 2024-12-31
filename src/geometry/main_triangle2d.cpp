#include <iostream>
#include "triangle2d.h"
#include "point2d.h"
#include "../couleur.h" // Assurez-vous que Couleur est bien implémenté

int main() {
    try {
        // Création de points
        Point2D p1(0, 0);
        Point2D p2(4, 0);
        Point2D p3(2, 3);

        // Test des constructeurs
        std::cout << "=== TEST DES CONSTRUCTEURS ===" << std::endl;

        // Constructeur par défaut
        Triangle2D defaultTriangle;
        std::cout << "Triangle par défaut : " << defaultTriangle << std::endl;

        // Constructeur avec sommets et couleur RVB
        Triangle2D t1(p1, p2, p3, 255, 0, 0, 10.0f);
        std::cout << "Triangle t1 (avec couleur RVB) : " << t1 << std::endl;

        // Constructeur avec sommets et objet Couleur
        Couleur green(0, 255, 0);
        Triangle2D t2(p1, p2, p3, green, 5.0f);
        std::cout << "Triangle t2 (avec objet Couleur) : " << t2 << std::endl;

        // Test des méthodes
        std::cout << "\n=== TEST DES METHODES ===" << std::endl;

        // Accesseurs pour les sommets
        std::cout << "Sommet p1 de t1 : " << t1.getP1() << std::endl;
        std::cout << "Sommet p2 de t1 : " << t1.getP2() << std::endl;
        std::cout << "Sommet p3 de t1 : " << t1.getP3() << std::endl;

        // Accesseurs et mutateurs pour la couleur
        std::cout << "Couleur de t1 : " << t1.getColor() << std::endl;
        t1.setColor(0, 0, 255);
        std::cout << "Couleur modifiée de t1 : " << t1.getColor() << std::endl;

        // Accesseurs et mutateurs pour la profondeur
        std::cout << "Profondeur de t1 : " << t1.getDepth() << std::endl;
        t1.setDepth(15.0f);
        std::cout << "Profondeur modifiée de t1 : " << t1.getDepth() << std::endl;

        // Calcul du périmètre
        std::cout << "Périmètre de t1 : " << t1.perimeter() << std::endl;

        // Calcul de l'aire
        std::cout << "Aire de t1 : " << t1.area() << std::endl;

        // Calcul de la profondeur moyenne
        std::cout << "Profondeur moyenne de t1 : " << t1.averageDepth() << std::endl;

        // Test de contains
        Point2D testPoint1(2, 1); // À l'intérieur
        Point2D testPoint2(5, 5); // À l'extérieur

        std::cout << "t1 contient le point (2,1) : " << (t1.contains(testPoint1) ? "Oui" : "Non") << std::endl;
        std::cout << "t1 contient le point (5,5) : " << (t1.contains(testPoint2) ? "Oui" : "Non") << std::endl;

    } catch (const std::runtime_error& e) {
        std::cerr << "Erreur : " << e.what() << std::endl;
    }

    return 0;
}