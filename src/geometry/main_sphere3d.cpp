#include <cassert>
#include <iostream>
#include "sphere3d.h"
#include "geometry_utils.h"

void testSphere3D() {
    // Points pour les tests
    Point3D center(0, 0, 0);
    float radius = 1.0f;
    int subdivisions = 5;

    // Test du constructeur par défaut
    Sphere3D defaultSphere;
    assert(defaultSphere.getCenter() == Point3D(0, 0, 0));
    assert(std::abs(defaultSphere.getRadius() - 1.0f) < TOLERANCE);
    assert(defaultSphere.getQuads().size() > 0); // La sphère doit être subdivisée en quadrilatères
    std::cout << "check1" << std::endl;

    // Test du constructeur paramétré
    Sphere3D sphere(center, radius, subdivisions);
    assert(sphere.getCenter() == center);
    assert(std::abs(sphere.getRadius() - radius) < TOLERANCE);
    assert(sphere.getQuads().size() > 0); // La sphère doit être subdivisée en quadrilatères
    std::cout << "check2" << std::endl;

    // Test des propriétés géométriques
    float expectedVolume = (4.0f / 3.0f) * M_PI * std::pow(radius, 3);
    float calculatedVolume = sphere.volume();
    assert(std::abs(calculatedVolume - expectedVolume) < TOLERANCE);
    std::cout << "check3 (volume)" << std::endl;

    float expectedSurfaceArea = 4.0f * M_PI * std::pow(radius, 2);
    float calculatedSurfaceArea = sphere.surfaceArea();
    assert(std::abs(calculatedSurfaceArea - expectedSurfaceArea) < TOLERANCE);
    std::cout << "check4 (surface area)" << std::endl;

    // Test de modification du centre
    Point3D newCenter(1, 1, 1);
    sphere.setCenter(newCenter);
    assert(sphere.getCenter() == newCenter);
    std::cout << "check5 (center modification)" << std::endl;

    // Test de modification du rayon
    float newRadius = 2.0f;
    sphere.setRadius(newRadius);
    assert(std::abs(sphere.getRadius() - newRadius) < TOLERANCE);

    expectedVolume = (4.0f / 3.0f) * M_PI * std::pow(newRadius, 3);
    calculatedVolume = sphere.volume();
    assert(std::abs(calculatedVolume - expectedVolume) < TOLERANCE);

    expectedSurfaceArea = 4.0f * M_PI * std::pow(newRadius, 2);
    calculatedSurfaceArea = sphere.surfaceArea();
    assert(std::abs(calculatedSurfaceArea - expectedSurfaceArea) < TOLERANCE);
    std::cout << "check6 (radius modification)" << std::endl;

    // Test des quadrilatères
    const auto& quads = sphere.getQuads();
    assert(!quads.empty()); // Les quadrilatères doivent exister
    std::cout << "check7 (quads existence)" << std::endl;

    // Test de modification de couleur d'un quadrilatère
    sphere.setQuadColor(0, Couleur(255, 0, 0));
    assert(sphere.getQuadColor(0) == Couleur(255, 0, 0));
    std::cout << "check8 (quad color modification)" << std::endl;

    // Test d'accès à un quadrilatère hors index
    try {
        sphere.getQuadColor(-1);
        assert(false); // Ne devrait pas atteindre cette ligne
    } catch (const std::out_of_range&) {
        std::cout << "check9 (out-of-range access)" << std::endl;
    }

    std::cout << "All Sphere3D tests passed!" << std::endl;
}

int main() {
    testSphere3D();
    return 0;
}
