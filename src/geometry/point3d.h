/**
 * @file Point3D.h
 * @brief Déclaration de la classe Point3D pour représenter un point dans l'espace 3D.
 * 
 * Cette classe représente un point dans l'espace tridimensionnel avec des coordonnées x, y et z.
 */
#ifndef POINT3D_H
#define POINT3D_H

#include <iostream>
#include <cmath>
#include <stdexcept>
#include "geometry_utils.h"

/**
 * @class Point3D
 * @brief Classe représentant un point dans l'espace 3D.
 * 
 * La classe Point3D permet de stocker les coordonnées d'un point en trois dimensions
 * et fournit des méthodes pour calculer la distance entre deux points.
 */
class Point3D {

    private:
        float x;
        float y;
        float z;

    public:
        /**
        * @brief Constructeur initialisant le point avec des valeurs spécifiques pour x, y et z.
        * @param x Coordonnée x du point.
        * @param y Coordonnée y du point.
        * @param z Coordonnée z du point.
        */
        Point3D(float x = 0, float y = 0, float z = 0);

        /**
         * @brief Constructeur par copie de la classe Point3D.
         * @param other Le point à copier.
         */
        Point3D(const Point3D& other);

        /**
         * @brief Destructeur de la classe Point3D.
         */
        ~Point3D(){};

        /**
        * @brief Accesseur pour la coordonnée x.
        * @return La coordonnée x du point.
        */
        float getX() const;

        /**
        * @brief Accesseur pour la coordonnée y.
        * @return La coordonnée y du point.
        */
        float getY() const;

        /**
        * @brief Accesseur pour la coordonnée z.
        * @return La coordonnée z du point.
        */
        float getZ() const;

        /**
         * @brief Modifie la coordonnée x.
         * @param newX La nouvelle valeur pour la coordonnée x.
         */
        void setX(float newX) {
            x = newX;
        }

        /**
         * @brief Modifie la coordonnée y.
         * @param newY La nouvelle valeur pour la coordonnée y.
         */
        void setY(float newY) {
            y = newY;
        }

        /**
         * @brief Modifie la coordonnée z.
         * @param newZ La nouvelle valeur pour la coordonnée z.
         */
        void setZ(float newZ) {
            z = newZ;
        }

        /**
         * @brief Calcule la distance (euclidienne) entre ce point et un autre point donné.
         * @param other L'autre point avec lequel calculer la distance.
         * @return La distance entre ce point et l'autre point.
         */
        float distance(const Point3D& other) const;

        /**
         * @brief Calcule la distance (euclidienne) entre deux points donnés.
         * @param p1 Le premier point.
         * @param p2 Le deuxième point.
         * @return La distance entre les deux points.
         */
        static float distance(const Point3D& p1, const Point3D& p2);

        /**
         * @brief Calcule le produit vectoriel entre deux points.
         * @param other L'autre point avec lequel calculer le produit vectoriel.
         * @return Le produit vectoriel entre les deux points.
         */
        Point3D crossProduct(const Point3D& other) const;

        /**
         * @brief Calcule le produit vectoriel entre deux points.
         * @param p1 Le premier point.
         * @param p2 Le deuxième point.
         * @return Le produit vectoriel entre les deux points.
         */
        static Point3D crossProduct(const Point3D& p1, const Point3D& p2);

        /**
         * @brief Calcule le produit scalaire entre deux points.
         * @param other L'autre point avec lequel calculer le produit scalaire.
         * @return Le produit scalaire entre les deux points.
         */
        float dotProduct(const Point3D& other) const;

        /**
         * @brief Calcule la norme du vecteur représenté par le point.
         * @return La norme du vecteur.
         */
        float norm() const {
            return std::sqrt(x * x + y * y + z * z);
        }

        /**
         * @brief Vérifie si trois points sont alingnés.
         * @param p1 Le premier point.
         * @param p2 Le deuxième point.
         * @param p3 Le troisième point.
         * @return true si les trois points sont colinéaires, false sinon.
         */
        static bool areCollinear(const Point3D& p1, const Point3D& p2, const Point3D& p3);

        /**
         * @brief Compare deux points pour l'égalité.
         * @param other L'autre point à comparer.
         * @return true si les deux points sont égaux, false sinon.
         */
        bool equals(const Point3D& other) const;

        /**
         * @brief Affecte les coordonnées d'un autre point à ce point.
         * @param other Le point à copier.
         * @return Une référence à ce point modifié.
         */
        Point3D& operator=(const Point3D& other){
            x = other.getX();
            y = other.getY();
            z = other.getZ();
            return *this;
        }

        /**
         * @brief Compare deux points pour l'égalité.
         * @param p1 Le premier point à comparer.
         * @param p2 Le deuxième point à comparer.
         * @return true si les deux points sont égaux, false sinon.
         */
        friend bool operator==(const Point3D& p1, const Point3D& p2);

        /**
         * @brief Compare deux points pour l'inégalité.
         * @param p1 Le premier point à comparer.
         * @param p2 Le deuxième point à comparer.
         */
        friend bool operator!=(const Point3D& p1, const Point3D& p2);

        /**
         * @brief Opérateur de soustraction de deux points.
         * @param p1 Le premier point à soustraire.
         * @param p2 Le deuxième point à soustraire.
         * @return Le point résultant de la soustraction.
         */
        friend Point3D operator-(const Point3D& p1, const Point3D& p2) {
            return Point3D(p1.x - p2.x, p1.y - p2.y, p1.z - p2.z);
        }

        Point3D operator+(const Point3D& other) const {
            return Point3D(x + other.x, y + other.y, z + other.z);
        }

        /**
         * @brief Opérateur de multiplication d'un point par un scalaire.
         * @param p Le point à multiplier.
         * @param scalar Le scalaire par lequel multiplier le point.
         * @return Le point résultant de la multiplication.
         */
        friend Point3D operator*(const Point3D& p, float scalar) {
            return Point3D(p.x * scalar, p.y * scalar, p.z * scalar);
        }

        /**
         * @brief Opérateur de division d'un point par un scalaire.
         * @param p Le point à diviser.
         * @param scalar Le scalaire par lequel diviser le point.
         * @return Le point résultant de la division.
         */
        friend Point3D operator/(const Point3D& p, float scalar) {
            if (scalar == 0) {
                throw std::invalid_argument("Division par zéro.");
            }
            return p * (1.0f / scalar);
        }

        /**
         * @brief Normalise le vecteur représenté par le point.
         * @return Un point normalisé (longueur égale à 1).
         */
        Point3D normalize() const ;


        friend std::ostream& operator<<(std::ostream& os, const Point3D& point);

}; 

#endif 