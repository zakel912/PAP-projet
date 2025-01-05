#include <SDL2/SDL.h>
#include <iostream>
#include "../quad3d.h"
#include "../point3d.h"
#include "../point2d.h"
#include "../triangle3d.h"
#include "../../couleur.h"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const float PROJECTION_DISTANCE = 300.0f; // Increased projection distance
const int MOVE_STEP = 10;
const float ROTATE_STEP = 0.1f;

Point2D projectPoint(const Point3D& point3D) {
    float denominator = PROJECTION_DISTANCE + point3D.getZ();
    if (denominator == 0) {
        throw std::runtime_error("Division by zero during projection.");
    }
    float scale = PROJECTION_DISTANCE / denominator;
    return Point2D(static_cast<int>(point3D.getX() * scale + SCREEN_WIDTH / 2),
                   static_cast<int>(-point3D.getY() * scale + SCREEN_HEIGHT / 2));
}

void renderQuad(SDL_Renderer* renderer, const Quad3D& quad, const Point3D& cameraPosition) {
    auto renderTriangle = [&](const Triangle3D& triangle) {
        Point3D normal = triangle.getNormale();
        Point3D toTriangle = triangle.getCentroid() - cameraPosition;
        float dotProduct = normal.getX() * toTriangle.getX() +
                           normal.getY() * toTriangle.getY() +
                           normal.getZ() * toTriangle.getZ();

        int intensity = std::max(0, 255 - static_cast<int>(triangle.averageDepth() * 0.5));
        Couleur faceColor = (dotProduct > 0) ? Couleur(intensity, 0, 0) : Couleur(0, 0, intensity);

        Point2D p1 = projectPoint(triangle.getP1());
        Point2D p2 = projectPoint(triangle.getP2());
        Point2D p3 = projectPoint(triangle.getP3());

        auto interpolate = [](int y1, int x1, int y2, int x2, int y) -> int {
            if (y2 == y1) return x1;
            return x1 + (x2 - x1) * (y - y1) / (y2 - y1);
        };

        if (p2.getY() < p1.getY()) std::swap(p1, p2);
        if (p3.getY() < p1.getY()) std::swap(p1, p3);
        if (p3.getY() < p2.getY()) std::swap(p2, p3);

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
    };

    renderTriangle(quad.getFirstTriangle());
    renderTriangle(quad.getSecondTriangle());
}

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "Error initializing SDL: " << SDL_GetError() << "\n";
        return -1;
    }

    SDL_Window* window = SDL_CreateWindow("Quad3D Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                          SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) {
        std::cerr << "Error creating SDL window: " << SDL_GetError() << "\n";
        SDL_Quit();
        return -1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "Error creating SDL renderer: " << SDL_GetError() << "\n";
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    Quad3D quad(Point3D(-100, -100, 200), Point3D(100, -100, 200), Point3D(100, 100, 200), Point3D(-100, 100, 200), 255, 0, 0);
    Point3D cameraPosition(0, 0, 0);

    bool running = true;
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            } else if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_UP:
                        quad.translate(Point3D(0, MOVE_STEP, 0));
                        break;
                    case SDLK_DOWN:
                        quad.translate(Point3D(0, -MOVE_STEP, 0));
                        break;
                    case SDLK_LEFT:
                        quad.translate(Point3D(-MOVE_STEP, 0, 0));
                        break;
                    case SDLK_RIGHT:
                        quad.translate(Point3D(MOVE_STEP, 0, 0));
                        break;
                    case SDLK_w:
                        cameraPosition = cameraPosition + Point3D(0, 0, -MOVE_STEP);
                        break;
                    case SDLK_s:
                        cameraPosition = cameraPosition + Point3D(0, 0, MOVE_STEP);
                        break;
                    case SDLK_a:
                        quad.rotate(ROTATE_STEP, 'y');
                        break;
                    case SDLK_d:
                        quad.rotate(-ROTATE_STEP, 'y');
                        break;
                    case SDLK_q:
                        quad.rotate(ROTATE_STEP, 'x');
                        break;
                    case SDLK_e:
                        quad.rotate(-ROTATE_STEP, 'x');
                        break;
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        renderQuad(renderer, quad, cameraPosition);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}