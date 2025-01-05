/**
 * @file quad3D.h
 * @brief Déclaration de la classe Quad3D pour représenter un quadrilatère dans l'espace 3D.
 */

#ifndef QUAD3D_H
#define QUAD3D_H

#include "point3d.h"
#include "triangle3d.h"
#include "vector"
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
    Quad3D();

    /**
     * @brief Constructeur initialisant un quadrilatère à partir de deux triangles.
     * 
     * @param firstT Premier triangle du quadrilatère.
     * @param secondT Deuxième triangle du quadrilatère.
     * @param rouge La composante rouge de la couleur du quadrilatère.
     * @param vert La composante verte de la couleur du quadrilatère.
     * @param bleu La composante bleue de la couleur du quadrilatère.
     * @pre Les triangles ne doivent pas être alignés.
     */
    Quad3D(const Triangle3D& firstT, const Triangle3D& secondT, int rouge = 0, int vert = 0, int bleu = 0);

    /**
     * @brief Constructeur initialisant un quadrilatère à partir de deux triangles.
     * 
     * @param secondT Premier triangle du quadrilatère.
     * @param secondT Deuxième triangle du quadrilatère.
     * @param color La couleur du quadrilatère.
     * @pre Les triangles ne doivent pas être alignés.
     */
    Quad3D(const Triangle3D& firstT, const Triangle3D& secondT, const Couleur& color);

    /**
     * @brief Constructeur par copie de la classe Quad3D.
     * 
     * @param other Le quadrilatère à copier.
     */
    Quad3D(const Quad3D& other);

    /**
     * @brief Constructeur construisant un quadrilatère à partir de quatre points.
     * @param p1 Premier sommet du quadrilatère.
     * @param p2 Deuxième sommet du quadrilatère.
     * @param p3 Troisième sommet du quadrilatère.
     * @param p4 Quatrième sommet du quadrilatère.
     * @param rouge La composante rouge de la couleur du quadrilatère.
     * @param vert La composante verte de la couleur du quadrilatère.
     * @param bleu La composante bleue de la couleur du quadrilatère.
     * @pre Trois points ne doivents pas être alignés.
     */
    Quad3D(const Point3D &p1, const Point3D &p2, const Point3D &p3, const Point3D &p4, int rouge = 0, int vert = 0, int bleu = 0);

    /**
     * @brief Constructeur construisant un quadrilatère à partir de quatre points.
     * @param p1 Premier sommet du quadrilatère.
     * @param p2 Deuxième sommet du quadrilatère.
     * @param p3 Troisième sommet du quadrilatère.
     * @param p4 Quatrième sommet du quadrilatère.
     * @param color La couleur du quadrilatère.
     * @pre Trois points ne doivents pas être alignés.
     */
    Quad3D(const Point3D& p1, const Point3D& p2, const Point3D& p3, const Point3D& p4, const Couleur& color);

    /**
     * @brief Détruit le quadrilatère.
     */
    ~Quad3D(){}

    /**
     * @brief Retourne le premier triangle du quadrilatère.
     * @return const Triangle3D& Référence constante vers le premier triangle.
     */
    const Triangle3D& getFirstTriangle() const noexcept;

    /**
     * @brief Retourne le deuxième triangle du quadrilatère.
     * @return const Triangle3D& Référence constante vers le deuxième triangle.
     */
    const Triangle3D& getSecondTriangle() const noexcept;

    /**
     * @brief Accesseur pour la couleur du quadrilatère.
     * @return La couleur du quadrilatère.
     */
    Couleur getColor() const;

    /**
     * @brief Modifie la couleur du quadrilatère.
     * @param color La nouvelle couleur du quadrilatère.
     * @return void
     */
    void setColor(const Couleur &color);

    /**
     * @brief Modifie la couleur du quadrilatère.
     * @param rouge La composante rouge de la couleur du quadrilatère.
     * @param vert La composante verte de la couleur du quadrilatère.
     * @param bleu La composante bleue de la couleur du quadrilatère.
     * @return void
     */
    void setColor(int rouge, int vert, int bleu);
    
    /**
     * @brief Modifie la composante rouge de la couleur du quadrilatère.
     * @param rouge La nouvelle composante rouge de la couleur du quadrilatère.
     * @return void
     */
    void setColorRouge(int rouge){
        triangles_[0].setColorRouge(rouge);
        triangles_[1].setColorRouge(rouge);
    }

    /**
     * @brief Modifie la composante verte de la couleur du quadrilatère.
     * @param vert La nouvelle composante verte de la couleur du quadrilatère.
     * @return void
     */
    void setColorVert(int vert){
        triangles_[0].setColorVert(vert);
        triangles_[1].setColorVert(vert);
    }

    /**
     * @brief Modifie la composante bleue de la couleur du quadrilatère.
     * @param bleu La nouvelle composante bleue de la couleur du quadrilatère.
     * @return void
     */
    void setColorBleu(int bleu){
        triangles_[0].setColorBleu(bleu);
        triangles_[1].setColorBleu(bleu);
    }

    /**
     * @brief Calcule la surface totale du quadrilatère.
     * @return float La surface totale du quadrilatère.
     */
    float surface() const;

    /**
     * @brief Vérifie si un point est un sommet du quadrilatère.
     * @param p Le point à vérifier.
     * @return true Si le point est un sommet du quadrilatère.
     * @return false Sinon.
     */
    bool isVertex(const Point3D& p) const;

    /**
     * @brief Vérifie si deux quadrilatères ont un côté en commun.
     * @param other L'autre quadrilatère à comparer.
     * @return true Si les deux quadrilatères ont un côté en commun.
     * @return false Sinon.
     */
    bool hasCommonSide(const Quad3D& other) const;

    /**
     * @brief Vérifie si deux quadrilatères ont un côté en commun (méthode statique).
     * @param q1 Le premier quadrilatère.
     * @param q2 Le deuxième quadrilatère.
     * @return true Si les deux quadrilatères ont un côté en commun.
     * @return false Sinon.
     */
    static bool hasCommonSide(const Quad3D& q1, const Quad3D& q2);

    /**
     * @brief Vérifie si deux quadrilatères ont la même surface.
     * @param other L'autre quadrilatère à comparer.
     * @return true Si les deux quadrilatères ont la même surface.
     * @return false Sinon.
     */
    bool sameSurface(const Quad3D& other) const;

    /**
     * @brief Compare deux quadrilatères pour vérifier s'ils sont égaux.
     * @param other L'autre quadrilatère à comparer.
     * @return true Si les deux quadrilatères sont égaux.
     * @return false Sinon.
     */
    bool equals(const Quad3D& other) const;

    /**
     * @brief Calcule la normale au quadrilatère.
     * @return Point3D Normale calculée à partir du premier triangle.
     */
    Point3D getNormal() const {
        return getFirstTriangle().getNormale();
    }

    /**
     * @brief Surcharge de l'opérateur d'égalité pour les quadrilatères.
     * @param other L'autre quadrilatère à comparer.
     * @return true Si les quadrilatères sont égaux.
     * @return false Sinon.
     */
    bool operator==(const Quad3D& other) const;

    /**
     * @brief Retrieves the vertices of the quadrilateral.
     * @return A vector of Point3D objects representing the vertices of the quadrilateral.
     */
    std::vector<Point3D> getVertices() const;

    /**
     * @brief Translate le quadrilatère dans l'espace 3D.
     * @param offset Le décalage à appliquer (Point3D).
     */
    void translate(const Point3D& offset) {
        triangles_[0].translate(offset);
        triangles_[1].translate(offset);
    }

    /**
     * @brief Orient les sommets du quadrilatère dans le sens trigonométrique en fonction de l'oeil.
     * @param eye L'oeil de la caméra.
     * @return void
     */
    void orient(const Point3D& eye);

    /**
     * @brief Retourne le centre du quadrilatère.
     * @return Point3D Le centre du quadrilatère.
     */
    Point3D center() const;

    /**
     * @brief Effectue une rotation du quadrilatère autour d'un axe donné.
     * @param angle Angle de rotation en radians.
     * @param axis Axe de rotation ('x', 'y' ou 'z').
     */
    void rotate(float angle, char axis);

    /**
     * @brief Effectue une rotation autour d'un axe et d'un centre donnés.
     * @param angle Angle de rotation en radians.
     * @param axis Axe de rotation ('x', 'y' ou 'z').
     * @param center Centre de rotation.
     */
    void rotate(float angle, char axis, const Point3D& center);

    /**
     * @brief Calculates the average depth of the quad.
     * @return The average depth of the two triangles composing the quad.
     */
    float averageDepth() const;

    /**
     * @brief Calcule le centroïde du quadrilatère.
     * @return Point3D Centroïde moyen des triangles.
     */
    Point3D getCentroid() const {

        Point3D centroid1 = triangles_[0].getCentroid();
        Point3D centroid2 = triangles_[1].getCentroid();

        return (centroid1 + centroid2) * 0.5;
    }

    /**
     * @brief Surcharge de l'opérateur de flux pour afficher les informations d'un quadrilatère.
     * @param os Flux de sortie.
     * @param quad Le quadrilatère à afficher.
     * @return std::ostream& Le flux de sortie modifié.
     */
    friend std::ostream& operator<<(std::ostream& os, const Quad3D& quad);

    /**
     * @brief Compare la profondeur moyenne de deux quadrilatères en 3D.
     * @param other Le quadrilatère avec lequel effectuer la comparaison.
     * @return `true` si la profondeur moyenne de ce quadrilatère est inférieure à celle de `other`,
     *         `false` sinon.
     */
    bool operator<(const Quad3D& other) const {
        return this->averageDepth() < other.averageDepth();
    }

    /**
     * @brief Opérateur d'affectation par défaut pour la classe Quad3D.
     * @param other L'objet `Quad3D` à copier.
     * @return Une référence à cet objet après l'affectation.
     */
    Quad3D& operator=(const Quad3D&) = default;

};

#endif // QUAD3D_H
