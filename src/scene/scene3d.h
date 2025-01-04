#ifndef SCENE3D_H
#define SCENE3D_H

#include "../geometry/pave3d.h"
#include "../geometry/sphere3d.h"
#include "../geometry/triangle2d.h"
#include "../geometry/triangle3d.h"
#include "../geometry/point3d.h"
#include "../geometry/point2d.h"
#include "../geometry/geometry_utils.h"

/**
 * @class Scene3D
 * @brief Classe pour représenter une scène en 3D et gérer la projection en 2D.
 */
class Scene3D {
private:
    Pave3D cube_; ///< Unique cube dans la scène.
    Sphere3D sphere_; ///< Unique sphère dans la scène.
    bool hasCube_; ///< Indique si un cube est défini.
    bool hasSphere_; ///< Indique si une sphère est définie.

    Point3D eye_; ///< Position de l'œil dans l'espace 3D.
    Point3D look_at_; ///< Direction de visée (point cible).
    float projection_plane_distance_; ///< Distance du plan de projection à l'œil.

public:
    /**
     * @brief Constructeur par défaut de Scene3D.
     * @param eye Position initiale de l'œil.
     * @param look_at Point cible initial de la direction de visée.
     * @param projection_plane_distance Distance initiale du plan de projection.
     */
    Scene3D(const Point3D& eye, const Point3D& look_at, float projection_plane_distance);

    /**
     * @brief Projette un point 3D sur le plan 2D.
     * @param point3D Le point en 3D à projeter.
     * @return Le point projeté en 2D.
     */
    Point2D projectPoint(const Point3D& point3D) const;

    /**
     * @brief Projette un triangle 3D sur un plan 2D.
     * @param triangle Le triangle en 3D à projeter.
     * @return Le triangle projeté en 2D.
     */
    Triangle2D projectTriangle(const Triangle3D& triangle) const;

    /**
     * @brief Définit un cube unique dans la scène.
     * @param cube Le cube à ajouter.
     */
    void addCube(const Pave3D& cube);

    /**
     * @brief Définit une sphère unique dans la scène.
     * @param sphere La sphère à ajouter.
     */
    void addSphere(const Sphere3D& sphere);

    /**
     * @brief Récupère les triangles 2D projetés de tous les objets dans la scène.
     * @return Un vecteur contenant les triangles projetés.
     */
    std::vector<Triangle2D> getProjectedTriangles() const;

    /**
     * @brief Récupère le cube de la scène.
     * @return Une référence constante vers le cube.
     * @throw std::logic_error Si aucun cube n'est défini.
     */
    Pave3D& getCube();

    /**
     * @brief Récupère la sphère de la scène.
     * @return Une référence constante vers la sphère.
     * @throw std::logic_error Si aucune sphère n'est définie.
     */
    const Sphere3D& getSphere() const;

    /**
     * @brief Vérifie si un cube est défini dans la scène.
     * @return true si un cube est défini, false sinon.
     */
    bool hasCube() const;

    /**
     * @brief Vérifie si une sphère est définie dans la scène.
     * @return true si une sphère est définie, false sinon.
     */
    bool hasSphere() const;

    /**
     * @brief Met à jour la position de l'œil.
     * @param eye La nouvelle position de l'œil.
     */
    void setEye(const Point3D& eye);

    /**
     * @brief Accesseur pour la position de l'oeil(look_at).
     * @return La position de l'oeil.
     */
    const Point3D& getEye() const{
        return eye_;
    }

    /**
     * @brief Met à jour la direction de visée (point cible).
     * @param look_at Le nouveau point cible.
     */
    void setLookAt(const Point3D& look_at);

    /**
     * @brief Accesseur pour le point de visée (look_at).
     * @return Le point de visée (look_at).
     */
    const Point3D& getLookAt() const{
        return look_at_;
    }

    /**
     * @brief Définit la distance du plan de projection à l'œil.
     * @param distance La nouvelle distance.
     */
    void setProjectionPlaneDistance(float distance);

    bool isVisible(const Triangle3D& triangle, const Point3D& eye) const {
        auto normal = triangle.getNormale();
        auto direction = triangle.getCentroid() - eye;

        std::cout << "Vérification de visibilité pour le triangle :\n";
        std::cout << "  Normale : " << normal << "\n";
        std::cout << "  Direction (œil vers centre) : " << direction << "\n";
        std::cout << "  Produit scalaire : " << normal.dotProduct(direction) << "\n";

        // Si le produit scalaire est positif, la face est visible
        return normal.dotProduct(direction) > -TOLERANCE;
    }



    /**
     * @brief Vide tous les objets de la scène.
     */
    void clear();
};

#endif // SCENE3D_H