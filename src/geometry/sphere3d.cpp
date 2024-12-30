#include "sphere3d.h"

// Constructeur
Sphere3D::Sphere3D(const Point3D& center, float radius, int subdivisions)
    : center_(center), radius_(radius), subdivisions_(subdivisions) {
    if (radius <= 0) {
        throw std::invalid_argument("Le rayon doit être positif.");
    }
    if (subdivisions <= 0) {
        throw std::invalid_argument("Le nombre de subdivisions doit être supérieur à zéro.");
    }
    generateQuads();
}

// Accesseur pour le centre
Point3D Sphere3D::getCenter() const {
    return center_;
}

// Modificateur pour le centre
void Sphere3D::setCenter(const Point3D& center) {
    center_ = center;
    generateQuads(); // Recalculer les quadrilatères
}

// Accesseur pour le rayon
float Sphere3D::getRadius() const {
    return radius_;
}

// Modificateur pour le rayon
void Sphere3D::setRadius(float radius) {
    if (radius <= 0) {
        throw std::invalid_argument("Le rayon doit être positif.");
    }
    radius_ = radius;
    generateQuads(); // Recalculer les quadrilatères
}

// Accesseur pour les quadrilatères
const std::vector<Quad3D>& Sphere3D::getQuads() const {
    return quads_;
}

// Calcul du volume
float Sphere3D::volume() const {
    return (4.0f / 3.0f) * static_cast<float>(M_PI) * std::pow(radius_, 3);
}

// Calcul de la surface
float Sphere3D::surfaceArea() const {
    return 4.0f * static_cast<float>(M_PI) * std::pow(radius_, 2);
}

// Génération des quadrilatères
void Sphere3D::generateQuads() {
    quads_.clear();

    // Approche basée sur les coordonnées sphériques
    float dTheta = static_cast<float>(M_PI) / subdivisions_;      // Divisions en latitude
    float dPhi = 2.0f * static_cast<float>(M_PI) / subdivisions_; // Divisions en longitude

    for (int i = 0; i < subdivisions_; ++i) {
        float theta1 = i * dTheta;
        float theta2 = (i + 1) * dTheta;

        for (int j = 0; j < subdivisions_; ++j) {
            float phi1 = j * dPhi;
            float phi2 = (j + 1) * dPhi;

            // Calcul des sommets des quadrilatères
            Point3D p1(center_.getX() + radius_ * std::sin(theta1) * std::cos(phi1),
                       center_.getY() + radius_ * std::sin(theta1) * std::sin(phi1),
                       center_.getZ() + radius_ * std::cos(theta1));

            Point3D p2(center_.getX() + radius_ * std::sin(theta2) * std::cos(phi1),
                       center_.getY() + radius_ * std::sin(theta2) * std::sin(phi1),
                       center_.getZ() + radius_ * std::cos(theta2));

            Point3D p3(center_.getX() + radius_ * std::sin(theta2) * std::cos(phi2),
                       center_.getY() + radius_ * std::sin(theta2) * std::sin(phi2),
                       center_.getZ() + radius_ * std::cos(theta2));

            Point3D p4(center_.getX() + radius_ * std::sin(theta1) * std::cos(phi2),
                       center_.getY() + radius_ * std::sin(theta1) * std::sin(phi2),
                       center_.getZ() + radius_ * std::cos(theta1));

            // Ajouter le quadrilatère
            quads_.emplace_back(p1, p2, p3, p4);
        }
    }
}
