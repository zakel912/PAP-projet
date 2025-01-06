#include "pave3d.h"
#include <stdexcept>
#include <iostream>

// Constructeur par défaut
Pave3D::Pave3D() {
    faces[0] = Quad3D(Point3D(0, 0, 0), Point3D(1, 0, 0), Point3D(1, 1, 0), Point3D(0, 1, 0), Couleur(255, 255, 255));
    faces[1] = Quad3D(Point3D(0, 0, 1), Point3D(1, 0, 1), Point3D(1, 1, 1), Point3D(0, 1, 1), Couleur(255, 255, 255));
    faces[2] = Quad3D(Point3D(0, 0, 0), Point3D(0, 1, 0), Point3D(0, 1, 1), Point3D(0, 0, 1), Couleur(255, 255, 255));
    faces[3] = Quad3D(Point3D(1, 0, 0), Point3D(1, 1, 0), Point3D(1, 1, 1), Point3D(1, 0, 1), Couleur(255, 255, 255));
    faces[4] = Quad3D(Point3D(0, 1, 0), Point3D(1, 1, 0), Point3D(1, 1, 1), Point3D(0, 1, 1), Couleur(255, 255, 255));
    faces[5] = Quad3D(Point3D(0, 0, 0), Point3D(1, 0, 0), Point3D(1, 0, 1), Point3D(0, 0, 1), Couleur(255, 255, 255));

    validateGeometry();
}

// Constructeur paramétré
Pave3D::Pave3D(const std::array<Quad3D, 6>& faces) : faces(faces) {
    validateGeometry();
}

Pave3D::Pave3D(const Quad3D& front_quad, const Quad3D& back_quad, const Quad3D& left_quad, const Quad3D& right_quad, const Quad3D& top_quad, const Quad3D& bottom_quad)
    : faces{front_quad, back_quad, left_quad, right_quad, top_quad, bottom_quad} {
}

Pave3D::Pave3D(const Point3D& origin, float length, float width, float height, const Couleur& color) {
    Point3D p1 = origin;
    Point3D p2 = origin + Point3D(length, 0, 0);
    Point3D p3 = origin + Point3D(length, width, 0);
    Point3D p4 = origin + Point3D(0, width, 0);

    Point3D p5 = origin + Point3D(0, 0, height);
    Point3D p6 = origin + Point3D(length, 0, height);
    Point3D p7 = origin + Point3D(length, width, height);
    Point3D p8 = origin + Point3D(0, width, height);

    faces[0] = Quad3D(p1, p2, p3, p4, color); // Bas
    faces[1] = Quad3D(p5, p6, p7, p8, color); // Haut
    faces[2] = Quad3D(p1, p4, p8, p5, color); // Gauche
    faces[3] = Quad3D(p2, p3, p7, p6, color); // Droite
    faces[4] = Quad3D(p1, p2, p6, p5, color); // Avant
    faces[5] = Quad3D(p4, p3, p7, p8, color); // Arrière

    validateGeometry();
}

// Constructeur par copie
Pave3D::Pave3D(const Pave3D& other) : faces(other.faces) {}

// Accesseur pour une face
const Quad3D& Pave3D::getFace(size_t index) const {
    if (index >= faces.size()) {
        throw std::out_of_range("Index hors limites pour les faces du pavé.");
    }
    return faces[index];
}

// Accesseur modifiable pour une face
Quad3D& Pave3D::getFace(size_t index) {
    if (index >= faces.size()) {
        throw std::out_of_range("Index hors limites pour les faces du pavé.");
    }
    return faces[index];
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
    static float cachedArea = -1.0f;
    if (cachedArea < 0) {
        cachedArea = 0.0f;
        for (const auto& face : faces) {
            cachedArea += face.surface();
        }
    }
    return cachedArea;
}

