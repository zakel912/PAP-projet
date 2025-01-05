#include "renderer.h"
#include <algorithm>
#include <stdexcept>

// Constructeur
Renderer::Renderer(int width, int height, int pixelSize)
    : width_(width), height_(height), pixelSize_(pixelSize) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        throw std::runtime_error("Erreur d'initialisation de SDL.");
    }
    window_ = SDL_CreateWindow("3D Renderer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width_, height_, SDL_WINDOW_SHOWN);
    if (!window_) {
        SDL_Quit();
        throw std::runtime_error("Erreur de création de la fenêtre SDL.");
    }
    renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer_) {
        SDL_DestroyWindow(window_);
        SDL_Quit();
        throw std::runtime_error("Erreur de création du renderer SDL.");
    }
}

// Destructeur
Renderer::~Renderer() {
    SDL_DestroyRenderer(renderer_);
    SDL_DestroyWindow(window_);
    SDL_Quit();
}

// Effacer l'écran
void Renderer::clear(const SDL_Color& color) {
    SDL_SetRenderDrawColor(renderer_, color.r, color.g, color.b, color.a);
    SDL_RenderClear(renderer_);
}

// Présenter le rendu
void Renderer::present() {
    SDL_RenderPresent(renderer_);
}

// Tri des triangles par profondeur
void Renderer::sortTrianglesByDepth(std::vector<Triangle2D>& triangles) const {
    std::sort(triangles.begin(), triangles.end(), [](const Triangle2D& a, const Triangle2D& b) {
        return a.getDepth() > b.getDepth();
    });
}

// Projection d'un point 3D
Point2D Renderer::projectPoint(const Point3D& point3D, const Point3D& eye, float projectionPlaneDistance) const {
    float dx = point3D.getX() - eye.getX();
    float dy = point3D.getY() - eye.getY();
    float dz = point3D.getZ() - eye.getZ();

    if (dz <= 0) {
        throw std::runtime_error("Projection impossible : le point est derrière l'œil.");
    }

    float scale = projectionPlaneDistance / dz;
    return Point2D(dx * scale + width_/2, dy * scale + height_/2);
}

// Projection d'un triangle 3D
Triangle2D Renderer::projectTriangle(const Triangle3D& triangle, const Point3D& eye, float projectionPlaneDistance) const {
    return Triangle2D(
        projectPoint(triangle.getP1(), eye, projectionPlaneDistance),
        projectPoint(triangle.getP2(), eye, projectionPlaneDistance),
        projectPoint(triangle.getP3(), eye, projectionPlaneDistance),
        triangle.getColor(),
        triangle.averageDepth()
    );
}

// Récupération des triangles projetés des cubes
std::vector<Triangle2D> Renderer::getProjectedTrianglesFromCubes(const Scene3D& scene) const {
    std::vector<Triangle2D> projectedTriangles;

    if (scene.hasCube()) {
        const auto& cube = scene.getCube();
        for (size_t i = 0; i < 6; ++i) { // Iterate over cube faces
            const auto& face = cube.getFace(i);
            const auto& t1 = face.getFirstTriangle();
            const auto& t2 = face.getSecondTriangle();

            projectedTriangles.push_back(projectTriangle(t1, scene.getEye(), scene.getProjectionPlaneDistance()));
            projectedTriangles.push_back(projectTriangle(t2, scene.getEye(), scene.getProjectionPlaneDistance()));
        }
    }

    return projectedTriangles;
}

// Récupération des triangles projetés des sphères
std::vector<Triangle2D> Renderer::getProjectedTrianglesFromSpheres(const Scene3D& scene) const {
    std::vector<Triangle2D> projectedTriangles;

    if (scene.hasSphere()) {
        const auto& sphere = scene.getSphere();
        for (const auto& quad : sphere.getQuads()) {
            const auto& t1 = quad.getFirstTriangle();
            const auto& t2 = quad.getSecondTriangle();

            projectedTriangles.push_back(projectTriangle(t1, scene.getEye(), scene.getProjectionPlaneDistance()));
            projectedTriangles.push_back(projectTriangle(t2, scene.getEye(), scene.getProjectionPlaneDistance()));
        }
    }

    return projectedTriangles;
}

// Culling des objets hors du champ de vision
bool Renderer::isPointVisible(const Point3D& point, const Point3D& eye) const {
    return point.getZ() > eye.getZ();
}

// Récupération de tous les triangles projetés
std::vector<Triangle2D> Renderer::getProjectedTriangles(const Scene3D& scene) const {
    auto triangles = getProjectedTrianglesFromCubes(scene);
    auto sphereTriangles = getProjectedTrianglesFromSpheres(scene);

    triangles.insert(triangles.end(), sphereTriangles.begin(), sphereTriangles.end());
    sortTrianglesByDepth(triangles);

    return triangles;
}

