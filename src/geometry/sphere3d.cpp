#include "sphere3d.h"
#include <stdexcept>
#include <cmath>
#include <iostream>



// Constructeur avec centre, rayon, subdivisions et couleur RGB
Sphere3D::Sphere3D(const Point3D& center, float radius, int subdivisions, int rouge, int vert, int bleu)
    : center(center), radius(radius), subdivisions(subdivisions), color(Couleur(rouge, vert, bleu)) {
    if (radius <= 0) throw std::invalid_argument("Radius must be positive.");
    if (subdivisions <= 0) throw std::invalid_argument("Subdivisions must be positive.");
    generateQuads(subdivisions, subdivisions);
}

// Constructeur avec centre, couleur, rayon et subdivisions
Sphere3D::Sphere3D(const Point3D& center, const Couleur& color, float radius, int subdivisions)
    : center(center), radius(radius), subdivisions(subdivisions), color(color) {
    if (radius <= 0) throw std::invalid_argument("Radius must be positive.");
    if (subdivisions <= 0) throw std::invalid_argument("Subdivisions must be positive.");
    generateQuads(subdivisions, subdivisions);
}

// Accesseur pour le centre
const Point3D Sphere3D::getCenter() const {
    return center;
}

// Modificateur pour le centre
void Sphere3D::setCenter(const Point3D& newCenter) {
    center = newCenter;
    generateQuads(subdivisions, subdivisions);
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
    generateQuads(subdivisions, subdivisions);
}

// Accesseur pour les quadrilatères
const std::vector<Quad3D>& Sphere3D::getQuads() const {
    return quads;
}

// Modificateur pour la couleur (RVB)
void Sphere3D::setColor(int rouge, int vert, int bleu) {
    if (Couleur(rouge, vert, bleu) == color) return;
    color.setRouge(rouge);
    color.setVert(vert);
    color.setBleu(bleu);
    for (Quad3D& quad : quads) {
        quad.setColor(rouge, vert, bleu);
    }
}

// Modificateur pour la couleur (objet Couleur)
void Sphere3D::setColor(const Couleur& newColor) {
    setColor(newColor.getRouge(), newColor.getVert(), newColor.getBleu());
}

// Modificateur pour la composante rouge
void Sphere3D::setColorRouge(int rouge) {
    setColor(rouge, color.getVert(), color.getBleu());
}

// Modificateur pour la composante verte
void Sphere3D::setColorVert(int vert) {
    setColor(color.getRouge(), vert, color.getBleu());
}

// Modificateur pour la composante bleue
void Sphere3D::setColorBleu(int bleu) {
    setColor(color.getRouge(), color.getVert(), bleu);
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
void Sphere3D::generateQuads(int numSlices, int numStacks) {
    quads.clear();
    const float pi = M_PI;

    for (int i = 0; i < numStacks; ++i) {
        float theta1 = i * (pi / numStacks);
        float theta2 = (i + 1) * (pi / numStacks);

        for (int j = 0; j < numSlices; ++j) {
            float phi1 = j * (2 * pi / numSlices);
            float phi2 = (j + 1) * (2 * pi / numSlices);

            // Points calculés pour la grille
            Point3D p1(center.getX() + radius * sin(theta1) * cos(phi1),
                       center.getY() + radius * cos(theta1),
                       center.getZ() + radius * sin(theta1) * sin(phi1));

            Point3D p2(center.getX() + radius * sin(theta2) * cos(phi1),
                       center.getY() + radius * cos(theta2),
                       center.getZ() + radius * sin(theta2) * sin(phi1));

            Point3D p3(center.getX() + radius * sin(theta2) * cos(phi2),
                       center.getY() + radius * cos(theta2),
                       center.getZ() + radius * sin(theta2) * sin(phi2));

            Point3D p4(center.getX() + radius * sin(theta1) * cos(phi2),
                       center.getY() + radius * cos(theta1),
                       center.getZ() + radius * sin(theta1) * sin(phi2));

            // Ajouter un quadrilatère valide
            if (!(p1 == p2 || p2 == p3 || p3 == p4 || p4 == p1)) {
                quads.emplace_back(Quad3D(p1, p2, p3, p4, color));
            }
        }
    }
}