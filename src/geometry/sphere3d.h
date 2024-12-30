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
    Point3D center_;              ///< Centre de la sphère.
    float radius_;                ///< Rayon de la sphère.
    int subdivisions_;            ///< Nombre de subdivisions pour discrétiser la sphère.
    std::vector<Quad3D> quads_;   ///< Ensemble des quadrilatères représentant la sphère.

    /**
     * @brief Génère les quadrilatères approximant la sphère.
     *
     * Cette méthode utilise une approche basée sur les coordonnées sphériques
     * pour créer les quadrilatères approximant la sphère.
     */
    void generateQuads();

public:
    /**
     * @brief Constructeur de la classe Sphere3D.
     * @param center Le centre de la sphère.
     * @param radius Le rayon de la sphère (doit être positif).
     * @param subdivisions Le nombre de subdivisions pour discrétiser la sphère (doit être > 0).
     */
    Sphere3D(const Point3D& center, float radius, int subdivisions);

    /**
     * @brief Accesseur pour le centre de la sphère.
     * @return Le centre de la sphère.
     */
    Point3D getCenter() const;

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
     * @param radius Le nouveau rayon (doit être positif).
     */
    void setRadius(float radius);

    /**
     * @brief Accesseur pour les quadrilatères approximant la sphère.
     * @return Une référence constante vers le vecteur des quadrilatères.
     */
    const std::vector<Quad3D>& getQuads() const;

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
