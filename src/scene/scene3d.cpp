#include "scene3d.h"
#include <algorithm>
#include "../geometry/point3d.h"
#include <stdexcept>
#include <iostream>
#include "../geometry/geometry_utils.h"
#include <memory>

// Constructor
Scene3D::Scene3D(const Point3D& eye, const Point3D& look_at, float projection_plane_distance)
    : cube_(nullptr), sphere_(nullptr), hasCube_(false), hasSphere_(false),
      eye_(eye), look_at_(look_at), projection_plane_distance_(projection_plane_distance) {
    if (projection_plane_distance_ <= TOLERANCE) {
        throw std::invalid_argument("La distance du plan de projection doit être strictement positive.");
    }

    if (eye_.distance(look_at_) < TOLERANCE) {
        throw std::invalid_argument("La position de l'œil et le point de visée ne peuvent pas être les mêmes.");
    }
    std::cout << "Scene3D initialized.\n";
}

// Check if a face is visible
bool Scene3D::isFaceVisible(const Quad3D& quad, const Point3D& eye) const {
    Point3D normal = quad.getNormal();
    Point3D toEye = eye - quad.getCentroid();
    return normal.dotProduct(toEye) > -TOLERANCE;
}

// Add a cube
void Scene3D::addCube(const std::shared_ptr<Pave3D>& cube) {
    cube_ = cube;
    hasCube_ = true;

    // Apply a red color to all faces
    for (size_t i = 0; i < 6; ++i) {
        cube_->setFaceColor(i, Couleur(255, 0, 0));
    }

    // Orient the faces toward the eye
    for (size_t i = 0; i < 6; ++i) {
        cube_->getFace(i).orient(eye_);
    }
}

// Add a sphere
void Scene3D::addSphere(const std::shared_ptr<Sphere3D>& sphere) {
    sphere_ = sphere;
    hasSphere_ = true;
    std::cout << "Sphère définie avec rayon : " << sphere->getRadius() << "\n";

    for (auto& quad : sphere_->getQuads()) {
        quad.orient(eye_);
    }
}

// Update the eye position
void Scene3D::setEye(const Point3D& eye) {
    if (eye.distance(look_at_) < TOLERANCE) {
        throw std::invalid_argument("La position de l'œil et le point de visée ne peuvent pas être les mêmes.");
    }
    eye_ = eye;
    std::cout << "Position de l'œil mise à jour : " << eye_ << "\n";

    // Reorient objects in the scene
    if (hasCube_) {
        for (size_t i = 0; i < 6; ++i) {
            cube_->getFace(i).orient(eye_);
        }
    }
    if (hasSphere_) {
        for (auto& quad : sphere_->getQuads()) {
            quad.orient(eye_);
        }
    }
}

// Update the look-at direction
void Scene3D::setLookAt(const Point3D& look_at) {
    look_at_ = look_at;
    std::cout << "Direction de visée mise à jour : " << look_at_ << "\n";
}

// Update the projection plane distance
void Scene3D::setProjectionPlaneDistance(float distance) {
    if (distance <= TOLERANCE) {
        throw std::invalid_argument("La distance du plan de projection doit être strictement positive.");
    }
    projection_plane_distance_ = distance;
    std::cout << "Distance du plan de projection mise à jour : " << projection_plane_distance_ << "\n";
}

// Clear the scene
void Scene3D::clear() {
    cube_ = nullptr;
    sphere_ = nullptr;
    hasCube_ = false;
    hasSphere_ = false;
    std::cout << "Scène vidée.\n";
}

// Get the cube
Pave3D& Scene3D::getCube() const {
    if (!hasCube_) {
        throw std::logic_error("Aucun cube n'est défini dans la scène.");
    }
    return *cube_;
}

// Get the sphere
Sphere3D& Scene3D::getSphere() const {
    if (!hasSphere_) {
        throw std::logic_error("Aucune sphère n'est définie dans la scène.");
    }
    return *sphere_;
}

// Get visible faces of the cube
std::vector<Quad3D> Scene3D::getVisibleFaces() const {
    if (!hasCube_) {
        throw std::logic_error("Aucun cube n'est défini dans la scène.");
    }

    std::vector<Quad3D> visibleFaces;
    for (size_t i = 0; i < 6; ++i) {
        const Quad3D& face = cube_->getFace(i);
        if (isFaceVisible(face, eye_)) {
            visibleFaces.push_back(face);
        }
    }
    return visibleFaces;
}