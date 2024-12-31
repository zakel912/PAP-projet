/**
 * @file Point2D.h
 * @brief Déclaration de la classe Point2D pour représenter un point dans l'espace 2D.
 *
 * Cette classe représente un point dans l'espace bidimensionnel avec des coordonnées x et y.
 */
#ifndef POINT2D_H
#define POINT2D_H

#include <iostream>
#include <cmath>
#include <stdexcept>

/**
 * @class Point2D
 * @brief Classe représentant un point dans l'espace 2D.
 *
 * La classe Point2D permet de stocker les coordonnées d'un point en deux dimensions
 * et fournit des méthodes pour calculer la distance entre deux points.
 */
class Point2D {
    private:
        int x; ///< Coordonnée x du point.
        int y; ///< Coordonnée y du point.

    public:
        /**
         * @brief Constructeur initialisant le point avec des valeurs spécifiques pour x et y.
         * @param x Coordonnée x du point.
         * @param y Coordonnée y du point.
         */
        Point2D(int x = 0, int y = 0);

        /**
         * @brief Constructeur initialisant le point avec des valeurs spécifiques pour x et y.
         * @param x Coordonnée x du point.
         * @param y Coordonnée y du point.
         */
        Point2D(float x = 0, float y = 0);
        
        /**
         * @brief Constructeur par copie de la classe Point2D.
         * @param other Le point à copier.
         */
        Point2D(const Point2D& other);

        /**
         * @brief Destructeur de la classe Point2D.
         */
        ~Point2D(){}

        /**
         * @brief Accesseur pour la coordonnée x.
         * @return La coordonnée x du point.
         */
        int getX() const;

        /**
         * @brief Accesseur pour la coordonnée y.
         * @return La coordonnée y du point.
         */
        int getY() const;

        void setX(int newX) { x = newX; }
        void setY(int newY) { y = newY; }

        /**
         * @brief Calcule la distance (euclidienne) entre ce point et un autre point donné.
         * @param other L'autre point avec lequel calculer la distance.
         * @return La distance entre ce point et l'autre point.
         */
        float distance(const Point2D& other) const;

        /**
         * @brief Calcule la distance (euclidienne) entre deux points donnés.
         * @param p1 Le premier point.
         * @param p2 Le deuxième point.
         * @return La distance entre les deux points.
         */
        static float distance(const Point2D& p1, const Point2D& p2);

        /**
         * @brief Vérifie si trois points sont colinéaires.
         * @param p1 Premier point.
         * @param p2 Deuxième point.
         * @param p3 Troisième point.
         * @return true si les trois points sont colinéaires, false sinon.
         */
        static bool areCollinear(const Point2D& p1, const Point2D& p2, const Point2D& p3);

        /**
         * @brief Opérateur d'addition de deux points.
         * @param other L'autre point à ajouter.
         * @return Le point résultant de l'addition.
         */
        Point2D operator+(const Point2D& other) const {
            return Point2D(x + other.x, y + other.y);
        };

        /**
         * @brief Opérateur de soustraction de deux points.
         * @param other L'autre point à soustraire.
         * @return Le point résultant de la soustraction.
         */
        Point2D operator-(const Point2D& other) const {
            return Point2D(x - other.x, y - other.y);
        };

        /**
         * @brief Compare deux points pour l'égalité.
         * @param other L'autre point à comparer.
         * @return true si les deux points sont égaux, false sinon.
         */
        bool operator==(const Point2D& other) const {
            return x == other.x && y == other.y;
        };

        /**
         * @brief Compare deux points pour l'inégalité.
         * @param other L'autre point à comparer.
         */
        bool operator!=(const Point2D& other) const {
            return !(*this == other);
        };

        friend std::ostream& operator<<(std::ostream& os, const Point2D& point);
};

#endif