// Rendu de la scène
void Renderer::renderScene(const Scene3D& scene, const Point2D& translation2D) {
    auto projectedTriangles = getProjectedTriangles(scene);

    for (const auto& triangle : projectedTriangles) {
        // Dessiner le triangle
        const auto& p1 = triangle.getP1() + translation2D;
        const auto& p2 = triangle.getP2() + translation2D;
        const auto& p3 = triangle.getP3() + translation2D;

        const auto& color = triangle.getColor();

        SDL_SetRenderDrawColor(renderer_, color.getRouge(), color.getVert(), color.getBleu(), 255);
        SDL_RenderDrawLine(renderer_, p1.getX(), p1.getY(), p2.getX(), p2.getY());
        SDL_RenderDrawLine(renderer_, p2.getX(), p2.getY(), p3.getX(), p3.getY());
        SDL_RenderDrawLine(renderer_, p3.getX(), p3.getY(), p1.getX(), p1.getY());
    }
}

void Renderer::renderCube(const std::shared_ptr<Pave3D>& cube, const Point2D& translation,float translationZ, const Scene3D& scene) {
    for (size_t i = 0; i < 6; ++i) { // Parcourir toutes les faces du pavé
        const auto& face = cube->getFace(i);
        
        // Récupérer les deux triangles qui composent la face
        Triangle3D t1 = face.getFirstTriangle();
        Triangle3D t2 = face.getSecondTriangle();

        t1.applyTranslationZ(translationZ);
        t2.applyTranslationZ(translationZ);

        // Projeter les triangles en 2D
        auto triangle1 = projectTriangle(t1, scene.getEye(), scene.getProjectionPlaneDistance());
        auto triangle2 = projectTriangle(t2, scene.getEye(), scene.getProjectionPlaneDistance());

        // Appliquer la translation et dessiner le premier triangle
        const auto& p1 = triangle1.getP1() + translation;
        const auto& p2 = triangle1.getP2() + translation;
        const auto& p3 = triangle1.getP3() + translation;

        const auto& color1 = triangle1.getColor();

        SDL_SetRenderDrawColor(renderer_, color1.getRouge(), color1.getVert(), color1.getBleu(), 255);
        SDL_RenderDrawLine(renderer_, p1.getX(), p1.getY(), p2.getX(), p2.getY());
        SDL_RenderDrawLine(renderer_, p2.getX(), p2.getY(), p3.getX(), p3.getY());
        SDL_RenderDrawLine(renderer_, p3.getX(), p3.getY(), p1.getX(), p1.getY());

        // Appliquer la translation et dessiner le second triangle
        const auto& p4 = triangle2.getP1() + translation;
        const auto& p5 = triangle2.getP2() + translation;
        const auto& p6 = triangle2.getP3() + translation;

        const auto& color2 = triangle2.getColor();

        SDL_SetRenderDrawColor(renderer_, color2.getRouge(), color2.getVert(), color2.getBleu(), 255);
        SDL_RenderDrawLine(renderer_, p4.getX(), p4.getY(), p5.getX(), p5.getY());
        SDL_RenderDrawLine(renderer_, p5.getX(), p5.getY(), p6.getX(), p6.getY());
        SDL_RenderDrawLine(renderer_, p6.getX(), p6.getY(), p4.getX(), p4.getY());
    }
}

void Renderer::renderSphere(const std::shared_ptr<Sphere3D>& sphere, const Point2D& translation, float translationZ, const Scene3D& scene) {
    // Obtenez les quads de la sphère
    const auto& quads = sphere->getQuads();

    for (const auto& quad : quads) {
        // Récupérez les deux triangles qui forment le quad
        Triangle3D t1 = quad.getFirstTriangle();
        Triangle3D t2 = quad.getSecondTriangle();

        t1.applyTranslationZ(translationZ);
        t2.applyTranslationZ(translationZ);
        
        // Projetez les triangles en 2D
        auto triangle1 = projectTriangle(t1, scene.getEye(), scene.getProjectionPlaneDistance());
        auto triangle2 = projectTriangle(t2, scene.getEye(), scene.getProjectionPlaneDistance());

        // Appliquez la translation et dessinez le premier triangle
        const auto& p1 = triangle1.getP1() + translation;
        const auto& p2 = triangle1.getP2() + translation;
        const auto& p3 = triangle1.getP3() + translation;

        const auto& color1 = triangle1.getColor();

        SDL_SetRenderDrawColor(renderer_, color1.getRouge(), color1.getVert(), color1.getBleu(), 255);
        SDL_RenderDrawLine(renderer_, p1.getX(), p1.getY(), p2.getX(), p2.getY());
        SDL_RenderDrawLine(renderer_, p2.getX(), p2.getY(), p3.getX(), p3.getY());
        SDL_RenderDrawLine(renderer_, p3.getX(), p3.getY(), p1.getX(), p1.getY());

        // Appliquez la translation et dessinez le second triangle
        const auto& p4 = triangle2.getP1() + translation;
        const auto& p5 = triangle2.getP2() + translation;
        const auto& p6 = triangle2.getP3() + translation;

        const auto& color2 = triangle2.getColor();

        SDL_SetRenderDrawColor(renderer_, color2.getRouge(), color2.getVert(), color2.getBleu(), 255);
        SDL_RenderDrawLine(renderer_, p4.getX(), p4.getY(), p5.getX(), p5.getY());
        SDL_RenderDrawLine(renderer_, p5.getX(), p5.getY(), p6.getX(), p6.getY());
        SDL_RenderDrawLine(renderer_, p6.getX(), p6.getY(), p4.getX(), p4.getY());
    }
}