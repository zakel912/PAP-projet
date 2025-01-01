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

    validateGeometry();
}

// Constructeur paramétré
Pave3D::Pave3D(const std::array<Quad3D, 6>& faces, const Couleur& color)
    : faces(faces), color(color) {
    validateGeometry();
}

Pave3D::Pave3D(const Quad3D& front_quad, const Quad3D& back_quad, const Quad3D& left_quad, const Quad3D& right_quad, const Quad3D& top_quad, const Quad3D& bottom_quad, const Couleur& color)
    : faces{front_quad, back_quad, left_quad, right_quad, top_quad, bottom_quad}, color(color) {
}

// Constructeur par copie
Pave3D::Pave3D(const Pave3D& other)
    : faces(other.faces), color(other.color) {}

// Accesseur pour une face
const Quad3D& Pave3D::getFace(size_t index) const {
    if (index >= faces.size()) {
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
    if (rouge < 0 || rouge > 255 || vert < 0 || vert > 255 || bleu < 0 || bleu > 255) {
        throw std::invalid_argument("Les valeurs RVB doivent être comprises entre 0 et 255.");
    }
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
    static float cachedArea = -1.0f;  // Cache initial
    if (cachedArea < 0) {  // Si le cache n'est pas valide
        cachedArea = 0.0f;
        for (const auto& face : faces) {
            cachedArea += face.surface();
        }
    }
    return cachedArea;
}

// Validation de la géométrie du pavé
void Pave3D::validateGeometry() const {
    // Vérification des dimensions des faces opposées
    if (faces[0].surface() != faces[1].surface() ||
        faces[2].surface() != faces[3].surface() ||
        faces[4].surface() != faces[5].surface()) {
        std::cerr << "[Avertissement] Les faces opposées du pavé ne correspondent pas en surface.\n";
    }

    // Vérification des faces dégénérées
    for (size_t i = 0; i < faces.size(); ++i) {
        if (faces[i].getFirstTriangle().isDegenerate() || faces[i].getSecondTriangle().isDegenerate()) {
            std::cerr << "[Avertissement] La face " << i + 1 << " du pavé est dégénérée et sera ignorée dans le rendu.\n";
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