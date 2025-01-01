#include "renderer.h"

bool initializeRenderer(SDL_Window** window, SDL_Renderer** renderer, int width, int height) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        SDL_Log("SDL_Init Error: %s", SDL_GetError());
        return false;
    }

    *window = SDL_CreateWindow("3D Renderer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
    if (!*window) {
        SDL_Log("SDL_CreateWindow Error: %s", SDL_GetError());
        SDL_Quit();
        return false;
    }

    *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!*renderer) {
        SDL_DestroyWindow(*window);
        SDL_Log("SDL_CreateRenderer Error: %s", SDL_GetError());
        SDL_Quit();
        return false;
    }

    return true;
}

void cleanupRenderer(SDL_Window* window, SDL_Renderer* renderer) {
    if (renderer) SDL_DestroyRenderer(renderer);
    if (window) SDL_DestroyWindow(window);
    SDL_Quit();
}

void drawFilledTriangle(SDL_Renderer* renderer, const Triangle2D& triangle) {
    const auto& p1 = triangle.getP1();
    const auto& p2 = triangle.getP2();
    const auto& p3 = triangle.getP3();

    int r = triangle.getColor().getRouge();
    int g = triangle.getColor().getVert();
    int b = triangle.getColor().getBleu();

    SDL_SetRenderDrawColor(renderer, r, g, b, 255);

    // Sorting vertices by y-coordinate
    std::vector<Point2D> points = {p1, p2, p3};
    std::sort(points.begin(), points.end(), [](const Point2D& a, const Point2D& b) {
        return a.getY() < b.getY();
    });

    // Triangle vertices
    Point2D v1 = points[0];
    Point2D v2 = points[1];
    Point2D v3 = points[2];

    // Rasterizing the triangle
    auto drawLine = [&](int x1, int y1, int x2, int y2) {
        float slope = (x2 - x1) / float(y2 - y1);
        float x = x1;

        for (int y = y1; y <= y2; ++y) {
            SDL_RenderDrawPoint(renderer, int(x), y);
            x += slope;
        }
    };

    if (v2.getY() != v1.getY()) {
        drawLine(v1.getX(), v1.getY(), v2.getX(), v2.getY());
    }
    if (v3.getY() != v2.getY()) {
        drawLine(v2.getX(), v2.getY(), v3.getX(), v3.getY());
    }
    if (v3.getY() != v1.getY()) {
        drawLine(v1.getX(), v1.getY(), v3.getX(), v3.getY());
    }
}

void renderTriangles(SDL_Renderer* renderer, const std::vector<Triangle2D>& triangles) {
    for (const auto& triangle : triangles) {
        drawFilledTriangle(renderer, triangle);
    }
}