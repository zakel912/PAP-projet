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
    Point3D center;              ///< Centre de la sphère.
    float radius;                ///< Rayon de la sphère.
    int subdivisions;            ///< Nombre de subdivisions pour discrétiser la sphère.
    std::vector<Quad3D> quads;   ///< Ensemble des quadrilatères représentant la sphère.

    Couleur color;

    /**
     * @brief Génère les quadrilatères approximant la sphère.
     *
     * Cette méthode utilise une approche basée sur les coordonnées sphériques
     * pour créer les quadrilatères approximant la sphère.
     */
    void generateQuads(int numSlices, int numStacks);

public:
    /**
     * @brief Constructeur de la classe Sphere3D.
     * @param center Le centre de la sphère.
     * @param radius Le rayon de la sphère (doit être positif).
     * @param subdivisions Le nombre de subdivisions pour discrétiser la sphère (doit être > 0).
     * @param rouge La composante rouge de la couleur de la sphère.
     * @param vert La composante verte de la couleur de la sphère.
     * @param bleu La composante bleue de la couleur de la sphère.
     * @pre Le rayon doit être strictement positif.
     */
    Sphere3D(const Point3D& center = Point3D(), float radius = 1, int subdivisions = 1, int rouge = 0, int vert = 0, int bleu = 0);

    /**
     * @brief Constructeur initialisant la sphère avec des valeurs spécifiques pour le centre, le rayon et pour la couleur.
     * @param center Centre de la sphère.
     * @param color La couleur de la sphère.
     * @param radius Rayon de la sphère.
     * @param subdivisions Le nombre de subdivisions pour discrétiser la sphère (doit être > 0).
     * @pre Le rayon doit être strictement positif.
     */
    Sphere3D(const Point3D& center, const Couleur& color, float radius = 1, int subdivisions = 1);

   

    /**
     * @brief Constructeur par copie de la classe Sphere3D.
     * @param other La sphère à copier.
     * @return Une nouvelle sphère qui est une copie de other.
     */
    Sphere3D(const Sphere3D& other){
        Sphere3D(other.getCenter(), other.getColor(), other.getRadius(), other.subdivisions);
    }

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
     * @brief Accesseur pour la couleur de la sphère.
     * @return La couleur de la sphère.
     */
    Couleur getColor() const { return color; }

    /**
     * @brief Modifie la couleur de la sphère.  
     * @param rouge La composante rouge de la couleur de la sphère.
     * @param vert La composante verte de la couleur de la sphère.
     * @param bleu La composante bleue de la couleur de la sphère.
     */
    void setColor(int rouge, int vert, int bleu);

    /**
     * @brief Modifie la couleur de la sphère.
     * @param color La nouvelle couleur de la sphère.
     */
    void setColor(const Couleur& color);

    /**
     * @brief Modifie la composante rouge de la couleur de la sphère.
     * @param rouge La nouvelle composante rouge de la couleur de la sphère.
     */
    void setColorRouge(int rouge);

    /**
     * @brief Modifie la composante verte de la couleur de la sphère.
     * @param vert La nouvelle composante verte de la couleur de la sphère.
     */
    void setColorVert(int vert);

    /**
     * @brief Modifie la composante bleue de la couleur de la sphère.
     * @param bleu La nouvelle composante bleue de la couleur de la sphère.
     */
    void setColorBleu(int bleu);

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