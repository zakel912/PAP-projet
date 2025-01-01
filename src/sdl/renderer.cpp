#include "renderer.h"
#include <stdexcept>
#include <algorithm>

Renderer::Renderer(int width, int height, int pixelSize)
    : pixelSize(pixelSize), window(nullptr), renderer(nullptr) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        throw std::runtime_error("Failed to initialize SDL");
    }

    window = SDL_CreateWindow("3D Renderer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
    if (!window) {
        SDL_Quit();
        throw std::runtime_error("Failed to create SDL Window");
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer) {
        SDL_DestroyWindow(window);
        SDL_Quit();
        throw std::runtime_error("Failed to create SDL Renderer");
    }
}

Renderer::~Renderer() {
    if (renderer) SDL_DestroyRenderer(renderer);
    if (window) SDL_DestroyWindow(window);
    SDL_Quit();
}


void Renderer::clear(const SDL_Color& color) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderClear(renderer);
}


void Renderer::drawPixel(int x, int y, const SDL_Color& color) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_Rect pixelRect = {x * pixelSize, y * pixelSize, pixelSize, pixelSize};
    SDL_RenderFillRect(renderer, &pixelRect);
}

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

void Renderer::renderScene(const std::vector<Triangle2D>& triangles) {
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


void Renderer::present() {
    SDL_RenderPresent(renderer);
}
