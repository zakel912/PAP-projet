#include "sphere3d.h"
#include <stdexcept>
#include <cmath>
#include <iostream>
#include "geometry_utils.h"

// Constructeur avec centre, rayon, subdivisions et couleur RGB
Sphere3D::Sphere3D(const Point3D& center, float radius, int subdivisions)
    : center(center), radius(radius), subdivisions(subdivisions) {
    if (radius <= 0) throw std::invalid_argument("Radius must be positive.");
    if (subdivisions <= 0) throw std::invalid_argument("Subdivisions must be positive.");
    generateQuads(subdivisions, subdivisions, Couleur(255,255,255));
}

// Accesseur pour le centre
const Point3D Sphere3D::getCenter() const {
    return center;
}

// Modificateur pour le centre
void Sphere3D::setCenter(const Point3D& newCenter) {
    center = newCenter;
    generateQuads(subdivisions, subdivisions, Couleur(255,255,255));
}

// Accesseur pour le rayon
float Sphere3D::getRadius() const {
    return radius;
}

// Modificateur pour le rayon
void Sphere3D::setRadius(float newRadius) {
    if (newRadius <= 0) {
        throw std::invalid_argument("The radius must be strictly positive.");
    }
    radius = newRadius;
    generateQuads(subdivisions, subdivisions, Couleur(255,255,255));
}

// Accesseur pour les quadrilatères
const std::vector<Quad3D>& Sphere3D::getQuads() const {
    return quads;
}

/**
 * @brief Modifie la couleur d'un quadrilatère spécifique.
 * @param index L'indice du quadrilatère.
 * @param color La nouvelle couleur.
 */
void Sphere3D::setQuadColor(int index, const Couleur& color) {
    if (index < 0 || index >= static_cast<int>(quads.size())) {
        throw std::out_of_range("Invalid quad index.");
    }
    quads[index].setColor(color);
}

/**
 * @brief Accesseur pour la couleur d'un quadrilatère spécifique.
 * @param index L'indice du quadrilatère.
 * @return La couleur du quadrilatère.
 */
Couleur Sphere3D::getQuadColor(int index) const {
    if (index < 0 || index >= static_cast<int>(quads.size())) {
        throw std::out_of_range("Invalid quad index.");
    }
    return quads[index].getColor();
}

// Calcul du volume de la sphère
float Sphere3D::volume() const {
    return (4.0f / 3.0f) * M_PI * std::pow(radius, 3);
}

// Calcul de la surface totale de la sphère
float Sphere3D::surfaceArea() const {
    return 4 * M_PI * std::pow(radius, 2);
}

// Génération des quadrilatères
void Sphere3D::generateQuads(int numSlices, int numStacks, const Couleur& color) {
    quads.clear();
    const float pi = M_PI;
    if (numSlices <= 0 || numStacks <= 0) {
        throw std::invalid_argument("numSlices et numStacks doivent être supérieurs à 0.");
    }

    auto computePoint = [this](float theta, float phi) -> Point3D {
        return Point3D(
            center.getX() + radius * sin(theta) * cos(phi),
            center.getY() + radius * cos(theta),
            center.getZ() + radius * sin(theta) * sin(phi)
        );
    };

    auto shouldSkipQuad = [](const Point3D& p1, const Point3D& p2, const Point3D& p3, const Point3D& p4) -> bool {
        return p1.distance(p2) < TOLERANCE || p2.distance(p3) < TOLERANCE || p3.distance(p4) < TOLERANCE || p4.distance(p1) < TOLERANCE;
    };

    for (int i = 0; i < numStacks; ++i) {
        float theta1 = i * (pi / numStacks);
        float theta2 = (i + 1) * (pi / numStacks);

        for (int j = 0; j < numSlices; ++j) {
            float phi1 = j * (2 * pi / numSlices);
            float phi2 = (j + 1) * (2 * pi / numSlices);

            Point3D p1 = computePoint(theta1, phi1);
            Point3D p2 = computePoint(theta2, phi1);
            Point3D p3 = computePoint(theta2, phi2);
            Point3D p4 = computePoint(theta1, phi2);

            if (shouldSkipQuad(p1, p2, p3, p4)) {
                continue;
            }

            quads.emplace_back(Quad3D(p1, p2, p3, p4, color));
        }
    }
    std::cout << quads.size() << " quads générés pour la sphère.\n";
}

void Sphere3D::rotate(float angle, char axis, const Point3D& origin) {
    for (auto& quad : quads) {
        quad.rotate(angle, axis, origin);
    }
}