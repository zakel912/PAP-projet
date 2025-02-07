/**
 * @file Pave3D.h
 * @brief Déclaration de la classe Pave3D pour représenter un pavé dans l'espace 3D.
 *
 * Cette classe représente un pavé, ou parallélipipède rectangle, défini par six faces planes (des Quad3D)
 * et une couleur associée. Elle fournit des méthodes pour manipuler et interroger ses propriétés géométriques.
 */

#ifndef PAVE3D_H
#define PAVE3D_H

#include "point3d.h"
#include "quad3d.h"
#include "../couleur.h"
#include <array>
#include <vector>
#include "geometry_utils.h"

/**
 * @class Pave3D
 * @brief Classe représentant un pavé dans l'espace 3D.
 *
 * La classe Pave3D permet de stocker les six faces d'un pavé et d'interagir avec ses
 * propriétés géométriques et visuelles, telles que son volume, sa surface totale et sa couleur.
 *
 * @note Les faces doivent former un pavé valide, où les faces opposées sont égales et parallèles,
 * et où les angles entre les faces adjacentes sont droits.
 */
class Pave3D {
private:
    std::array<Quad3D, 6> faces; ///< Tableau contenant les six faces du pavé (avant, arrière, gauche, droite, haut, bas).

    /**
     * @brief Valide la géométrie du pavé.
     *
     * Cette méthode vérifie que les faces définies respectent les propriétés géométriques
     * d'un pavé (parallélipipède rectangle). Elle vérifie notamment que :
     * - Les faces opposées ont la même surface et sont parallèles.
     * - Les faces adjacentes sont perpendiculaires.
     *
     * @throw std::runtime_error Si les faces ne forment pas un pavé valide.
     */
    void validateGeometry() const;

public:
    /**
     * @brief Constructeur par défaut de la classe Pave3D.
     * Initialise un pavé avec des faces standard et une couleur par défaut (noir).
     */
    Pave3D();

    /**
     * @brief Constructeur paramétré de la classe Pave3D.
     * @param faces Tableau contenant les six faces du pavé (ordre : avant, arrière, gauche, droite, haut, bas).
     * @throw std::runtime_error Si les faces ne forment pas un pavé valide.
     */
    Pave3D(const std::array<Quad3D, 6>& faces);

    /**
     * @brief Constructeur paramétré avec des quadrilatères individuels.
     * @param front_quad Face avant du pavé.
     * @param back_quad Face arrière du pavé.
     * @param left_quad Face gauche du pavé.
     * @param right_quad Face droite du pavé.
     * @param top_quad Face supérieure du pavé.
     * @param bottom_quad Face inférieure du pavé.
     */
    Pave3D(const Quad3D& front_quad, const Quad3D& back_quad, const Quad3D& left_quad, const Quad3D& right_quad, const Quad3D& top_quad, const Quad3D& bottom_quad);

    /**
     * @brief Constructeur paramétré avec dimensions et origine.
     * @param origin Le point d'origine du pavé.
     * @param length La longueur du pavé.
     * @param width La largeur du pavé.
     * @param height La hauteur du pavé.
     * @param color La couleur associée au pavé.
     */
    Pave3D(const Point3D& origin, float length, float width, float height, const Couleur& color);

    /**
     * @brief Constructeur par copie de la classe Pave3D.
     * @param other Le pavé à copier.
     */
    Pave3D(const Pave3D& other);

    /**
     * @brief Accesseur pour une face du pavé.
     * @param index Index de la face (0 à 5 : avant, arrière, gauche, droite, haut, bas).
     * @return La face demandée (Quad3D).
     * @throw std::out_of_range Si l'index est hors des limites.
     */
    const Quad3D& getFace(size_t index) const;

    /**
     * @brief Accesseur modifiable pour une face du pavé.
     * @param index Index de la face (0 à 5).
     * @return Une référence modifiable vers la face demandée.
     */
    Quad3D& getFace(size_t index);

    /**
     * @brief Obtient les faces visibles du pavé pour un point d'observation donné.
     * @param eye La position de l'œil (observateur).
     * @return Un vecteur contenant les faces visibles (Quad3D).
     */
    std::vector<Quad3D> getVisibleFaces(const Point3D& eye) const;

    /**
     * @brief Modifie la couleur d'une face spécifique du pavé.
     * @param index L'indice de la face (de 0 à 5).
     * @param color La nouvelle couleur à appliquer à la face.
     * @throws std::out_of_range Si l'indice est hors des limites.
     */
    void setFaceColor(size_t index, const Couleur& color);

    /**
     * @brief Retourne la couleur de la face spécifique.
     * @param index L'indice de la face (de 0 à 5).
     * @return La couleur de la face.
     * @throws std::out_of_range Si l'indice est hors des limites.
     */
    Couleur getFaceColor(size_t index) const;

    /**
     * @brief Calcule le volume du pavé.
     * @return Le volume du pavé (float).
     */
    float volume() const;

    /**
     * @brief Calcule la surface totale du pavé.
     * @return La surface totale du pavé (float).
     */
    float surfaceArea() const;

    /**
     * @brief Vérifie si deux pavés sont égaux.
     * @param other L'autre pavé à comparer.
     * @return true si les pavés sont égaux, false sinon.
     */
    bool equals(const Pave3D& other) const;

    /**
     * @brief Translate le pavé dans l'espace 3D.
     * @param offset Le décalage à appliquer (Point3D).
     */
    void translate(const Point3D& offset);

    /**
     * @brief Translate le pavé selon une distance projetée.
     * @param offset Le décalage à appliquer (Point3D).
     * @param projectionDistance La distance du plan de projection.
     */
    void translate(const Point3D& offset, float projectionDistance);

    /**
     * @brief Effectue une rotation du pavé autour d'un axe donné.
     * @param angle L'angle de rotation en radians.
     * @param axis L'axe de rotation ('x', 'y' ou 'z').
     * @param center Le centre de rotation.
     */
    void rotate(float angle, char axis, const Point3D& center);

    /**
     * @brief Calcule le centre géométrique du pavé.
     * @return Le centre géométrique du pavé (Point3D).
     */
    Point3D center() const;

    /**
     * @brief Calcule la profondeur moyenne du pavé.
     * @return La profondeur moyenne (float).
     */
    float averageDepth() const;

    /**
     * @brief Surcharge de l'opérateur de flux pour afficher un pavé.
     * @param os Le flux de sortie.
     * @param pave Le pavé à afficher.
     * @return Le flux de sortie modifié.
     */
    friend std::ostream& operator<<(std::ostream& os, const Pave3D& pave);
    
    /**
     * @brief Opérateur d'affectation par défaut pour la classe Pave3D.
     * @param other Le pavé source à copier.
     * @return Une référence à cet objet après l'affectation.
     */
    Pave3D& operator=(const Pave3D& other) = default;

};

#endif // PAVE3D_H