/**
 * @file Triangle3D.h
 * @brief Déclaration de la classe Triangle3D pour représenter un triangle dans l'espace 3D.
 *
 * Cette classe représente un triangle dans l'espace tridimensionnel, défini par trois points.
 */
#ifndef TRIANGLE3D_H
#define TRIANGLE3D_H

#include "point3d.h"
#include "../couleur.h"
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
        Point3D p1; // Premier sommet du triangle.
        Point3D p2; // Deuxième sommet du triangle.
        Point3D p3; // Troisième sommet du triangle.
        Couleur color; //couleur du triangle

        static Point3D eyePosition; //position de l'oeil pour le rendu 3D
        
    public:

        /**
        * @brief Constructeur par défaut de la classe Triangle3D.
        */
        Triangle3D();

        /**
         * @brief Constructeur initialisant le triangle avec trois points donnés et une couleur spécifique.
         * @param p1 Premier sommet du triangle.
         * @param p2 Deuxième sommet du triangle.
         * @param p3 Troisième sommet du triangle.
         * @param rouge La composante rouge de la couleur du triangle.
         * @param vert La composante verte de la couleur du triangle.
         * @param bleu La composante bleue de la couleur du triangle.
         * @pre Les trois sommets ne doivent pas être alignés.
         */
        Triangle3D(const Point3D& p1, const Point3D& p2, const Point3D& p3, int rouge =0, int vert=0, int bleu =0);

        /**
         * @brief Constructeur initialisant le triangle avec des valeurs spécifiques pour les trois sommets dans l'ordre
         * trigonométrique et une couleur spécifique.
         * @param p1 Premier sommet du triangle.
         * @param p2 Deuxième sommet du triangle.
         * @param p3 Troisième sommet du triangle.
         * @param color La couleur du triangle.
         * @pre Les trois sommets ne doivent pas être alignés.
         */
        Triangle3D(const Point3D& p1, const Point3D& p2, const Point3D& p3, const Couleur& color);

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
         * @brief Accesseur pour la couleur du triangle.
         * @return La couleur du triangle.
         */
        Couleur getColor() const{return color;}

        /**
         * @brief Modifie la couleur du triangle.
         * @param color La nouvelle couleur du triangle.
         * @return void
         */
        void setColor(const Couleur& color){this->color = color;}

        /**
         * @brief Modifie la couleur du triangle.
         * @param rouge La composante rouge de la couleur du triangle.
         * @param vert La composante verte de la couleur du triangle.
         * @param bleu La composante bleue de la couleur du triangle.
         * @return void
         */
        void setColor(int rouge, int vert, int bleu){
            color.setRouge(rouge); color.setVert(vert); color.setBleu(bleu);
        }

        /**
         * @brief Modifie la Composante rouge de la couleur du triangle.
         * @param rouge La nouvelle composante rouge de la couleur du triangle.
         * @return void
         */
        void setColorRouge(int rouge){color.setRouge(rouge);}

        /**
         * @brief Modifie la Composante verte de la couleur du triangle.
         * @param vert La nouvelle composante verte de la couleur du triangle.
         * @return void
         */
        void setColorVert(int vert){color.setVert(vert);}

        /**
         * @brief Modifie la Composante bleue de la couleur du triangle.
         * @param bleu La nouvelle composante bleue de la couleur du triangle.
         * @return void
         */
        void setColorBleu(int bleu){color.setBleu(bleu);}

        /**
         * @brief Accesseur pour la position de l'oeil pour le rendu 3D.
         * @return La position de l'oeil pour le rendu 3D.
         */
        static Point3D getEyePosition(){return eyePosition;}

        /**
         * @brief Modifie la position de l'oeil pour le rendu 3D.
         * @param eyePosition La nouvelle position de l'oeil pour le rendu 3D.
         * @return void
         */
        static void setEyePosition(const Point3D& eyePosition){Triangle3D::eyePosition = eyePosition;}

        /**
         * @brief Méthode pour orienter les sommets dans le sens trigonométrique.
         * @return void
         */
        void orient();


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

