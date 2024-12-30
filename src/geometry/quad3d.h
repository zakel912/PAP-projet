/**
 * @file quad3D.h
 * @brief Déclaration de la classe Quad3D pour représenter un quadrilatère dans l'espace 3D.
 */

#ifndef QUAD3D_H
#define QUAD3D_H

#include "point3d.h"
#include "triangle3d.h"
#include <array>

/**
 * @class Quad3D
 * @brief Classe représentant un quadrilatère dans l'espace 3D.
 * 
 * La classe Quad3D permet de manipuler des quadrilatères composés de deux triangles 
 * dans un espace tridimensionnel, et fournit des méthodes pour calculer leurs propriétés.
 */
class Quad3D {
private:
    std::array<Triangle3D, 2> triangles_; ///< Tableau contenant les deux triangles qui composent le quadrilatère.

public:
    /**
     * @brief Constructeur par défaut de la classe Quad3D.
     * 
     * Initialise un quadrilatère vide.
     */
    Quad3D() = default;

    /**
     * @brief Constructeur initialisant un quadrilatère à partir de deux triangles.
     * 
     * @param firstT Premier triangle du quadrilatère.
     * @param secondT Deuxième triangle du quadrilatère.
     */
    Quad3D(const Triangle3D& firstT, const Triangle3D& secondT);

    /**
     * @brief Constructeur par copie de la classe Quad3D.
     * 
     * @param other Le quadrilatère à copier.
     */
    Quad3D(const Quad3D& other) = default;

    /**
     * @brief Constructeur construisant un quadrilatère à partir de quatre points.
     * 
     * Les points doivent être donnés dans l'ordre trigonométrique.
     * 
     * @param p1 Premier sommet du quadrilatère.
     * @param p2 Deuxième sommet du quadrilatère.
     * @param p3 Troisième sommet du quadrilatère.
     * @param p4 Quatrième sommet du quadrilatère.
     * @pre Les points doivent être coplanaires et non alignés.
     */
    Quad3D(const Point3D& p1, const Point3D& p2, const Point3D& p3, const Point3D& p4);

    /**
     * @brief Retourne le premier triangle du quadrilatère.
     * 
     * @return const Triangle3D& Référence constante vers le premier triangle.
     */
    const Triangle3D& getFirstTriangle() const noexcept;

    /**
     * @brief Retourne le deuxième triangle du quadrilatère.
     * 
     * @return const Triangle3D& Référence constante vers le deuxième triangle.
     */
    const Triangle3D& getSecondTriangle() const noexcept;

    /**
     * @brief Calcule la surface totale du quadrilatère.
     * 
     * La surface est la somme des surfaces des deux triangles.
     * 
     * @return float La surface totale du quadrilatère.
     */
    float surface() const;

    /**
     * @brief Vérifie si un point est un sommet du quadrilatère.
     * 
     * @param p Le point à vérifier.
     * @return true Si le point est un sommet du quadrilatère.
     * @return false Sinon.
     */
    bool isVertex(const Point3D& p) const;

    /**
     * @brief Vérifie si deux quadrilatères ont un côté en commun.
     * 
     * @param other L'autre quadrilatère à comparer.
     * @return true Si les deux quadrilatères ont un côté en commun.
     * @return false Sinon.
     */
    bool hasCommonSide(const Quad3D& other) const;

    /**
     * @brief Vérifie si deux quadrilatères ont un côté en commun (méthode statique).
     * 
     * @param q1 Le premier quadrilatère.
     * @param q2 Le deuxième quadrilatère.
     * @return true Si les deux quadrilatères ont un côté en commun.
     * @return false Sinon.
     */
    static bool hasCommonSide(const Quad3D& q1, const Quad3D& q2);

    /**
     * @brief Vérifie si deux quadrilatères ont la même surface.
     * 
     * @param other L'autre quadrilatère à comparer.
     * @return true Si les deux quadrilatères ont la même surface.
     * @return false Sinon.
     */
    bool sameSurface(const Quad3D& other) const;

    /**
     * @brief Compare deux quadrilatères pour vérifier s'ils sont égaux.
     * 
     * Deux quadrilatères sont égaux si leurs triangles correspondants sont égaux.
     * 
     * @param other L'autre quadrilatère à comparer.
     * @return true Si les deux quadrilatères sont égaux.
     * @return false Sinon.
     */
    bool equals(const Quad3D& other) const;

    /**
     * @brief Surcharge de l'opérateur d'égalité pour les quadrilatères.
     * 
     * @param other L'autre quadrilatère à comparer.
     * @return true Si les quadrilatères sont égaux.
     * @return false Sinon.
     */
    bool operator==(const Quad3D& other) const;

    /**
     * @brief Surcharge de l'opérateur de flux pour afficher les informations d'un quadrilatère.
     * 
     * @param os Flux de sortie.
     * @param quad Le quadrilatère à afficher.
     * @return std::ostream& Le flux de sortie modifié.
     */
    friend std::ostream& operator<<(std::ostream& os, const Quad3D& quad);
};

#endif // QUAD3D_H
