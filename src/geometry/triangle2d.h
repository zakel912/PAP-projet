/**
 * @file Triangle2D.h
 * @brief Déclaration de la classe Triangle2D pour représenter un triangle dans un espace 2D.
 *
 * Cette classe représente un triangle dans un espace bidimensionnel avec trois sommets
 * et une couleur associée.
 */

#ifndef TRIANGLE2D_H
#define TRIANGLE2D_H

#include "point2d.h"
#include "../couleur.h"
#include <iostream>

/**
 * @class Triangle2D
 * @brief Classe représentant un triangle dans l'espace 2D.
 *
 * La classe Triangle2D permet de stocker trois sommets d'un triangle et fournit des méthodes
 * pour calculer le périmètre, l'aire, vérifier si un point est à l'intérieur du triangle,
 * gérer sa couleur, et calculer sa profondeur moyenne.
 */
class Triangle2D {
private:
    Point2D p1; // Premier sommet du triangle.
    Point2D p2; // Deuxième sommet du triangle.
    Point2D p3; // Troisième sommet du triangle.
    Couleur color; // Couleur du triangle.
    float depth; // Profondeur associée au triangle (par exemple pour le rendu).

public:
    /**
     * @brief Constructeur par défaut initialisant un triangle avec des points à l'origine, une couleur par défaut et une profondeur nulle.
     */
    Triangle2D();

    /**
     * @brief Constructeur initialisant le triangle avec trois sommets donnés, une couleur RVB et une profondeur.
     * @param p1 Premier sommet du triangle.
     * @param p2 Deuxième sommet du triangle.
     * @param p3 Troisième sommet du triangle.
     * @param rouge Composante rouge de la couleur.
     * @param vert Composante verte de la couleur.
     * @param bleu Composante bleue de la couleur.
     * @param depth Profondeur du triangle.
     * @throws std::runtime_error Si les trois points sont colinéaires.
     */
    Triangle2D(const Point2D& p1, const Point2D& p2, const Point2D& p3, int rouge = 0, int vert = 0, int bleu = 0, float depth=0.0f);

    /**
     * @brief Constructeur initialisant le triangle avec trois sommets donnés, une couleur et une profondeur.
     * @param p1 Premier sommet du triangle.
     * @param p2 Deuxième sommet du triangle.
     * @param p3 Troisième sommet du triangle.
     * @param color Couleur du triangle.
     * @param depth Profondeur du triangle.
     * @throws std::runtime_error Si les trois points sont colinéaires.
     */
    Triangle2D(const Point2D& p1, const Point2D& p2, const Point2D& p3, const Couleur& color, float depth=0.0f);

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
     * @brief Accesseur pour la couleur du triangle.
     * @return La couleur du triangle.
     */
    Couleur getColor() const;

    /**
     * @brief Modifie la couleur du triangle.
     * @param color Nouvelle couleur du triangle.
     */
    void setColor(const Couleur& color);

    /**
     * @brief Modifie la couleur du triangle.
     * @param rouge Composante rouge de la couleur.
     * @param vert Composante verte de la couleur.
     * @param bleu Composante bleue de la couleur.
     */
    void setColor(int rouge, int vert, int bleu);

    /**
     * @brief Accesseur pour la profondeur du triangle.
     * @return La profondeur du triangle.
     */
    float getDepth() const{
        return depth;
    }

    /**
     * @brief Modifie la profondeur du triangle.
     * @param depth Nouvelle profondeur du triangle.
     */
    void setDepth(float newDepth){
        depth = newDepth;
    }

    /**
     * @brief Calcule le périmètre du triangle.
     * @return Le périmètre du triangle.
     */
    float perimeter() const;

    /**
     * @brief Calcule l'aire du triangle en utilisant la formule de Héron.
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