/**
 * @file Triangle2D.h
 * @brief Déclaration de la classe Triangle2D pour représenter un triangle dans un espace 2D.
 *
 * Cette classe représente un triangle dans un espace bidimensionnel avec trois sommets.
 */
#ifndef TRIANGLE2D_H
#define TRIANGLE2D_H

#include "point2d.h"
#include <iostream>

/**
 * @class Triangle2D
 * @brief Classe représentant un triangle dans l'espace 2D.
 *
 * La classe Triangle2D permet de stocker trois sommets d'un triangle et fournit des méthodes
 * pour calculer le périmètre, l'aire et vérifier si un point est à l'intérieur du triangle.
 */
class Triangle2D {
private:
    Point2D p1_; ///< Premier sommet du triangle.
    Point2D p2_; ///< Deuxième sommet du triangle.
    Point2D p3_; ///< Troisième sommet du triangle.

public:
    /**
     * @brief Constructeur par défaut initialisant un triangle avec des points à l'origine.
     */
    Triangle2D();

    /**
     * @brief Constructeur initialisant le triangle avec trois sommets donnés.
     * @param p1 Premier sommet du triangle.
     * @param p2 Deuxième sommet du triangle.
     * @param p3 Troisième sommet du triangle.
     * @throws std::runtime_error Si les trois points sont colinéaires.
     */
    Triangle2D(const Point2D& p1, const Point2D& p2, const Point2D& p3);

    /**
     * @brief Accesseur pour le premier sommet du triangle.
     * @return Le premier sommet du triangle.
     */
    Point2D getP1() const;

    /**
     * @brief Accesseur pour le deuxième sommet du triangle.
     * @return Le deuxième sommet du triangle.
     */
    Point2D getP2() const;

    /**
     * @brief Accesseur pour le troisième sommet du triangle.
     * @return Le troisième sommet du triangle.
     */
    Point2D getP3() const;

    /**
     * @brief Calcule le périmètre du triangle.
     * @return Le périmètre du triangle.
     */
    float perimeter() const;

    /**
     * @brief Calcule l'aire du triangle en utilisant la formule de l'aire de Heron.
     * @return L'aire du triangle.
     */
    float area() const;

    /**
     * @brief Vérifie si un point est à l'intérieur du triangle.
     * @param point Le point à vérifier.
     * @return true si le point est à l'intérieur, false sinon.
     */
    bool contains(const Point2D& point) const;

    /**
     * @brief Surcharge de l'opérateur de flux pour afficher les informations du triangle.
     * @param os Flux de sortie.
     * @param triangle Triangle à afficher.
     * @return Le flux de sortie modifié.
     */
    friend std::ostream& operator<<(std::ostream& os, const Triangle2D& triangle);
};

#endif // TRIANGLE2D_H