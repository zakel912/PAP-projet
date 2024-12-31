#include <iostream>
#include "point2d.h"

int main() {
    // Création de points
    Point2D p1(1, 2);
    Point2D p2(3, 4);
    Point2D p3(1, 2);
    Point2D p4(p3);

    // Affichage des coordonnées
    std::cout << "Point p1: " << p1 << std::endl;
    std::cout << "Point p2: " << p2 << std::endl;

    // Test des opérateurs ==
    if (p1 == p3) {
        std::cout << "p1 et p3 sont égaux." << std::endl;
    }

    // Test des opérateurs !=
    if (p1 != p2) {
        std::cout << "p1 et p2 sont différents." << std::endl;
    }

    // Calcul de la distance entre deux points
    std::cout << "Distance entre p1 et p2: " << p1.distance(p2) << std::endl;

    // Distance statique entre deux points
    std::cout << "Distance (statique) entre p2 et p3: " << Point2D::distance(p2, p3) << std::endl;

    // Test de l'opérateur +
    Point2D sum = p1 + p2;
    std::cout << "Somme de p1 et p2: " << sum << std::endl;

    // Test de l'opérateur -
    Point2D diff = p2 - p1;
    std::cout << "Différence de p2 et p1: " << diff << std::endl;

    return 0;
}