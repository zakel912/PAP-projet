#include "scene3d.h"
#include <algorithm>
#include <stdexcept>
#include <iostream>

// Constructeur
Scene3D::Scene3D(const Point3D& eye, const Point3D& look_at, float projection_plane_distance)
    : eye_(eye), look_at_(look_at), projection_plane_distance_(projection_plane_distance) {
    if (projection_plane_distance_ <= TOLERANCE) {
        throw std::invalid_argument("La distance du plan de projection doit être strictement positive.");
    }

    if (eye_.distance(look_at_) < TOLERANCE) {
        throw std::invalid_argument("La position de l'œil et le point de visée ne peuvent pas être les mêmes.");
    }
    std::cout << "Scene3D initialized.\n";
}

// Définir un cube
void Scene3D::addCube(const Pave3D& cube) {
    cube_ = cube;
    hasCube_ = true;
    std::cout << "Cube défini.\n";
    // Orienter les faces du cube par rapport à l'œil
    for (size_t i = 0; i < 6; ++i) {
        cube_.getFace(i).orient(eye_);  // Vérifiez que getFace retourne une référence modifiable
    }
}

// Définir une sphère
void Scene3D::addSphere(const Sphere3D& sphere) {
    sphere_ = sphere;
    hasSphere_ = true;
    std::cout << "Sphère définie avec rayon : " << sphere.getRadius() << "\n";
    // Orienter les quadrilatères de la sphère par rapport à l'œil
    for (auto& quad : sphere_.getQuads()) {  // Assurez-vous que getQuads retourne une référence non-constante
        quad.orient(eye_);
    }
}

// Projection d'un point 3D sur un plan 2D
Point2D Scene3D::projectPoint(const Point3D& point3D) const {
    float dx = point3D.getX() - eye_.getX();
    float dy = point3D.getY() - eye_.getY();
    float dz = point3D.getZ() - eye_.getZ();

    if (dz <= 0) {
        std::cerr << "Projection impossible : le point est derrière l'œil.\n"
                  << "  Point 3D : " << point3D << "\n"
                  << "  Position de l'œil : " << eye_ << "\n"
                  << "  dz (distance Z) : " << dz << "\n";
        throw std::runtime_error("Projection impossible : le point est derrière l'œil.");
    }

    float scale = projection_plane_distance_ / dz;
    float x = dx * scale;
    float y = dy * scale;

    return Point2D(x, y);
}

// Projette un triangle 3D en 2D
Triangle2D Scene3D::projectTriangle(const Triangle3D& triangle) const {
    Point2D p1 = projectPoint(triangle.getP1());
    Point2D p2 = projectPoint(triangle.getP2());
    Point2D p3 = projectPoint(triangle.getP3());

    return Triangle2D(p1, p2, p3, triangle.getColor(), triangle.averageDepth());
}

// Récupère les triangles projetés
std::vector<Triangle2D> Scene3D::getProjectedTriangles() const {
    std::vector<Triangle2D> projectedTriangles;

    auto processTriangles = [&](const std::vector<Triangle3D>& triangles) {
        for (const auto& triangle : triangles) {
            std::cout << "Traitement du triangle 3D : " << triangle << "\n";
            if (isVisible(triangle, eye_)) {
                projectedTriangles.push_back(projectTriangle(triangle));
                std::cout << "  Triangle projeté avec succès.\n";
            } else {
                std::cout << "  Triangle non visible.\n";
            }
        }
    };

    if (hasCube_) {
        std::cout << "Traitement des faces du cube.\n";
        for (size_t i = 0; i < 6; ++i) {
            const Quad3D& face = cube_.getFace(i);
            processTriangles({face.getFirstTriangle(), face.getSecondTriangle()});
        }
    }

    if (hasSphere_) {
        std::cout << "Traitement des quadrilatères de la sphère.\n";
        for (const auto& quad : sphere_.getQuads()) {
            processTriangles({quad.getFirstTriangle(), quad.getSecondTriangle()});
        }
    }

    std::cout << "Nombre de triangles projetés : " << projectedTriangles.size() << "\n";
    return projectedTriangles;
}

// Modifier la position de l'œil
void Scene3D::setEye(const Point3D& eye) {
    if (eye.distance(look_at_) < TOLERANCE) {
        throw std::invalid_argument("La position de l'œil et le point de visée ne peuvent pas être les mêmes.");
    }
    eye_ = eye;
    std::cout << "Position de l'œil mise à jour : " << eye_ << "\n";

    // Réorienter les objets de la scène
    if (hasCube_) {
        for (size_t i = 0; i < 6; ++i) {
            cube_.getFace(i).orient(eye_);
        }
    }
    if (hasSphere_) {
        for (auto& quad : sphere_.getQuads()) {
            quad.orient(eye_);
        }
    }
}

// Modifier la direction de visée
void Scene3D::setLookAt(const Point3D& look_at) {
    look_at_ = look_at;
    std::cout << "Direction de visée mise à jour : " << look_at_ << "\n";
}

// Modifier la distance du plan de projection
void Scene3D::setProjectionPlaneDistance(float distance) {
    if (distance <= TOLERANCE) {
        throw std::invalid_argument("La distance du plan de projection doit être strictement positive.");
    }
    projection_plane_distance_ = distance;
    std::cout << "Distance du plan de projection mise à jour : " << projection_plane_distance_ << "\n";
}

// Vide tous les objets de la scène
void Scene3D::clear() {
    hasCube_ = false;
    hasSphere_ = false;
    std::cout << "Scène vidée.\n";
}

// Accesseur pour le cube
Pave3D& Scene3D::getCube() {
    if (!hasCube_) {
        throw std::logic_error("Aucun cube n'est défini dans la scène.");
    }
    return cube_;
}

// Accesseur pour la sphère
const Sphere3D& Scene3D::getSphere() const {
    if (!hasSphere_) {
        throw std::logic_error("Aucune sphère n'est définie dans la scène.");
    }
    return sphere_;
}

// Vérifie si un cube est défini
bool Scene3D::hasCube() const {
    return hasCube_;
}

// Vérifie si une sphère est définie
bool Scene3D::hasSphere() const {
    return hasSphere_;
}
