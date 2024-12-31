#include <iostream>
#include "point3d.h"

int main() {
    // Création de points
    Point3D p1(1.0, 2.0, 3.0);
    Point3D p2(4.0, 5.0, 6.0);
    Point3D p3(7.0, 8.0, 9.0);
    Point3D p4(p3);

    // Accès aux coordonnées
    std::cout << "p1: (" << p1.getX() << ", " << p1.getY() << ", " << p1.getZ() << ")\n";
    std::cout << "p2: (" << p2.getX() << ", " << p2.getY() << ", " << p2.getZ() << ")\n";
    std::cout << "p4: (" << p4.getX() << ", " << p4.getY() << ", " << p4.getZ() << ")\n";

    // Distance entre deux points
    std::cout << "Distance entre p1 et p2: " << p1.distance(p2) << "\n";

    // Distance statique entre deux points
    std::cout << "Distance entre p1 et p3 (statique): " << Point3D::distance(p1, p3) << "\n";

    // Produit scalaire
    std::cout << "Produit scalaire p1 . p2: " << p1.dotProduct(p2) << "\n";

    // Produit vectoriel
    Point3D cross = p1.crossProduct(p2);
    std::cout << "Produit vectoriel p1 x p2: (" << cross.getX() << ", " << cross.getY() << ", " << cross.getZ() << ")\n";

    // Produit vectoriel statique
    Point3D crossStatic = Point3D::crossProduct(p1, p3);
    std::cout << "Produit vectoriel (statique) p1 x p3: (" << crossStatic.getX() << ", " << crossStatic.getY() << ", " << crossStatic.getZ() << ")\n";

    // Vérification de colinéarité
    bool collinear = Point3D::areCollinear(p1, p2, p3);
    std::cout << "Les points p1, p2, et p3 sont " << (collinear ? "colinéaires" : "non colinéaires") << ".\n";

    // Comparaison d'égalité
    bool equal = (p1 == p2);
    std::cout << "p1 et p2 sont " << (equal ? "égaux" : "différents") << ".\n";

    // Addition de points
    Point3D sum = p1 + p2;
    std::cout << "Somme p1 + p2: (" << sum.getX() << ", " << sum.getY() << ", " << sum.getZ() << ")\n";

    // Soustraction de points
    Point3D diff = p2 - p1;
    std::cout << "Différence p2 - p1: (" << diff.getX() << ", " << diff.getY() << ", " << diff.getZ() << ")\n";

    // Comparaison d'inégalité
    bool notEqual = (p1 != p3);
    std::cout << "p1 et p3 sont " << (notEqual ? "différents" : "égaux") << ".\n";

    // Utilisation de l'opérateur d'affichage
    std::cout << "Point p1: " << p1 << "\n";
    std::cout << "Point p2: " << p2 << "\n";
    std::cout << "Point p3: " << p3 << "\n";

    return 0;
}
