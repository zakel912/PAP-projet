#include "pave3d.h"
#include <stdexcept>
#include <iostream>

// Constructeur par défaut
Pave3D::Pave3D()
    : color(Couleur()) {
    faces[0] = Quad3D(Point3D(0, 0, 0), Point3D(1, 0, 0), Point3D(1, 1, 0), Point3D(0, 1, 0), color);
    faces[1] = Quad3D(Point3D(0, 0, 1), Point3D(1, 0, 1), Point3D(1, 1, 1), Point3D(0, 1, 1), color);
    faces[2] = Quad3D(Point3D(0, 0, 0), Point3D(0, 1, 0), Point3D(0, 1, 1), Point3D(0, 0, 1), color);
    faces[3] = Quad3D(Point3D(1, 0, 0), Point3D(1, 1, 0), Point3D(1, 1, 1), Point3D(1, 0, 1), color);
    faces[4] = Quad3D(Point3D(0, 1, 0), Point3D(1, 1, 0), Point3D(1, 1, 1), Point3D(0, 1, 1), color);
    faces[5] = Quad3D(Point3D(0, 0, 0), Point3D(1, 0, 0), Point3D(1, 0, 1), Point3D(0, 0, 1), color);
}

// Constructeur paramétré
Pave3D::Pave3D(const std::array<Quad3D, 6>& faces, const Couleur& color)
    : faces(faces), color(color) {
    for (auto& face : this->faces) {
        face.setColor(color);
    }
    validateGeometry();
}

Pave3D::Pave3D(Quad3D front_quad, Quad3D back_quad, Quad3D left_quad, Quad3D right_quad, Quad3D top_quad, Quad3D bottom_quad, Couleur color)
    : Pave3D({front_quad, back_quad, left_quad, right_quad, top_quad, bottom_quad}, color) {}

// Constructeur par copie
Pave3D::Pave3D(const Pave3D& other)
    : Pave3D(other.getFaces(), other.getColor()) {}

// Accesseur pour une face
const Quad3D& Pave3D::getFace(size_t index) const {
    if (index >= faces.size() || index < 0) {
        throw std::out_of_range("Index hors limites pour les faces du pavé.");
    }
    return faces[index];
}

// Modificateur pour la couleur
void Pave3D::setColor(const Couleur& newColor) {
    color = newColor;
    for (auto& face : faces) {
        face.setColor(newColor);
    }
}

// Modificateur pour la couleur avec RVB
void Pave3D::setColor(int rouge, int vert, int bleu) {
    color.setRouge(rouge);
    color.setVert(vert);
    color.setBleu(bleu);
    for (auto& face : faces) {
        face.setColor(rouge, vert, bleu);
    }
}

void Pave3D::setColorRouge(int rouge) {
    setColor(rouge, color.getVert(), color.getBleu());
}

void Pave3D::setColorVert(int vert) {
    setColor(color.getRouge(), vert, color.getBleu());
}

void Pave3D::setColorBleu(int bleu) {
    setColor(color.getRouge(), color.getVert(), bleu);
}

// Calcul du volume
float Pave3D::volume() const {
    float length = faces[0].getFirstTriangle().getP1().distance(faces[0].getFirstTriangle().getP2());
    float width = faces[0].getFirstTriangle().getP2().distance(faces[0].getFirstTriangle().getP3());
    float height = faces[0].getFirstTriangle().getP1().distance(faces[1].getFirstTriangle().getP1());

    if (length <= 0 || width <= 0 || height <= 0) {
        throw std::runtime_error("Dimensions invalides pour le pavé.");
    }

    return length * width * height;
}

// Calcul de la surface totale
float Pave3D::surfaceArea() const {
    float area = 0.0f;
    for (const auto& face : faces) {
        area += face.surface();
    }
    return area;
}

// Validation de la géométrie du pavé
void Pave3D::validateGeometry() const {
    // Vérifiez que les faces opposées sont égales en surface
    if (faces[0].surface() != faces[1].surface() ||
        faces[2].surface() != faces[3].surface() ||
        faces[4].surface() != faces[5].surface()) {
        throw std::runtime_error("Les faces opposées du pavé ne correspondent pas en surface.");
    }

    // Vérifiez que les faces ne sont pas dégénérées
    for (const auto& face : faces) {
        if (face.getFirstTriangle().isDegenerate() || face.getSecondTriangle().isDegenerate()) {
            throw std::runtime_error("Une des faces du pavé est dégénérée.");
        }
    }
}

// Vérification d'égalité
bool Pave3D::equals(const Pave3D& other) const {
    return faces == other.faces && color.equals(other.color);
}

// Surcharge de l'opérateur de flux
std::ostream& operator<<(std::ostream& os, const Pave3D& pave) {
    os << "Pave3D :\n";
    for (size_t i = 0; i < pave.faces.size(); ++i) {
        os << "  Face " << i + 1 << ": " << pave.faces[i] << "\n";
    }
    os << "  Color: " << pave.getColor() << "\n";
    return os;
}