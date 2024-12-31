/**
 * @file Pave3D.h
 * @brief Déclaration de la classe Pave3D pour représenter un pavé dans l'espace 3D.
 *
 * Cette classe représente un pavé, ou parallélipipède rectangle, défini par six faces planes (des Quad3D)
 * et une couleur associée. Elle fournit des méthodes pour manipuler et interroger ses propriétés géométriques,
 * telles que le volume et la surface totale.
 */

#ifndef PAVE3D_H
#define PAVE3D_H

#include "point3d.h"
#include "quad3d.h"
#include "../couleur.h"
#include <array>

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
    Couleur color; ///< Couleur associée au pavé.

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
     *
     * Initialise un pavé avec des faces standard et une couleur par défaut (noir).
     */
    Pave3D();

    /**
     * @brief Constructeur paramétré de la classe Pave3D.
     *
     * Ce constructeur permet de définir un pavé à partir de ses six faces et d'une couleur associée.
     *
     * @param faces Tableau contenant les six faces du pavé (ordre : avant, arrière, gauche, droite, haut, bas).
     * @param color Couleur associée au pavé.
     *
     * @throw std::runtime_error Si les faces ne forment pas un pavé valide.
     */
    Pave3D(const std::array<Quad3D, 6>& faces, const Couleur& color);

    Pave3D(Quad3D front_quad, Quad3D back_quad, Quad3D left_quad, Quad3D right_quad, Quad3D top_quad, Quad3D bottom_quad, Couleur color);

    /**
     * @brief Constructeur par copie de la classe Pave3D.
     *
     * Ce constructeur crée une copie complète d'un pavé existant.
     *
     * @param other Le pavé à copier.
     */
    Pave3D(const Pave3D& other);

    /**
     * @brief Accesseur pour une face du pavé.
     *
     * @param index Index de la face (0 à 5 : avant, arrière, gauche, droite, haut, bas).
     * @return La face demandée (Quad3D).
     * @throw std::out_of_range Si l'index est hors des limites.
     */
    const Quad3D& getFace(size_t index) const;

    /**
     * @brief Accesseur pour la couleur du pavé.
     *
     * @return La couleur du pavé (Couleur).
     */
    const Couleur& getColor() const {
        return color;
    }

    /**
     * @brief Modifie la couleur du pavé.
     *
     * Cette modification s'applique à toutes les faces du pavé.
     *
     * @param color La nouvelle couleur du pavé.
     */
    void setColor(const Couleur& color);

    /**
     * @brief Modifie la couleur du pavé.
     *
     * Cette modification s'applique à toutes les faces du pavé.
     *
     * @param rouge Composante rouge de la couleur (0-255).
     * @param vert Composante verte de la couleur (0-255).
     * @param bleu Composante bleue de la couleur (0-255).
     */
    void setColor(int rouge=0, int vert=0, int bleu=0);

    /**
     * @brief Modifie la composante rouge de la couleur du pavé.
     * @param rouge La nouvelle composante rouge de la couleur (0-255).
     */
    void setColorRouge(int rouge);

    /**
     * @brief Modifie la composante verte de la couleur du pavé.
     * @param vert La nouvelle composante verte de la couleur (0-255).
     */
    void setColorVert(int vert);

    /**
     * @brief Modifie la composante bleue de la couleur du pavé.
     * @param bleu La nouvelle composante bleue de la couleur (0-255).
     */
    void setColorBleu(int bleu);

    /**
     * @brief Calcule le volume du pavé.
     *
     * Le volume est calculé en supposant que les dimensions sont bien alignées et définies par les faces.
     *
     * @return Le volume du pavé (float).
     */
    float volume() const;

    /**
     * @brief Calcule la surface totale du pavé.
     *
     * La surface totale est la somme des surfaces de toutes les faces du pavé.
     *
     * @return La surface totale du pavé (float).
     */
    float surfaceArea() const;

    /**
     * @brief Vérifie si deux pavés sont égaux.
     *
     * Deux pavés sont considérés comme égaux si toutes leurs faces et leur couleur sont identiques.
     *
     * @param other L'autre pavé à comparer.
     * @return true si les pavés sont égaux, false sinon.
     */
    bool equals(const Pave3D& other) const;

    /**
     * @brief Surcharge de l'opérateur de flux pour afficher un pavé.
     *
     * Affiche les informations détaillées du pavé, y compris ses faces et sa couleur.
     *
     * @param os Le flux de sortie.
     * @param pave Le pavé à afficher.
     * @return Le flux de sortie modifié.
     */
    friend std::ostream& operator<<(std::ostream& os, const Pave3D& pave);
};

#endif // PAVE3D_H