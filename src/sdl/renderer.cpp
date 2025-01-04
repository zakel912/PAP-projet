#include "renderer.h"
#include <stdexcept>
#include <algorithm>

// Constructeur
Renderer::Renderer(int width, int height, int pixelSize)
    : width_(width), height_(height), pixelSize_(pixelSize), window_(nullptr), renderer_(nullptr) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        throw std::runtime_error("Failed to initialize SDL");
    }

    window_ = SDL_CreateWindow("3D Renderer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width_, height_, SDL_WINDOW_SHOWN);
    if (!window_) {
        SDL_Quit();
        throw std::runtime_error("Failed to create SDL Window");
    }

    renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer_) {
        SDL_DestroyWindow(window_);
        SDL_Quit();
        throw std::runtime_error("Failed to create SDL Renderer");
    }
}

// Destructeur
Renderer::~Renderer() {
    if (renderer_) SDL_DestroyRenderer(renderer_);
    if (window_) SDL_DestroyWindow(window_);
    SDL_Quit();
}

// Effacer l'écran avec une couleur
void Renderer::clear(const SDL_Color& color) {
    SDL_SetRenderDrawColor(renderer_, color.r, color.g, color.b, color.a);
    SDL_RenderClear(renderer_);
}

// Dessiner un pixel
void Renderer::drawPixel(int x, int y, const SDL_Color& color) {
    SDL_SetRenderDrawColor(renderer_, color.r, color.g, color.b, color.a);
    SDL_Rect pixelRect = {x * pixelSize_, y * pixelSize_, pixelSize_, pixelSize_};
    SDL_RenderFillRect(renderer_, &pixelRect);
}

// Remplir un triangle
void Renderer::fillTriangle(const Triangle2D& triangle, const SDL_Color& color) {
    std::vector<Point2D> vertices = {triangle.getP1(), triangle.getP2(), triangle.getP3()};
    auto [minY, maxY] = std::minmax_element(vertices.begin(), vertices.end(),
                                            [](const Point2D& a, const Point2D& b) {
                                                return a.getY() < b.getY();
                                            });

    for (int y = minY->getY(); y <= maxY->getY(); ++y) {
        std::vector<int> xIntersections;

        for (size_t i = 0; i < vertices.size(); ++i) {
            const Point2D& current = vertices[i];
            const Point2D& next = vertices[(i + 1) % vertices.size()];

            if ((y > current.getY() && y <= next.getY()) ||
                (y <= current.getY() && y > next.getY())) {
                float dx = next.getX() - current.getX();
                float dy = next.getY() - current.getY();
                float slope = dx / dy;
                xIntersections.push_back(current.getX() + slope * (y - current.getY()));
            }
        }

        if (xIntersections.size() >= 2) {
            std::sort(xIntersections.begin(), xIntersections.end());
            for (int x = xIntersections[0]; x <= xIntersections[1]; ++x) {
                drawPixel(x, y, color);
            }
        }
    }
}

// Rendu de la scène
void Renderer::renderScene(const Scene3D& scene) {
    auto triangles = scene.getProjectedTriangles();
    for (const auto& triangle : triangles) {
        SDL_Color color = {
            static_cast<Uint8>(triangle.getColor().getRouge()),
            static_cast<Uint8>(triangle.getColor().getVert()),
            static_cast<Uint8>(triangle.getColor().getBleu()),
            255
        };
        fillTriangle(triangle, color);
    }
}

// Afficher le rendu
void Renderer::present() {
    SDL_RenderPresent(renderer_);
}
