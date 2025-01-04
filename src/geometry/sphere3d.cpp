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

    // Constants for calculations
    const float pi = M_PI;

    // Ensure valid input for slices and stacks
    if (numSlices <= 0 || numStacks <= 0) {
        throw std::invalid_argument("numSlices and numStacks must be greater than 0.");
    }

    // Loop through stacks and slices to generate the sphere quads
    for (int i = 0; i < numStacks; ++i) {
        float theta1 = i * (pi / numStacks);        // Starting angle for this stack
        float theta2 = (i + 1) * (pi / numStacks);  // Ending angle for this stack

        for (int j = 0; j < numSlices; ++j) {
            float phi1 = j * (2 * pi / numSlices);        // Starting angle for this slice
            float phi2 = (j + 1) * (2 * pi / numSlices);  // Ending angle for this slice

            // Calculate the four points for this quad
            Point3D p1(
                center.getX() + radius * sin(theta1) * cos(phi1),
                center.getY() + radius * cos(theta1),
                center.getZ() + radius * sin(theta1) * sin(phi1)
            );

            Point3D p2(
                center.getX() + radius * sin(theta2) * cos(phi1),
                center.getY() + radius * cos(theta2),
                center.getZ() + radius * sin(theta2) * sin(phi1)
            );

            Point3D p3(
                center.getX() + radius * sin(theta2) * cos(phi2),
                center.getY() + radius * cos(theta2),
                center.getZ() + radius * sin(theta2) * sin(phi2)
            );

            Point3D p4(
                center.getX() + radius * sin(theta1) * cos(phi2),
                center.getY() + radius * cos(theta1),
                center.getZ() + radius * sin(theta1) * sin(phi2)
            );

            // Validate that points are not degenerate
            if (p1.distance(p2) < TOLERANCE || p2.distance(p3) < TOLERANCE ||
                p3.distance(p4) < TOLERANCE || p4.distance(p1) < TOLERANCE) {
                continue; // Skip degenerate quads
            }

            // Add the quad
            quads.emplace_back(Quad3D(p1, p2, p3, p4, color));
        }
    }

    std::cout << "Generated " << quads.size() << " quads for the sphere.\n";
}
