#ifndef SCENE3D_H
#define SCENE3D_H

#include <vector>
#include <memory>
#include "pave3d.h"
#include "sphere3d.h"
#include "triangle2d.h"
#include "point3d.h"
#include "point2d.h"

/**
 * @class Scene3D
 * @brief Classe pour représenter une scène en 3D et gérer la projection en 2D.
 */
class Scene3D {
private:
    std::vector<std::shared_ptr<Pave3D>> cubes_; ///< Liste des cubes dans la scène.
    std::vector<std::shared_ptr<Sphere3D>> spheres_; ///< Liste des sphères dans la scène.

    Point3D eye_; ///< Position de l'œil dans l'espace 3D.
    Point3D look_at_; ///< Direction de visée (point cible).
    float projection_plane_distance_; ///< Distance du plan de projection à l'œil.

    /**
     * @brief Projette un point 3D sur le plan 2D.
     * @param point3D Le point en 3D à projeter.
     * @return Le point projeté en 2D.
     */
    Point2D projectPoint(const Point3D& point3D) const;

public:
    /**
     * @brief Constructeur par défaut de Scene3D.
     * @param eye Position initiale de l'œil.
     * @param look_at Point cible initial de la direction de visée.
     * @param projection_plane_distance Distance initiale du plan de projection.
     */
    Scene3D(const Point3D& eye, const Point3D& look_at, float projection_plane_distance);

    /**
     * @brief Ajoute un cube (Pave3D) à la scène.
     * @param cube Un pointeur intelligent vers le cube à ajouter.
     */
    void addCube(const std::shared_ptr<Pave3D>& cube);

    /**
     * @brief Ajoute une sphère (Sphere3D) à la scène.
     * @param sphere Un pointeur intelligent vers la sphère à ajouter.
     */
    void addSphere(const std::shared_ptr<Sphere3D>& sphere);

    /**
     * @brief Récupère les triangles 2D projetés de tous les objets dans la scène.
     * @return Un vecteur contenant les triangles projetés.
     */
    std::vector<Triangle2D> getProjectedTriangles() const;

    /**
     * @brief Met à jour la position de l'œil.
     * @param eye La nouvelle position de l'œil.
     */
    void setEye(const Point3D& eye);

    /**
     * @brief Met à jour la direction de visée (point cible).
     * @param look_at Le nouveau point cible.
     */
    void setLookAt(const Point3D& look_at);

    /**
     * @brief Définit la distance du plan de projection à l'œil.
     * @param distance La nouvelle distance.
     */
    void setProjectionPlaneDistance(float distance);

    /**
     * @brief Vide tous les objets de la scène.
     */
    void clear();
};

#endif // SCENE3D_H
