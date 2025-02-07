#include <SDL2/SDL.h>
#include <iostream>
#include <algorithm>
#include "../pave3d.h"
#include "../point3d.h"
#include "../point2d.h"
#include "../quad3d.h"
#include "../../couleur.h"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const float PROJECTION_DISTANCE = 300.0f;
const int MOVE_STEP = 10;
const float ROTATE_STEP = 0.1f;

Point2D projectPoint(const Point3D& point3D) {
    float denominator = PROJECTION_DISTANCE + point3D.getZ();
    if (denominator == 0) {
        throw std::runtime_error("Division par zéro lors de la projection.");
    }
    float scale = PROJECTION_DISTANCE / denominator;
    return Point2D(static_cast<int>(point3D.getX() * scale + SCREEN_WIDTH / 2),
                   static_cast<int>(-point3D.getY() * scale + SCREEN_HEIGHT / 2));
}

void renderPave(SDL_Renderer* renderer, const Pave3D& pave, const Point3D& cameraPosition, const Point2D& translation2D) {
    std::vector<std::pair<float, const Quad3D*>> faceDepths;

    for (size_t i = 0; i < 6; ++i) {
        const Quad3D& face = pave.getFace(i);
        faceDepths.emplace_back(face.averageDepth(), &face);
    }
    std::sort(faceDepths.begin(), faceDepths.end(), std::greater<>());

    auto renderTriangle = [&](const Triangle3D& triangle, const Couleur& color) {
        Point2D p1 = projectPoint(triangle.getP1()) + translation2D;
        Point2D p2 = projectPoint(triangle.getP2()) + translation2D;
        Point2D p3 = projectPoint(triangle.getP3()) + translation2D;

        if (p2.getY() < p1.getY()) std::swap(p1, p2);
        if (p3.getY() < p1.getY()) std::swap(p1, p3);
        if (p3.getY() < p2.getY()) std::swap(p2, p3);

        SDL_SetRenderDrawColor(renderer, color.getRouge(), color.getVert(), color.getBleu(), 255);
        auto interpolate = [](int y1, int x1, int y2, int x2, int y) -> int {
            if (y2 == y1) return x1;
            return x1 + (x2 - x1) * (y - y1) / (y2 - y1);
        };

        for (int y = p1.getY(); y <= p2.getY(); ++y) {
            int xStart = interpolate(p1.getY(), p1.getX(), p2.getY(), p2.getX(), y);
            int xEnd = interpolate(p1.getY(), p1.getX(), p3.getY(), p3.getX(), y);
            if (xStart > xEnd) std::swap(xStart, xEnd);
            SDL_RenderDrawLine(renderer, xStart, y, xEnd, y);
        }

        for (int y = p2.getY(); y <= p3.getY(); ++y) {
            int xStart = interpolate(p2.getY(), p2.getX(), p3.getY(), p3.getX(), y);
            int xEnd = interpolate(p1.getY(), p1.getX(), p3.getY(), p3.getX(), y);
            if (xStart > xEnd) std::swap(xStart, xEnd);
            SDL_RenderDrawLine(renderer, xStart, y, xEnd, y);
        }
    };

    float maxDepth = std::max_element(faceDepths.begin(), faceDepths.end(), [](const auto& a, const auto& b) { return a.first < b.first; })->first;

    for (const auto& [depth, face] : faceDepths) {
        float normalizedDepth = std::clamp(depth / maxDepth, 0.0f, 1.0f);
        int redIntensity = static_cast<int>(255 * (1 - normalizedDepth));
        Couleur faceColor(redIntensity, 0, 0);

        renderTriangle(face->getFirstTriangle(), faceColor);
        renderTriangle(face->getSecondTriangle(), faceColor);
    }
}

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "Erreur : impossible d'initialiser SDL: " << SDL_GetError() << "\n";
        return -1;
    }

    SDL_Window* window = SDL_CreateWindow("Pave3D Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                          SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) {
        std::cerr << "Erreur : impossible de créer la fenêtre SDL: " << SDL_GetError() << "\n";
        SDL_Quit();
        return -1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "Erreur : impossible de créer le renderer SDL: " << SDL_GetError() << "\n";
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    Pave3D pave(Point3D(0, 0, 0), 250, 250, 250, Couleur(255, 255, 255));
    Point3D cameraPosition(0, 0, 0);
    Point2D translation2D(0, 0);

    bool running = true;
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            } else if (event.type == SDL_KEYDOWN) {
                Point3D paveCenter = pave.center();
                switch (event.key.keysym.sym) {
                    case SDLK_UP:
                        translation2D = translation2D + Point2D(0, -MOVE_STEP); // Déplacer en haut
                        break;
                    case SDLK_DOWN:
                        translation2D = translation2D + Point2D(0, MOVE_STEP); // Déplacer en bas
                        break;
                    case SDLK_LEFT:
                        translation2D = translation2D + Point2D(-MOVE_STEP, 0); // Déplacer à gauche
                        break;
                    case SDLK_RIGHT:
                        translation2D = translation2D + Point2D(MOVE_STEP, 0); // Déplacer à droite
                        break;
                    case SDLK_q:
                        pave.rotate(ROTATE_STEP, 'x', paveCenter);
                        break;
                    case SDLK_e:
                        pave.rotate(-ROTATE_STEP, 'x', paveCenter);
                        break;
                    case SDLK_a:
                        pave.rotate(ROTATE_STEP, 'y', paveCenter);
                        break;
                    case SDLK_d:
                        pave.rotate(-ROTATE_STEP, 'y', paveCenter);
                        break;
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        renderPave(renderer, pave, cameraPosition, translation2D);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}