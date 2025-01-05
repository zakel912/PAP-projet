#ifndef SCENE3D_H
#define SCENE3D_H

#include "../geometry/pave3d.h"
#include "../geometry/sphere3d.h"
#include "../geometry/triangle2d.h"
#include "../geometry/triangle3d.h"
#include "../geometry/point3d.h"
#include "../geometry/point2d.h"
#include "../geometry/geometry_utils.h"
#include <memory>

/**
 * @class Scene3D
 * @brief Classe pour représenter une scène en 3D et gérer la projection en 2D.
 */
class Scene3D {
private:
    std::shared_ptr<Pave3D> cube_;;
    std::shared_ptr<Sphere3D> sphere_;
    bool hasCube_;                      // Indique si un cube est défini.
    bool hasSphere_;                    // Indique si une sphère est définie.

    Point3D eye_;                       // Position de l'œil dans l'espace 3D.
    Point3D look_at_;                   // Direction de visée (point cible).
    float projection_plane_distance_;   // Distance du plan de projection à l'œil.

public:
    /**
     * @brief Constructeur par défaut de Scene3D.
     * @param eye Position initiale de l'œil.
     * @param look_at Point cible initial de la direction de visée.
     * @param projection_plane_distance Distance initiale du plan de projection.
     */
    Scene3D(const Point3D& eye, const Point3D& look_at, float projection_plane_distance);
    
    /**
     * @brief Définit un cube unique dans la scène.
     * @param cube Le cube à ajouter.
     */
    void addCube(const std::shared_ptr<Pave3D>& cube);

    /**
     * @brief Définit une sphère unique dans la scène.
     * @param sphere La sphère à ajouter.
     */
    void addSphere(const std::shared_ptr<Sphere3D>& sphere);

    /**
     * @brief Récupère le cube de la scène.
     * @return Une référence constante vers le cube.
     * @throw std::logic_error Si aucun cube n'est défini.
     */
    Pave3D& getCube() const;

    /**
     * @brief Récupère la sphère de la scène.
     * @return Une référence constante vers la sphère.
     * @throw std::logic_error Si aucune sphère n'est définie.
     */
    Sphere3D& getSphere() const;
    
    /**
     * @brief Vérifie si un cube est défini dans la scène.
     * @return true si un cube est défini, false sinon.
     */
    bool hasCube() const { return hasCube_; }

    /**
     * @brief Vérifie si une sphère est définie dans la scène.
     * @return true si une sphère est définie, false sinon.
     */
    bool hasSphere() const { return hasSphere_; }

    /**
     * @brief Met à jour la position de l'œil.
     * @param eye La nouvelle position de l'œil.
     */
    void setEye(const Point3D& eye);

    /**
     * @brief Accesseur pour la position de l'oeil(look_at).
     * @return La position de l'oeil.
     */
    const Point3D& getEye() const{ return eye_; }

    /**
     * @brief Met à jour la direction de visée (point cible).
     * @param look_at Le nouveau point cible.
     */
    void setLookAt(const Point3D& look_at);

    /**
     * @brief Accesseur pour le point de visée (look_at).
     * @return Le point de visée (look_at).
     */
    const Point3D& getLookAt() const{ return look_at_; }

    /**
     * @brief Définit la distance du plan de projection à l'œil.
     * @param distance La nouvelle distance.
     */
    void setProjectionPlaneDistance(float distance);

    /**
     * @brief retourne la distance du plan de projection à l'œil.
     */
    float getProjectionPlaneDistance() const { return projection_plane_distance_; }

    /**
     * @brief Vide tous les objets de la scène.
     */
    void clear();

    /**
     * @brief Récupère les faces visibles du cube.
     * @return Un vecteur contenant les faces visibles.
     */
    std::vector<Quad3D> getVisibleFaces() const;

    /**
     * @brief Determines if a face is visible from the eye's perspective.
     * @param quad The face to check.
     * @param eye The position of the eye.
     * @return True if the face is visible, false otherwise.
     */
    bool isFaceVisible(const Quad3D& quad, const Point3D& eye) const;
    
    void rotateCamera(float angle, char axis) {

        Point3D direction = eye_ - look_at_;

        direction.rotate(angle, axis, Point3D(0,0,0));

        eye_ = look_at_ + direction;
    }

};

#endif // SCENE3D_H