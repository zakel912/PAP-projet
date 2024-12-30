/**
 * @file Triangle3D.h
 * @brief Déclaration de la classe Triangle3D pour représenter un triangle dans l'espace 3D.
 *
 * Cette classe représente un triangle dans l'espace tridimensionnel, défini par trois points.
 */
#ifndef TRIANGLE3D_H
#define TRIANGLE3D_H

#include "point3d.h"
#include <iostream>
#include <cmath>
#include <stdexcept>

/**
 * @class Triangle3D
 * @brief Classe représentant un triangle dans l'espace 3D.
 *
 * La classe Triangle3D permet de manipuler les triangles en trois dimensions.
 */
class Triangle3D {

    private:
        Point3D p1; ///< Premier sommet du triangle.
        Point3D p2; ///< Deuxième sommet du triangle.
        Point3D p3; ///< Troisième sommet du triangle.

    public:

        Triangle3D();

        /**
         * @brief Constructeur initialisant le triangle avec trois points donnés.
         * @param p1 Premier sommet du triangle.
         * @param p2 Deuxième sommet du triangle.
         * @param p3 Troisième sommet du triangle.
         */
        Triangle3D(const Point3D& p1, const Point3D& p2, const Point3D& p3);

        /**
         * @brief Constructeur par copie de la classe Triangle3D.
         * @param other Le triangle à copier.
         */
        Triangle3D(const Triangle3D& other);

        /**
         * @brief Destructeur de la classe Triangle3D.
         */
        ~Triangle3D();

        /**
         * @brief Accesseur pour le premier sommet.
         * @return Le premier sommet du triangle.
         */
        const Point3D& getP1() const;

        /**
         * @brief Accesseur pour le deuxième sommet.
         * @return Le deuxième sommet du triangle.
         */
        const Point3D& getP2() const;

        /**
         * @brief Accesseur pour le troisième sommet.
         * @return Le troisième sommet du triangle.
         */
        const Point3D& getP3() const;

        /**
         * @brief Calcul du périmètre du triangle.
         * @return Le périmètre du triangle.
         */
        float perimeter() const;

        /**
         * @brief Calcule l'aire du triangle en utilisant la formule de Héron.
         * @return L'aire du triangle.
         */
        float area() const;

        /**
         * @brief vérifie si un point fait partie des sommets du triangle
         * @param p le point à vérifier
         * @return true si le point est un sommet du triangle, false sinon
         */
        bool isVertex(const Point3D& p) const;

        /**
         * @brief Détermine si le triangle est dégénéré (aire nulle).
         * @return true si le triangle est dégénéré, false sinon.
         */
        bool isDegenerate() const;

    /**
     * @brief Vérifie si deux triangles ont un côté en commun.
     * @param other L'autre triangle à comparer.
     * @return true si les deux triangles ont un côté en commun, false sinon.
     */
    bool hasCommonSide(const Triangle3D& other) const;

    /**
     * @brief Vérifie si deux triangles ont un côté en commun.
     * @param t1 Le premier triangle.
     * @param t2 Le deuxième triangle.
     * @return true si les deux triangles ont un côté en commun, false sinon.
     */
    static bool hasCommonSide(const Triangle3D& t1, const Triangle3D& t2);

        /**
     * @brief Compare deux triangles pour l'égalité.
     * @param other L'autre triangle avec lequel comparer.
     * @return true si les deux triangles sont égaux, false sinon.
     */
    bool equals(const Triangle3D& other) const;

    friend std::ostream& operator<<(std::ostream& os, const Triangle3D& triangle);


};

//bool operator==(const triangle3D& t1, const triangle3D& t2);

#endif