// Validation de la géométrie du pavé
void Pave3D::validateGeometry() const {

    if (faces[0].surface() != faces[1].surface() ||
        faces[2].surface() != faces[3].surface() ||
        faces[4].surface() != faces[5].surface()) {
        std::cerr << "[Avertissement] Les faces opposées du pavé ne correspondent pas en surface.\n";
    }

    for (size_t i = 0; i < faces.size(); ++i) {
        if (faces[i].getFirstTriangle().isDegenerate() || faces[i].getSecondTriangle().isDegenerate()) {
            std::cerr << "[Avertissement] La face " << i + 1 << " du pavé est dégénérée et sera ignorée dans le rendu.\n";
        }
    }
}

// Vérification d'égalité
bool Pave3D::equals(const Pave3D& other) const {
    return faces == other.faces;
}

void Pave3D::rotate(float angle, char axis, const Point3D& center) {
    for (auto& face : faces) {
        face.rotate(angle, axis, center);
    }
}

Point3D Pave3D::center() const {
    Point3D minPoint = faces[0].getFirstTriangle().getP1();
    Point3D maxPoint = minPoint;

    for (const auto& face : faces) {
        for (const auto& vertex : face.getVertices()) {
            minPoint.setX(std::min(minPoint.getX(), vertex.getX()));
            minPoint.setY(std::min(minPoint.getY(), vertex.getY()));
            minPoint.setZ(std::min(minPoint.getZ(), vertex.getZ()));

            maxPoint.setX(std::max(maxPoint.getX(), vertex.getX()));
            maxPoint.setY(std::max(maxPoint.getY(), vertex.getY()));
            maxPoint.setZ(std::max(maxPoint.getZ(), vertex.getZ()));
        }
    }
    return (minPoint + maxPoint) * 0.5f;
}

float Pave3D::averageDepth() const {
    float totalDepth = 0.0f;
    int vertexCount = 0;

    for (const auto& face : faces) {
        totalDepth += face.getFirstTriangle().averageDepth();
        totalDepth += face.getSecondTriangle().averageDepth();
        vertexCount += 6; // 3 sommets par triangle, 2 triangles par face
    }

    return totalDepth / vertexCount;
}

// Surcharge de l'opérateur de flux
std::ostream& operator<<(std::ostream& os, const Pave3D& pave) {
    os << "Pave3D :\n";
    for (size_t i = 0; i < pave.faces.size(); ++i) {
        os << "  Face " << i + 1 << ": " << pave.faces[i] << "\n";
    }
    return os;
}

// Calcule les faces visibles
std::vector<Quad3D> Pave3D::getVisibleFaces(const Point3D& eye) const {
    std::vector<Quad3D> visibleFaces;
    for (const auto& face : faces) {
        Point3D normal = face.getNormal();
        Point3D toEye = eye - face.center();

        if (normal.dotProduct(toEye) > 0) {
            visibleFaces.push_back(face);
        }
    }
    return visibleFaces;
}

// Définir la couleur d'une face
void Pave3D::setFaceColor(size_t index, const Couleur& color) {
    if (index >= faces.size()) {
        throw std::out_of_range("Index hors limites pour les faces du pavé.");
    }
    faces[index].setColor(color);
}

// Retourner la couleur d'une face
Couleur Pave3D::getFaceColor(size_t index) const {
    if (index >= faces.size()) {
        throw std::out_of_range("Index hors limites pour les faces du pavé.");
    }
    return faces[index].getColor();
}

void Pave3D::translate(const Point3D& offset, float projectionDistance) {
    for (auto& face : faces) {
        Triangle3D t1 = face.getFirstTriangle();
        Triangle3D t2 = face.getSecondTriangle();

        t1.setP1(t1.getP1().adjustedTranslation(offset, projectionDistance));
        t1.setP2(t1.getP2().adjustedTranslation(offset, projectionDistance));
        t1.setP3(t1.getP3().adjustedTranslation(offset, projectionDistance));

        t2.setP1(t2.getP1().adjustedTranslation(offset, projectionDistance));
        t2.setP2(t2.getP2().adjustedTranslation(offset, projectionDistance));
        t2.setP3(t2.getP3().adjustedTranslation(offset, projectionDistance));

        face = Quad3D(t1, t2);
    }
}

// Translate le pavé
void Pave3D::translate(const Point3D& offset) {
    for (auto& face : faces) {
        face.translate(offset);
    }
}