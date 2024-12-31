#include "pave3d.h"
#include <stdexcept>
#include <iostream>

Pave3D::Pave3D()
    : front_quad(), back_quad(), left_quad(), right_quad(), top_quad(), bottom_quad(), color() {}

Pave3D::Pave3D(Quad3D front_quad, Quad3D back_quad, Quad3D left_quad, Quad3D right_quad, Quad3D top_quad, Quad3D bottom_quad, Couleur color)
    : front_quad(front_quad), back_quad(back_quad), left_quad(left_quad), right_quad(right_quad), top_quad(top_quad), bottom_quad(bottom_quad), color(color) {
    validateGeometry();
}

Pave3D::Pave3D(const Pave3D& other)
    : front_quad(other.front_quad), back_quad(other.back_quad), left_quad(other.left_quad),
      right_quad(other.right_quad), top_quad(other.top_quad), bottom_quad(other.bottom_quad), color(other.color) {}

Quad3D Pave3D::getFrontQuad() const {
    return front_quad;
}

Quad3D Pave3D::getBackQuad() const {
    return back_quad;
}

Quad3D Pave3D::getLeftQuad() const {
    return left_quad;
}

Quad3D Pave3D::getRightQuad() const {
    return right_quad;
}

Quad3D Pave3D::getTopQuad() const {
    return top_quad;
}

Quad3D Pave3D::getBottomQuad() const {
    return bottom_quad;
}

Couleur Pave3D::getColor() const {
    return color;
}

void Pave3D::setColor(const Couleur& newColor) {
    color = newColor;
    front_quad.setColor(newColor);
    back_quad.setColor(newColor);
    left_quad.setColor(newColor);
    right_quad.setColor(newColor);
    top_quad.setColor(newColor);
    bottom_quad.setColor(newColor);
}

void Pave3D::setColor(int rouge, int vert, int bleu) {
    setColor(Couleur(rouge, vert, bleu));
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

float Pave3D::volume() const {
    // Supposons que les dimensions du pavé sont définies par la longueur, la largeur et la hauteur :
    float length = front_quad.getFirstTriangle().getP1().distance(front_quad.getFirstTriangle().getP2());
    float width = front_quad.getFirstTriangle().getP2().distance(front_quad.getFirstTriangle().getP3());
    float height = front_quad.getFirstTriangle().getP1().distance(back_quad.getFirstTriangle().getP1());

    return length * width * height;
}

float Pave3D::surfaceArea() const {
    return 2 * (front_quad.surface() + left_quad.surface() + top_quad.surface());
}

// Validation de la géométrie du pavé
void Pave3D::validateGeometry() const {
    // Vérifiez que les dimensions des faces opposées correspondent.
    if (front_quad.surface() != back_quad.surface() ||
        left_quad.surface() != right_quad.surface() ||
        top_quad.surface() != bottom_quad.surface()) {
        throw std::runtime_error("Les faces opposées du pavé ne correspondent pas en surface.");
    }

    // Vérifiez l'alignement orthogonal des faces.
    // Cela nécessiterait des calculs supplémentaires basés sur les normales.
}

bool Pave3D::equals(const Pave3D& other) const {
    return front_quad.equals(other.front_quad) &&
           back_quad.equals(other.back_quad) &&
           left_quad.equals(other.left_quad) &&
           right_quad.equals(other.right_quad) &&
           top_quad.equals(other.top_quad) &&
           bottom_quad.equals(other.bottom_quad) &&
           color.equals(other.color);
}

std::ostream& operator<<(std::ostream& os, const Pave3D& pave) {
    os << "Pave3D : \n";
    os << "  Front face: " << pave.getFrontQuad() << "\n";
    os << "  Back face: " << pave.getBackQuad() << "\n";
    os << "  Left face: " << pave.getLeftQuad() << "\n";
    os << "  Right face: " << pave.getRightQuad() << "\n";
    os << "  Top face: " << pave.getTopQuad() << "\n";
    os << "  Bottom face: " << pave.getBottomQuad() << "\n";
    os << "  Color: " << pave.getColor() << "\n";
    return os;
}
