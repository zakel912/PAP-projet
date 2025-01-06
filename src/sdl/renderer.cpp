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
        // std::cout << "Projection impossible : le point est derrière l'œil.\n";
        throw std::runtime_error("Projection impossible : le point est derrière l'œil.\n");
    }

    float scale = projectionPlaneDistance / (projectionPlaneDistance + dz);
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
        for (size_t i = 0; i < 6; ++i) {
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

// Fonction pour rendre un triangle avec translation et projection
void Renderer::renderTriangle(const Triangle3D& triangle, const Couleur& color, const Point2D& translation, float translationZ, const Scene3D& scene) {
    Triangle3D transformedTriangle = triangle;
    transformedTriangle.applyTranslationZ(translationZ);

    Point2D p1 = projectPoint(transformedTriangle.getP1(), scene.getEye(), scene.getProjectionPlaneDistance()) + translation;
    Point2D p2 = projectPoint(transformedTriangle.getP2(), scene.getEye(), scene.getProjectionPlaneDistance()) + translation;
    Point2D p3 = projectPoint(transformedTriangle.getP3(), scene.getEye(), scene.getProjectionPlaneDistance()) + translation;

    drawFilledTriangle(renderer_, p1, p2, p3, color);
}

// Render a single triangle with calculated color
void Renderer::renderTriangleWithColor(const Triangle3D& triangle, const Point2D& translation, float translationZ, const Scene3D& scene) {
    Triangle3D transformedTriangle = triangle;
    transformedTriangle.applyTranslationZ(translationZ);

    // Projeter les sommets et appliquer la translation 2D
    Point2D p1 = projectPoint(transformedTriangle.getP1(), scene.getEye(), scene.getProjectionPlaneDistance()) + translation;
    Point2D p2 = projectPoint(transformedTriangle.getP2(), scene.getEye(), scene.getProjectionPlaneDistance()) + translation;
    Point2D p3 = projectPoint(transformedTriangle.getP3(), scene.getEye(), scene.getProjectionPlaneDistance()) + translation;

    Couleur faceColor = computeTriangleColor(transformedTriangle);

    drawFilledTriangle(renderer_, p1, p2, p3, faceColor);
}

// Compute color for a triangle based on its centroid
Couleur Renderer::computeTriangleColor(const Triangle3D& triangle) const {
    Point3D centroid = triangle.getCentroid();

    float xyExcentricity = std::sqrt(centroid.getX() * centroid.getX() + centroid.getY() * centroid.getY());
    float zClarity = std::abs(centroid.getZ());
    float yHeight = std::abs(centroid.getY());

    float maxXY = 100.0f;
    float maxY = 100.0f;
    float maxZ = 100.0f;

    float xyFactor = std::clamp((xyExcentricity / maxXY), 0.0f, 1.0f);
    float yFactor = std::clamp(1.0f - (yHeight / maxY), 0.0f, 1.0f);
    float zFactor = std::clamp((zClarity / maxZ), 0.0f, 1.0f);

    int redIntensity = static_cast<int>(0 * yFactor);
    int greenIntensity = static_cast<int>(255 * (yFactor + xyFactor + zFactor) / 3.0f);
    int blueIntensity = static_cast<int>(0 * zFactor);

    return Couleur(redIntensity, greenIntensity, blueIntensity);
}

// Fonction pour dessiner un triangle rempli
void Renderer::drawFilledTriangle(SDL_Renderer* renderer, const Point2D& p1, const Point2D& p2, const Point2D& p3, const Couleur& color) {
    SDL_SetRenderDrawColor(renderer, color.getRouge(), color.getVert(), color.getBleu(), 255);

    auto interpolate = [](int y1, int x1, int y2, int x2, int y) -> int {
        if (y2 == y1) return x1;
        return x1 + (x2 - x1) * (y - y1) / (y2 - y1);
    };

    // Trier les sommets par coordonnée Y
    Point2D sorted[3] = {p1, p2, p3};
    std::sort(sorted, sorted + 3, [](const Point2D& a, const Point2D& b) { return a.getY() < b.getY(); });

    const Point2D& pTop = sorted[0];
    const Point2D& pMiddle = sorted[1];
    const Point2D& pBottom = sorted[2];

    // Dessiner la partie supérieure
    for (int y = pTop.getY(); y <= pMiddle.getY(); ++y) {
        int xStart = interpolate(pTop.getY(), pTop.getX(), pMiddle.getY(), pMiddle.getX(), y);
        int xEnd = interpolate(pTop.getY(), pTop.getX(), pBottom.getY(), pBottom.getX(), y);
        if (xStart > xEnd) std::swap(xStart, xEnd);
        SDL_RenderDrawLine(renderer, xStart, y, xEnd, y);
    }

    // Dessiner la partie inférieure
    for (int y = pMiddle.getY(); y <= pBottom.getY(); ++y) {
        int xStart = interpolate(pMiddle.getY(), pMiddle.getX(), pBottom.getY(), pBottom.getX(), y);
        int xEnd = interpolate(pTop.getY(), pTop.getX(), pBottom.getY(), pBottom.getX(), y);
        if (xStart > xEnd) std::swap(xStart, xEnd);
        SDL_RenderDrawLine(renderer, xStart, y, xEnd, y);
    }
}

// Rendu d'un cube
void Renderer::renderCube(const std::shared_ptr<Pave3D>& cube, const Point2D& translation, float translationZ, const Scene3D& scene) {
    std::vector<std::pair<float, const Quad3D*>> faceDepths;
    
    for (size_t i = 0; i < 6; ++i) {
        const Quad3D& face = cube->getFace(i);
        faceDepths.emplace_back(face.averageDepth(), &face);
    }
    std::sort(faceDepths.begin(), faceDepths.end(), std::greater<>());

    float maxDepth = std::max_element(faceDepths.begin(), faceDepths.end(), [](const auto& a, const auto& b) {
        return a.first < b.first;
    })->first;

    for (const auto& [depth, face] : faceDepths) {
        float normalizedDepth = std::clamp(depth / maxDepth, 0.0f, 1.0f);
        int redIntensity = static_cast<int>(255 * (1 - normalizedDepth));
        Couleur faceColor(redIntensity, 0, 0);
        renderTriangle(face->getFirstTriangle(), faceColor, translation, translationZ, scene);
        renderTriangle(face->getSecondTriangle(), faceColor, translation, translationZ, scene);
    }
}

// Rendu d'une sphère
void Renderer::renderSphere(const std::shared_ptr<Sphere3D>& sphere, const Point2D& translation, float translationZ, const Scene3D& scene) {

    std::vector<std::pair<float, const Quad3D*>> faceDepths;

    for (const auto& quad : sphere->getQuads()) {
        faceDepths.emplace_back(quad.averageDepth(), &quad);
    }
    std::sort(faceDepths.begin(), faceDepths.end(), std::greater<>());

    for (const auto& [depth, face] : faceDepths) {
        renderTriangleWithColor(face->getFirstTriangle(), translation, translationZ, scene);
        renderTriangleWithColor(face->getSecondTriangle(), translation, translationZ, scene);
    }
}