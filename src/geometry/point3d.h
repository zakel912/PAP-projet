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
        ~Point3D();

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

        //Définition des opérateurs externes

        /**
         * @brief Opérateur d'addition de deux points.
         * @param p1 Le premier point à ajouter.
         * @param p2 Le deuxième point à ajouter.
         * @return Le point résultant de l'addition.
         */
        friend Point3D operator+(const Point3D& p1, const Point3D& p2) {
            return Point3D(p1.x + p2.x, p1.y + p2.y, p1.z + p2.z);
        }

        /**
         * @brief Opérateur de soustraction de deux points.
         * @param p1 Le premier point à soustraire.
         * @param p2 Le deuxième point à soustraire.
         * @return Le point résultant de la soustraction.
         */
        friend Point3D operator-(const Point3D& p1, const Point3D& p2) {
            return Point3D(p1.x - p2.x, p1.y - p2.y, p1.z - p2.z);
        }
        friend std::ostream& operator<<(std::ostream& os, const Point3D& point);

}; 

#endif 