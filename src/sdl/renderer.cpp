#include "renderer.h"
#include <stdexcept>
#include <algorithm>
#include <iostream>

Renderer::Renderer(int width, int height, int pixelSize)
    : width(width), height(height), pixelSize(pixelSize) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        throw std::runtime_error("Failed to initialize SDL.");
    }

    window = SDL_CreateWindow("3D Scene", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
    if (!window) {
        throw std::runtime_error("Failed to create SDL window.");
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        throw std::runtime_error("Failed to create SDL renderer.");
    }
}

Renderer::~Renderer() {
    if (renderer) {
        SDL_DestroyRenderer(renderer);
    }
    if (window) {
        SDL_DestroyWindow(window);
    }
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

template <typename T>
T clamp(T value, T min, T max) {
    return (value < min) ? min : (value > max) ? max : value;
}

void Renderer::fillTriangle(const Triangle2D& triangle, const SDL_Color& color) {
    // Récupération des sommets du triangle
    Point2D p1 = triangle.getP1();
    Point2D p2 = triangle.getP2();
    Point2D p3 = triangle.getP3();

    // Vérification des triangles dégénérés (les sommets doivent être distincts)
    if ((p1.getX() == p2.getX() && p1.getY() == p2.getY()) ||
        (p1.getX() == p3.getX() && p1.getY() == p3.getY()) ||
        (p2.getX() == p3.getX() && p2.getY() == p3.getY())) {
        std::cerr << "Triangle dégénéré ignoré." << std::endl;
        return;
    }

    // Tri des sommets par ordre croissant de la coordonnée Y
    if (p2.getY() < p1.getY()) std::swap(p1, p2);
    if (p3.getY() < p1.getY()) std::swap(p1, p3);
    if (p3.getY() < p2.getY()) std::swap(p2, p3);

    // Fonction pour interpoler les coordonnées X entre deux points
    auto interpolateX = [](int x1, int y1, int x2, int y2, int y) -> int {
        if (y1 == y2) return x1; // Évite la division par zéro
        return x1 + (x2 - x1) * (y - y1) / (y2 - y1);
    };

    // Dessin de la partie supérieure du triangle (entre p1 et p2)
    if (p2.getY() > p1.getY()) { // Évite les segments horizontaux
        for (int y = p1.getY(); y <= p2.getY(); ++y) {
            int xStart = interpolateX(p1.getX(), p1.getY(), p2.getX(), p2.getY(), y);
            int xEnd = interpolateX(p1.getX(), p1.getY(), p3.getX(), p3.getY(), y);
            if (xStart > xEnd) std::swap(xStart, xEnd);

            for (int x = xStart; x <= xEnd; ++x) {
                drawPixel(x, y, color);
            }
        }
    }

    // Dessin de la partie inférieure du triangle (entre p2 et p3)
    if (p3.getY() > p2.getY()) { // Évite les segments horizontaux
        for (int y = p2.getY(); y <= p3.getY(); ++y) {
            int xStart = interpolateX(p2.getX(), p2.getY(), p3.getX(), p3.getY(), y);
            int xEnd = interpolateX(p1.getX(), p1.getY(), p3.getX(), p3.getY(), y);
            if (xStart > xEnd) std::swap(xStart, xEnd);

            for (int x = xStart; x <= xEnd; ++x) {
                drawPixel(x, y, color);
            }
        }
    }
}

void Renderer::renderScene(const std::vector<Triangle2D>& triangles) {
    // Nettoyage de l'écran avec un fond noir
    clear({0, 0, 0, 255});

    // Tri des triangles par profondeur moyenne (z-sorting)
    auto sortedTriangles = triangles;
    std::sort(sortedTriangles.begin(), sortedTriangles.end(),
              [](const Triangle2D& a, const Triangle2D& b) {
                  return a.getDepth() > b.getDepth(); // Tri décroissant
              });

    for (const auto& triangle : sortedTriangles) {
        // Couleur du triangle
        Couleur color = triangle.getColor();
        SDL_Color sdlColor = {
            static_cast<Uint8>(clamp(color.getRouge(), 0, 255)),
            static_cast<Uint8>(clamp(color.getVert(), 0, 255)),
            static_cast<Uint8>(clamp(color.getBleu(), 0, 255)),
            255
        };

        // Remplissage du triangle
        fillTriangle(triangle, sdlColor);
    }

    // Présentation des pixels sur l'écran
    present();
}

void Renderer::present() {
    SDL_RenderPresent(renderer);
}
