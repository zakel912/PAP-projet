#include <SDL2/SDL.h>
#include <iostream>
#include <cmath>
#include "../triangle3d.h"
#include "../point3d.h"
#include "../point2d.h"
#include "../../couleur.h"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const float PROJECTION_DISTANCE = 100.0f;
const int MOVE_STEP = 10;
const float ROTATION_ANGLE = M_PI / 18;

Point2D projectPoint(const Point3D& point3D) {
    float denominator = PROJECTION_DISTANCE + point3D.getZ();
    if (denominator == 0) {
        throw std::runtime_error("Division par zéro lors de la projection.");
    }
    float scale = PROJECTION_DISTANCE / denominator;
    return Point2D(static_cast<int>(point3D.getX() * scale + SCREEN_WIDTH / 2),
                   static_cast<int>(-point3D.getY() * scale + SCREEN_HEIGHT / 2));
}

void renderTriangle(SDL_Renderer* renderer, const Triangle3D& triangle, const Point3D& cameraPosition) {
    Point3D normal = triangle.getNormale();
    Point3D toTriangle = triangle.getCentroid() - cameraPosition;
    float dotProduct = normal.getX() * toTriangle.getX() +
                       normal.getY() * toTriangle.getY() +
                       normal.getZ() * toTriangle.getZ();

    float depth = triangle.averageDepth();

    int intensity = static_cast<int>(255 * (1.0f - std::min(depth / 300.0f, 1.0f)));
    Couleur faceColor = (dotProduct > 0) ? Couleur(intensity, 0, 0) : Couleur(0, 0, intensity);

    Point2D p1 = projectPoint(triangle.getP1());
    Point2D p2 = projectPoint(triangle.getP2());
    Point2D p3 = projectPoint(triangle.getP3());

    if (p2.getY() < p1.getY()) std::swap(p1, p2);
    if (p3.getY() < p1.getY()) std::swap(p1, p3);
    if (p3.getY() < p2.getY()) std::swap(p2, p3);

    auto interpolate = [](int y1, int x1, int y2, int x2, int y) -> int {
        if (y2 == y1) return x1;
        return x1 + (x2 - x1) * (y - y1) / (y2 - y1);
    };

    SDL_SetRenderDrawColor(renderer, faceColor.getRouge(), faceColor.getVert(), faceColor.getBleu(), 255);

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
}

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "Erreur : impossible d'initialiser SDL: " << SDL_GetError() << "\n";
        return -1;
    }

    SDL_Window* window = SDL_CreateWindow("3D Triangle Rotation", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
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

    Triangle3D triangle(Point3D(-100, -100, 200), Point3D(100, -100, 200), Point3D(0, 100, 200), Couleur(255, 255, 255));
    Point3D cameraPosition(0, 0, 0);

    bool running = true;
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            } else if (event.type == SDL_KEYDOWN) {
                Point3D centroid = triangle.getCentroid();
                switch (event.key.keysym.sym) {
                    case SDLK_UP:
                        triangle.translate(Point3D(0, MOVE_STEP, 0));
                        break;
                    case SDLK_DOWN:
                        triangle.translate(Point3D(0, -MOVE_STEP, 0));
                        break;
                    case SDLK_LEFT:
                        triangle.translate(Point3D(-MOVE_STEP, 0, 0));
                        break;
                    case SDLK_RIGHT:
                        triangle.translate(Point3D(MOVE_STEP, 0, 0));
                        break;
                    case SDLK_r: 
                        triangle.rotate(ROTATION_ANGLE, 'x', centroid);
                        break;
                    case SDLK_t:
                        triangle.rotate(ROTATION_ANGLE, 'y', centroid);
                        break;
                    case SDLK_y: 
                        triangle.rotate(ROTATION_ANGLE, 'z', centroid);
                        break;
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        renderTriangle(renderer, triangle, cameraPosition);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
