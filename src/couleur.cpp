#include "couleur.h"
#include <iostream>

// Constructeur par défaut ou avec paramètres
Couleur::Couleur(int rouge, int vert, int bleu) {
    validateComponent(rouge);
    validateComponent(vert);
    validateComponent(bleu);
    this->rouge = rouge;
    this->vert = vert;
    this->bleu = bleu;
}

Couleur::Couleur(const Couleur& other){
    Couleur(other.getRouge(), other.getVert(), other.getBleu());
}

// Accesseurs et mutateurs (déjà définis inline dans `couleur.h`)

// Validation des composantes RGB
void Couleur::validateComponent(int valeur) const {
    if (valeur < 0 || valeur > 255) {
        throw std::invalid_argument("La valeur de la composante RVB doit être entre 0 et 255.");
    }
}

// Comparaison d'égalité
bool Couleur::equals(const Couleur& other) const {
    return rouge == other.rouge && vert == other.vert && bleu == other.bleu;
}

// Mélange de couleurs
Couleur Couleur::blend(const Couleur& other) const {
    int blendedRouge = (getRouge() + other.getRouge()) / 2;
    int blendedVert = (getVert() + other.getVert()) / 2;
    int blendedBleu = (getBleu() + other.getBleu()) / 2;
    return Couleur(blendedRouge, blendedVert, blendedBleu);
}

// Surcharge des opérateurs
bool operator==(const Couleur& c1, const Couleur& c2) {
    return c1.equals(c2);
}

bool operator!=(const Couleur& c1, const Couleur& c2) {
    return !c1.equals(c2);
}

// Surcharge de l'opérateur <<
std::ostream& operator<<(std::ostream& os, const Couleur& couleur) {
    os << "(R: " << couleur.getRouge() << ", G: " << couleur.getVert() << ", B: " << couleur.getBleu() << ")";
    return os;
}
