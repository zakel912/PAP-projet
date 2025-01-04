/** 
 * @file Sphere3D.h
 * @brief Déclaration de la classe Sphere3D pour représenter une sphère en 3D.
 *
 * La classe Sphere3D permet de représenter une sphère à l'aide d'un centre et d'un rayon.
 * La sphère est discrétisée en un ensemble de quadrilatères (à travers des Quad3D).
 */

#ifndef SPHERE3D_H
#define SPHERE3D_H

#include "point3d.h"
#include "quad3d.h"
#include "../couleur.h"
#include <vector>
#include <cmath>
#include <stdexcept>

/**
 * @class Sphere3D
 * @brief Classe représentant une sphère dans l'espace 3D.
 *
 * La sphère est approximée par un ensemble de quadrilatères (à travers des Quad3D).
 */
class Sphere3D {
private:
    Point3D center;              // Centre de la sphère.
    float radius;                // Rayon de la sphère.
    int subdivisions;            // Nombre de subdivisions pour discrétiser la sphère.
    std::vector<Quad3D> quads;   // Ensemble des quadrilatères représentant la sphère.


    /**
     * @brief Génère les quadrilatères approximant la sphère.
     *
     * Cette méthode utilise une approche basée sur les coordonnées sphériques
     * pour créer les quadrilatères approximant la sphère.
     */
    void generateQuads(int numSlices, int numStacks, const Couleur& color = Couleur(0, 0, 0));


public:
    /**
     * @brief Constructeur de la classe Sphere3D.
     * @param center Le centre de la sphère.
     * @param radius Le rayon de la sphère (doit être positif).
     * @param subdivisions Le nombre de subdivisions pour discrétiser la sphère (doit être > 0).
     * @pre Le rayon doit être strictement positif.
     */
    Sphere3D(const Point3D& center = Point3D(), float radius = 1, int subdivisions = 1);

    /**
     * @brief Constructeur par copie de la classe Sphere3D.
     * @param other La sphère à copier.
     * @return Une nouvelle sphère qui est une copie de other.
     */
    Sphere3D(const Sphere3D& other)
        : center(other.center), radius(other.radius), subdivisions(other.subdivisions), quads(other.quads) {
        if (radius <= 0 || subdivisions <= 0) {
            throw std::invalid_argument("Cannot copy a sphere with invalid parameters.");
        }
    }
    /**
     * @brief Accesseur pour le centre de la sphère.
     * @return Le centre de la sphère.
     */
    const Point3D getCenter() const;

    /**
     * @brief Modifie le centre de la sphère.
     * @param center Le nouveau centre de la sphère.
     */
    void setCenter(const Point3D& center);

    /**
     * @brief Accesseur pour le rayon de la sphère.
     * @return Le rayon de la sphère.
     */
    float getRadius() const;

    /**
     * @brief Modifie le rayon de la sphère.
     * @param radius Le nouveau rayon (doit être strictement positif).
     * @throw std::invalid_argument Si le rayon est <= 0.
     */
    void setRadius(float radius);

    /**
     * @brief Accesseur pour les quadrilatères approximant la sphère.
     * @return Une référence constante vers le vecteur des quadrilatères.
     */
    const std::vector<Quad3D>& getQuads() const;

    std::vector<Quad3D>& getQuads() {
        return quads;
    }

    /**
     * @brief Modifie la couleur d'un quadrilatère spécifique de la sphère.
     * @param index L'indice du quadrilatère.
     * @param color La nouvelle couleur.
     * @throw std::out_of_range Si l'indice est invalide.
     */
    void setQuadColor(int index, const Couleur& color);

    /**
     * @brief Accesseur pour la couleur d'un quadrilatère spécifique de la sphère.
     * @param index L'indice du quadrilatère.
     * @return La couleur du quadrilatère.
     * @throw std::out_of_range Si l'indice est invalide.
     */
    Couleur getQuadColor(int index) const;

    /**
     * @brief Calcul le volume de la sphère.
     * @return Le volume de la sphère.
     */
    float volume() const;

    /**
     * @brief Calcul la surface totale de la sphère.
     * @return La surface totale de la sphère.
     */
    float surfaceArea() const;
};

#endif