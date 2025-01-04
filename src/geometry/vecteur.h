/**
 * @file vecteur.h
 * 
 * @brief Déclaration de la classe Vecteur pour représenter un vecteur dans l'espace 3D.
 * 
 * Cette classe représente un vecteur dans l'espace tridimensionnel avec des coordonnées x, y et z.
 */

#ifndef VECTEUR_H
#define VECTEUR_H

#include "point3d.h"
#include <iostream>
#include <cmath>
#include "triangle3d.h"
#include "quad3d.h"

/**
 * @class Vecteur
 * @brief Classe représentant un vecteur dans l'espace 3D.
 * 
 * La classe Vecteur permet de stocker les coordonnées d'un vecteur en trois dimensions
 * et fournit des méthodes pour effectuer des opérations vectorielles.
 */
class Vecteur {

    private:
        Point3D origine; ///< Point d'origine du vecteur.
        Point3D extremite; ///< Point d'extrémité du vecteur.

    public:
        /**
         * @brief Constructeur initialisant le vecteur avec des valeurs spécifiques pour ses points d'origine et d'extrémité.
         * @param origine Point d'origine du vecteur.
         * @param extremite Point d'extrémité du vecteur.
         */
        Vecteur(const Point3D& origine = Point3D(), const Point3D& extremite = Point3D(0,0,1));

        /**
         * @brief Constructeur par copie de la classe Vecteur.
         * @param other Le vecteur à copier.
         */
        Vecteur(const Vecteur& other);

        /**
         * @brief Destructeur de la classe Vecteur.
         */
        ~Vecteur(){};

        /**
         * @brief Accesseur pour le point d'origine du vecteur.
         * @return Le point d'origine du vecteur.
         */
        Point3D getOrigine() const{ return origine; }

        /**
         * @brief Accesseur pour le point d'extrémité du vecteur.
         * @return Le point d'extrémité du vecteur.
         */
        Point3D getExtremite() const { return extremite; }

        /**
         * @brief Calcule la norme du vecteur.
         * @return La norme du vecteur.
         */
        float norm() const;

        /**
         * @brief Calcule le produit scalaire entre deux vecteurs.
         * @param other L'autre vecteur avec lequel calculer le produit scalaire.
         * @return Le produit scalaire entre les deux vecteurs.
         */
        float dotProduct(const Vecteur& other) const;

        /**
         * @brief Calcule le produit scalaire entre deux vecteurs.
         * @param v1 Le premier vecteur.
         * @param v2 Le deuxième vecteur.
         * @return Le produit scalaire entre les deux vecteurs.
         */
        static float dotProduct(const Vecteur& v1, const Vecteur& v2){
            return v1.dotProduct(v2);
        }

        /**
         * @brief Calcule la distance entre un point et le plan normal au vecteur passant par l'origine.
         * @param point Le point pour lequel calculer la distance.
         * @return La distance entre le point et le plan.
         */
        float distanceToPlane(const Point3D& point) const;

        /**
         * @brief Calcule la distance entre un triangle et le plan normal au vecteur passant par l'origine.
         * @param triangle Le triangle pour lequel calculer la distance.
         * @return La distance entre le triangle et le plan.
         */
        float distanceToPlane(const Triangle3D& triangle) const{
            return std::min({distanceToPlane(triangle.getP1()), distanceToPlane(triangle.getP2()), distanceToPlane(triangle.getP3())});
        }

        /**
         * @brief Calcule ma distance entre un quads et le plan normal au vecteur passant par l'origine.
         * @param quad Le quadrilatère pour lequel calculer la distance.
         * @return La distance entre le quadrilatère et le plan.
         */
        float distanceToPlane(const Quad3D& quad) const{
            return std::min({distanceToPlane(quad.getTriangle1()), distanceToPlane(quad.getTriangle2())}); }

        /**
         * @brief Calcule la distance entre un pavé et le plan normal au vecteur passant par l'origine.
         * @param pave Le pavé pour lequel calculer la distance.
         * @return La distance entre le pavé et le plan.
         */
        float distanceToPlane(const Pave3D& pave) const;


        /**
         * @brief Vérifi si le point est devantle plan normal au vecteur passant par l'origine.
         * @param point Le point à vérifier.
         * @return true si le point est devant le plan, false sinon.
         */
        bool isPointInFront(const Point3D& point) const{
            Point3D u = origine - point;

            //normale au plan
            Point3D n = origine - extremite;

            if (u.dotProduct(n) > 0){
                return true;
            }
            return false;

        }

        /**
         * @brief Vérifie si un triangle est visible dépuis l'origine
         * @param triangle Le triangle à vérifier.
         * @return true si le triangle est visible, false sinon.
         */
        bool isTriangleVisible(const Triangle3D& triangle) const{
            return isPointInFront(triangle.getP1()) || isPointInFront(triangle.getP2()) || isPointInFront(triangle.getP3());
        }

        /**
         * @brief Vérifie si un quadrilatère est visible depuis l'origine.
         * @param quad Le quadrilatère à vérifier.
         * @return true si le quadrilatère est visible, false sinon.
         */ 
        bool isQuadVisible(const Quad3D& quad) const{
            return isTriangleVisible(quad.getTriangle1()) || isTriangleVisible(quad.getTriangle2());
        }

        /**
         * @brief Vérifie si un pavé est visible depuis l'origine.
         * @param pave Le pavé à vérifier.
         * @return true si le pavé est visible, false sinon.
         */
        bool isPaveVisible(const Pave3D& pave) const;

        /**
         * @brief Vérifie si une sphère est visible depuis l'origine.
         * @param sphere La sphère à vérifier.
         * @return true si la sphère est visible, false sinon.
         */
        bool isSphereVisible(const Sphere3D& sphere) const;

        /**
         * @brief Vérifie si deux vecteurs sont égaux.
         * @param other L'autre vecteur à comparer.
         * @return true si les deux vecteurs sont égaux, false sinon.
         */
        bool equals(const Vecteur& other) const{
            return origine.equals(other.origine) && extremite.equals(other.extremite);
        }

        /**
         * @brief Surcharge de l'opérateur d'égalité pour les vecteurs.
         * @param other L'autre vecteur à comparer.
         * @return true si les vecteurs sont égaux, false sinon.
         */
        friend bool operator==(const Vecteur& v1, const Vecteur& v2){
            return v1.equals(v2);
        }

        /**
         * @brief Surcharge de l'opérateur d'assignation pour les vecteurs.
         */
        Vecteur& operator=(const Vecteur& other);

        /**
         * @brief Pojette un point  sur le plan normal au vecteur qui a pour origine l'origine du vecteur, puis projette le point sur l'écran.
         * @param point Le point à projeter.
         * @param width La largeur de l'écran.
         * @param height La hauteur de l'écran.
         * @return Le point 2D projeté sur l'écran.
         */
        Point2D project(const Point3D& point, int width, int height) const;

        /**
         * @brief Porjette un triangle sur le plan normal au vecteur qui a pour origine l'origine du vecteur, puis projette le triangle sur l'écran.
         * @param triangle Le triangle à projeter.
         * @param width La largeur de l'écran.
         * @param height La hauteur de l'écran. 
         * @return Le triangle 2D projeté sur l'écran.
         */
        Triangle2D project(const Triangle3D& triangle, int width, int height) const;
};



#endif // VECTEUR_H