#include "vecteur.cpp"

Vecteur::Vecteur(const Point3D& origine, const Point3D& extremite){
    if(origine.equals(extremite)){
        throw std::invalid_argument("Le point d'origine et le point d'extrémité ne peuvent pas être les mêmes.");
    }
    this->origine = origine;
    this->extremite = extremite;
}

Vecteur::Vecteur(const Vecteur& other){
    Vecteur(other.getOrigine(), other.getExtremite());
}

Vecteur:: Point3D getOrigine() const{
    return origine;
}

Vecteur:: Point3D getExtremite() const{
    return extremite;
}

Vecteur:: float norm() const{
    return origine.distance(extremite);
}

Vecteur:: float dotProduct(const Vecteur& other) const{
    Point3D u = extremite - origine;
    Point3D v = other.getExtremite() - other.getOrigine();
    return u.dotProduct(v);
}

float Vecteur::distanceToPlane(const Point3D& point) const {
    Point3D u = extremite - origine;
    float d = -u.dotProduct(origine);
    float dist = fabs(u.dotProduct(point) + d) / u.norm();
    return dist;
}

float Vecteur::distanceToPlane(const Pave3D& pave) const {
    std::array<Quad3D, 6> faces = pave.getFaces();
    float minDist = distanceToPlane(faces[0]);
    for (int i = 1; i < 6; i++) {
        float dist = distanceToPlane(faces[i]);
        if (dist < minDist) {
            minDist = dist;
        }
    }
    return minDist;
}

bool Vecteur::isPointInFront(const Point3D& point) const{
    Point3D u = origine - point;

    //normale au plan
    Point3D n = origine - extremite;

    if (u.dotProduct(n) > 0){
        return true;
    }
    return false;

}

bool Vecteur::isPaveVisible(const Pave3D& pave) const {
    for (const auto& face : pave.getFaces()) {
        if (isTriangleVisible(face.getFirstTriangle()) || isTriangleVisible(face.getSecondTriangle())) {
            return true;
        }
    }
    return false;
}

bool Vecteur::IsSphereVisible(const Sphere3D& sphere) const {
    Point3D center = sphere.getCenter();
    float radius = sphere.getRadius();
    float dist = distanceToPlane(center);
    float dot = (center - origine).dotProduct(extremite - origine);
    return dist < radius && dot > 0;
}

Vecteur& Vecteur::operator=(const Vecteur& other){
    origine = other.getOrigine();
    extremite = other.getExtremite();
    return *this;
}

Point2D Vecteur::projectPoint(const Point3D& point, int width, int height) const {

    if (widgt <= 0 || height <= 0) {
        throw std::invalid_argument("La largeur et la hauteur doivent être positives.");
    }

    // Projection du point sur le plan
    Point3D n = extremite - origine;
    Point3D n_normalise = n / n.norm();
    Point3D p_projet = point - distanceToPlane(point) * n_normalise;

    // Projection du point sur l'écran
    // Création des axes locaux
    // Rotation d'angle 30° de n par rapport à l'axe des x
    double angle = 30 * M_PI / 180; // Conversion de 30 degrés en radians
    double cosAngle = cos(angle);
    double sinAngle = sin(angle);
    Point3D n_rot(n.getX(), cosAngle * n.getY() - sinAngle * n.getZ(), sinAngle * n.getY() + cosAngle * n.getZ());
    Point3D axe_u = n_rot - distanceToPlane(n_rot) * n_normalise;
    Point3D axe_u_normalise = axe_u / axe_u.norm();

    // Axe v = n x u
    Point3D axe_v = n.crossProduct(axe_u_normalise);

    // Projection du point sur le plan
    float x = p_projet.dotProduct(axe_u_normalise);
    float y = p_projet.dotProduct(axe_v);

    // Projection sur l'écran
    float x_ecran = (x + 1) * width / 2;

    // L'axe des y est inversé
    float y_ecran = height - (y + 1) * height / 2;

    return Point2D(static_cast<int>(x_ecran), static_cast<int>(y_ecran));
}

Triangle2D Vecteur::projectTriangle(const Triangle3D& triangle, int width, int height) const {
    Point2D p1 = projectPoint(triangle.getPoint1(), width, height);
    Point2D p2 = projectPoint(triangle.getPoint2(), width, height);
    Point2D p3 = projectPoint(triangle.getPoint3(), width, height);
    return Triangle2D(p1, p2, p3, triangle.getColor(), distanceToPlane(triangle));
}