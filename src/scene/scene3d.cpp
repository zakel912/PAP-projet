#include "scene3d.h"
#include <algorithm>
#include <stdexcept>
#include <iostream>

// Constructeur
Scene3D::Scene3D(const Point3D& eye, const Point3D& look_at, float projection_plane_distance)
    : eye_(eye), look_at_(look_at), projection_plane_distance_(projection_plane_distance) {
    if (projection_plane_distance_ <= 0) {
        throw std::invalid_argument("La distance du plan de projection doit être strictement positive.");
    }

    if (eye_.distance(look_at_) < 1e-6) {
        throw std::invalid_argument("La position de l'\u0153il et le point de visée ne peuvent pas être les mêmes.");
    }
}

// Ajout d'un cube à la scène
void Scene3D::addCube(const std::shared_ptr<Pave3D>& cube) {
    if (!cube) {
        throw std::invalid_argument("Le cube ajouté est invalide (nullptr).");
    }
    cubes_.push_back(cube);
    std::cout << "Cube ajouté : " << cube->getColor() << "\n";
}

// Ajout d'une sphère à la scène
void Scene3D::addSphere(const std::shared_ptr<Sphere3D>& sphere) {
    if (!sphere) {
        throw std::invalid_argument("La sphère ajoutée est invalide (nullptr).");
    }
    spheres_.push_back(sphere);
    std::cout << "Sphère ajoutée avec rayon : " << sphere->getRadius() << "\n";
}

// Projection d'un point 3D sur un plan 2D
Point2D Scene3D::projectPoint(const Point3D& point3D) const {
    // Calcul de la projection perspective
    float dx = point3D.getX() - eye_.getX();
    float dy = point3D.getY() - eye_.getY();
    float dz = point3D.getZ() - eye_.getZ();

    if (dz <= 0) {
        std::cerr << "Projection impossible : le point est derrière l'\u0153il.\n"
                  << "  Point 3D : " << point3D << "\n"
                  << "  Position de l'\u0153il : " << eye_ << "\n"
                  << "  dz (distance Z) : " << dz << "\n";
        throw std::runtime_error("Projection impossible : le point est derrière l'\u0153il.");
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

// Récupère les triangles projetés des cubes
std::vector<Triangle2D> Scene3D::getProjectedTrianglesFromCubes() const {
    std::vector<Triangle2D> projectedTriangles;

    for (const auto& cube : cubes_) {
        for (const auto& face : cube->getFaces()) {
            const Triangle3D& t1 = face.getFirstTriangle();
            const Triangle3D& t2 = face.getSecondTriangle();

            // Projection du premier triangle
            try {
                if (t1.isValid()) {
                    Triangle2D t = projectTriangle(t1);
                    projectedTriangles.push_back(t);
                }
            } catch (const std::exception& e) {
                std::cerr << "Erreur lors de la projection du triangle T1 : " << e.what() << "\n";
            }

            // Projection du deuxième triangle
            try {
                if (t2.isValid()) {
                    Triangle2D t = projectTriangle(t2);
                    projectedTriangles.push_back(t);
                }
            } catch (const std::exception& e) {
                std::cerr << "Erreur lors de la projection du triangle T2 : " << e.what() << "\n";
            }
        }
    }

    return projectedTriangles;
}

// Récupère les triangles projetés des sphères

std::vector<Triangle2D> Scene3D::getProjectedTrianglesFromSpheres() const {
    std::vector<Triangle2D> projectedTriangles;
    size_t collinearCount = 0;  

    for(const auto& sphere : spheres_) {
        for(const auto& quad : sphere->getQuads()) {
            const Triangle3D& t1 = quad.getFirstTriangle();
            const Triangle3D& t2 = quad.getSecondTriangle();

            // Projection des triangles
            try {
                if (t1.isValid()) {
                    Triangle2D t = projectTriangle(t1);
                    projectedTriangles.push_back(t);
                } else {
                    std::cerr << "Erreur : Les points projetés du triangle T1 d'un quad de la sphère forment une ligne droite en 2D.\n";
                    ++collinearCount;
                    continue;
                }

                if (t2.isValid()) {
                    Triangle2D t = projectTriangle(t2);
                    projectedTriangles.push_back(t);
                } else {
                    std::cerr << "Erreur : Les points projetés du triangle T2 d'un quad de la sphère forment une ligne droite en 2D.\n";
                    ++collinearCount;
                    continue;
                }
            } catch (const std::exception& e) {
                std::cerr << "Erreur lors de la projection des triangles : " << e.what() << "\n";
            }
        }
    }

    if (collinearCount > 0) {
        std::cerr << collinearCount << " triangles colinéaires ignorés.\n";
    }

    return projectedTriangles;
}


// Récupère les triangles projetés
std::vector<Triangle2D> Scene3D::getProjectedTriangles() const {
    std::vector<Triangle2D> projectedTriangles;

    // Ajout des triangles projetés des cubes
    std::vector<Triangle2D> projectedCubes = getProjectedTrianglesFromCubes();
    projectedTriangles.insert(projectedTriangles.end(), projectedCubes.begin(), projectedCubes.end());

    // Ajout des triangles projetés des sphères
    std::vector<Triangle2D> projectedSpheres = getProjectedTrianglesFromSpheres();
    projectedTriangles.insert(projectedTriangles.end(), projectedSpheres.begin(), projectedSpheres.end());

    return projectedTriangles;
}

// Modifier la position de l'œil
void Scene3D::setEye(const Point3D& eye) {
    if (eye.distance(look_at_) < 1e-6) {
        throw std::invalid_argument("La position de l'œil et le point de visée ne peuvent pas être les mêmes.");
    }
    eye_ = eye;
}


// Modifier la direction de visée
void Scene3D::setLookAt(const Point3D& look_at) {
    look_at_ = look_at;
}

// Modifier la distance du plan de projection
void Scene3D::setProjectionPlaneDistance(float distance) {
    if (distance <= 0) {
        throw std::invalid_argument("La distance du plan de projection doit être strictement positive.");
    }
    projection_plane_distance_ = distance;
}

// Vide tous les objets de la scène
void Scene3D::clear() {
    cubes_.clear();
    spheres_.clear();
}

// Accesseur pour les cubes
const std::vector<std::shared_ptr<Pave3D>>& Scene3D::getCubes() const {
    return cubes_;
}

// Accesseur pour les sphères
const std::vector<std::shared_ptr<Sphere3D>>& Scene3D::getSpheres() const {
    return spheres_;
}