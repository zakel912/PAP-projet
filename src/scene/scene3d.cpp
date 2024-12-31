#include "scene3d.h"
#include <algorithm>
#include <stdexcept>

// Constructeur
Scene3D::Scene3D(const Point3D& eye, const Point3D& look_at, float projection_plane_distance)
    : eye_(eye), look_at_(look_at), projection_plane_distance_(projection_plane_distance) {
    if (projection_plane_distance_ <= 0) {
        throw std::invalid_argument("La distance du plan de projection doit être strictement positive.");
    }
}

// Ajout d'un cube à la scène
void Scene3D::addCube(const std::shared_ptr<Pave3D>& cube) {
    cubes_.push_back(cube);
}

// Ajout d'une sphère à la scène
void Scene3D::addSphere(const std::shared_ptr<Sphere3D>& sphere) {
    spheres_.push_back(sphere);
}

// Projection d'un point 3D sur un plan 2D
Point2D Scene3D::projectPoint(const Point3D& point3D) const {
    // Calcul de la projection perspective
    float dx = point3D.getX() - eye_.getX();
    float dy = point3D.getY() - eye_.getY();
    float dz = point3D.getZ() - eye_.getZ();

    float scale = projection_plane_distance_ / dz;
    float x = dx * scale;
    float y = dy * scale;

    return Point2D(x, y);
}

// Récupère les triangles projetés
std::vector<Triangle2D> Scene3D::getProjectedTriangles() const {
    std::vector<Triangle2D> projectedTriangles;

    // Ajouter les triangles projetés des cubes
    for (const auto& cube : cubes_) {
        std::vector<Quad3D> quads = {cube->getFrontQuad(), cube->getBackQuad(),
                                     cube->getLeftQuad(), cube->getRightQuad(),
                                     cube->getTopQuad(), cube->getBottomQuad()};

        for (const auto& quad : quads) {
            const Triangle3D& t1 = quad.getFirstTriangle();
            const Triangle3D& t2 = quad.getSecondTriangle();

            // Créer les triangles 2D à partir des projections
            projectedTriangles.emplace_back(projectPoint(t1.getP1()), projectPoint(t1.getP2()), projectPoint(t1.getP3()), t1.getColor());
            projectedTriangles.emplace_back(projectPoint(t2.getP1()), projectPoint(t2.getP2()), projectPoint(t2.getP3()), t2.getColor());
        }
    }

    // Ajouter les triangles projetés des sphères
    for (const auto& sphere : spheres_) {
        const auto& quads = sphere->getQuads();
        for (const auto& quad : quads) {
            const Triangle3D& t1 = quad.getFirstTriangle();
            const Triangle3D& t2 = quad.getSecondTriangle();

            projectedTriangles.emplace_back(projectPoint(t1.getP1()), projectPoint(t1.getP2()), projectPoint(t1.getP3()), t1.getColor());
            projectedTriangles.emplace_back(projectPoint(t2.getP1()), projectPoint(t2.getP2()), projectPoint(t2.getP3()), t2.getColor());
        }
    }

    // Trier les triangles par profondeur moyenne
    std::sort(projectedTriangles.begin(), projectedTriangles.end(), [](const Triangle2D& a, const Triangle2D& b) {
        return a.averageDepth() > b.averageDepth();
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

// Vider tous les objets de la scène
void Scene3D::clear() {
    cubes_.clear();
    spheres_.clear();
}
