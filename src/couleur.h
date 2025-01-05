/**
 * @file couleur.h
 * @brief Déclaration de la classe Couleur pour représenter une couleur RVB.
 */

#ifndef COULEUR_H
#define COULEUR_H

#include <iostream>
#include <stdexcept>

/**
 * @class Couleur
 * @brief Classe représentant une couleur RVB.
 * 
 * La classe Couleur permet de stocker les composantes rouge, verte et bleue d'une couleur
 * et fournit des méthodes pour manipuler et comparer les couleurs.
 */
class Couleur {
private:
    int rouge; // Composante rouge de la couleur (0-255).
    int vert;  // Composante verte de la couleur (0-255).
    int bleu;  // Composante bleue de la couleur (0-255).

    /**
     * @brief Valide une composante RVB.
     * @param valeur La valeur à valider.
     * @throw std::invalid_argument Si la valeur est hors de l'intervalle [0, 255].
     */
    void validateComponent(int valeur) const;
public:
    /**
     * @brief Constructeur initialisant la couleur avec des valeurs spécifiques pour les composantes rouge, verte et bleue.
     * @param rouge La composante rouge (0-255).
     * @param vert La composante verte (0-255).
     * @param bleu La composante bleue (0-255).
     * @throw std::invalid_argument Si une composante est hors de l'intervalle [0, 255].
     */
    Couleur(int rouge = 255, int vert = 255, int bleu = 255);

    /**
     * @brief Constructeur par copie de la classe Couleur.
     * @param other La couleur à copier.
     */
    Couleur(const Couleur& other);

    /**
     * @brief Accesseur pour la composante rouge.
     * @return La composante rouge de la couleur.
     */
    int getRouge() const { return rouge; }

    /**
     * @brief Accesseur pour la composante verte.
     * @return La composante verte de la couleur.
     */
    int getVert() const { return vert; }

    /**
     * @brief Accesseur pour la composante bleue.
     * @return La composante bleue de la couleur.
     */
    int getBleu() const { return bleu; }

    /**
     * @brief Modifie la composante rouge de la couleur.
     * @param rouge La nouvelle valeur de la composante rouge (0-255).
     * @throw std::invalid_argument Si la valeur est hors de l'intervalle [0, 255].
     */
    void setRouge(int rouge) {
        validateComponent(rouge);
        this->rouge = rouge;
    }

    /**
     * @brief Modifie la composante verte de la couleur.
     * @param vert La nouvelle valeur de la composante verte (0-255).
     * @throw std::invalid_argument Si la valeur est hors de l'intervalle [0, 255].
     */
    void setVert(int vert) {
        validateComponent(vert);
        this->vert = vert;
    }

    /**
     * @brief Modifie la composante bleue de la couleur.
     * @param bleu La nouvelle valeur de la composante bleue (0-255).
     * @throw std::invalid_argument Si la valeur est hors de l'intervalle [0, 255].
     */
    void setBleu(int bleu) {
        validateComponent(bleu);
        this->bleu = bleu;
    }

    /**
     * @brief Compare deux couleurs pour l'égalité.
     * @param other L'autre couleur à comparer.
     * @return true si les deux couleurs sont égales, false sinon.
     */
    bool equals(const Couleur& other) const;
    /**
     * @brief Mélange la couleur actuelle avec une autre couleur.
     * @param other L'autre couleur à mélanger.
     * @return Une nouvelle couleur résultant du mélange.
     */
    Couleur blend(const Couleur& other) const;

    /**
     * @brief Affiche la couleur sous forme de chaîne lisible.
     * @param os Flux de sortie.
     * @param couleur La couleur à afficher.
     * @return Le flux de sortie modifié.
     */
    friend std::ostream& operator<<(std::ostream& os, const Couleur& couleur);

    /**
     * @brief Opérateur d'assignation d'une couleur à une autre.
     * @param other La couleur à copier.
     */
    Couleur& operator=(const Couleur& other);

};

// Surcharge des opérateurs
bool operator==(const Couleur& c1, const Couleur& c2);

bool operator!=(const Couleur& c1, const Couleur& c2);

#endif // COULEUR_H
