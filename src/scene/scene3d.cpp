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


// Récupère les triangles projetés
std::vector<Triangle2D> Scene3D::getProjectedTriangles() const {
    std::vector<Triangle2D> projectedTriangles;

    // Ajouter les triangles projetés des cubes
    for (const auto& cube : cubes_) {
        for (size_t i = 0; i < 6; ++i) { // Un pavé a toujours 6 faces
            const auto& face = cube->getFace(i);

            const Triangle3D& t1 = face.getFirstTriangle();
            const Triangle3D& t2 = face.getSecondTriangle();

            // Projection du premier triangle
            try {
                if (t1.isValid()) {
                    Point2D p1 = projectPoint(t1.getP1());
                    Point2D p2 = projectPoint(t1.getP2());
                    Point2D p3 = projectPoint(t1.getP3());

                    if (!Point2D::areCollinear(p1, p2, p3)) {
                        float depth = t1.averageDepth();
                        projectedTriangles.emplace_back(p1, p2, p3, face.getColor(), depth);
                    } else {
                        std::cerr << "Erreur : Les points projetés du triangle T1 sur la face " << i 
                                  << " forment une ligne droite en 2D.\n";
                    }
                }
            } catch (const std::exception& e) {
                std::cerr << "Erreur lors de la projection du triangle T1 : " << e.what() << "\n";
            }

            // Projection du deuxième triangle
            try {
                if (t2.isValid()) {
                    Point2D p1 = projectPoint(t2.getP1());
                    Point2D p2 = projectPoint(t2.getP2());
                    Point2D p3 = projectPoint(t2.getP3());

                    if (!Point2D::areCollinear(p1, p2, p3)) {
                        float depth = t2.averageDepth();
                        projectedTriangles.emplace_back(p1, p2, p3, face.getColor(), depth);
                    } else {
                        std::cerr << "Erreur : Les points projetés du triangle T2 sur la face " << i 
                                  << " forment une ligne droite en 2D.\n";
                    }
                }
            } catch (const std::exception& e) {
                std::cerr << "Erreur lors de la projection du triangle T2 : " << e.what() << "\n";
            }
        }
    }

    // Ajouter les triangles projetés des sphères
    for (const auto& sphere : spheres_) {
        const auto& quads = sphere->getQuads();
        for (const auto& quad : quads) {
            const Triangle3D& t1 = quad.getFirstTriangle();
            const Triangle3D& t2 = quad.getSecondTriangle();

            // Projection du premier triangle
            try {
                if (t1.isValid()) {
                    Point2D p1 = projectPoint(t1.getP1());
                    Point2D p2 = projectPoint(t1.getP2());
                    Point2D p3 = projectPoint(t1.getP3());

                    if (!Point2D::areCollinear(p1, p2, p3)) {
                        float depth = t1.averageDepth();
                        projectedTriangles.emplace_back(p1, p2, p3, quad.getColor(), depth);
                    } else {
                        std::cerr << "Erreur : Les points projetés du triangle T1 d'un quad de la sphère forment une ligne droite en 2D.\n";
                    }
                }
            } catch (const std::exception& e) {
                std::cerr << "Erreur lors de la projection du triangle T1 : " << e.what() << "\n";
            }

            // Projection du deuxième triangle
            try {
                if (t2.isValid()) {
                    Point2D p1 = projectPoint(t2.getP1());
                    Point2D p2 = projectPoint(t2.getP2());
                    Point2D p3 = projectPoint(t2.getP3());

                    if (!Point2D::areCollinear(p1, p2, p3)) {
                        float depth = t2.averageDepth();
                        projectedTriangles.emplace_back(p1, p2, p3, quad.getColor(), depth);
                    } else {
                        std::cerr << "Erreur : Les points projetés du triangle T2 d'un quad de la sphère forment une ligne droite en 2D.\n";
                    }
                }
            } catch (const std::exception& e) {
                std::cerr << "Erreur lors de la projection du triangle T2 : " << e.what() << "\n";
            }
        }
    }

    // Trier les triangles par profondeur moyenne (ordre décroissant)
    std::sort(projectedTriangles.begin(), projectedTriangles.end(), [](const Triangle2D& a, const Triangle2D& b) {
        return a.getDepth() > b.getDepth();
    });

    return projectedTriangles;
}

// Modifier la position de l'œil
void Scene3D::setEye(const Point3D& eye) {
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