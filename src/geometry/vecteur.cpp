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