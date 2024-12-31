#ifndef RENDERER_H
#define RENDERER_H

#include <SDL2/SDL.h>
#include <vector>
#include "../geometry/triangle2d.h"

class Renderer {
private:
    SDL_Window* window_;
    SDL_Renderer* renderer_;
    int width_, height_;

public:
    Renderer(int width, int height);
    ~Renderer();

    void clear(); // Nettoyer l'écran
    void present(); // Présenter l'écran
    void drawTriangle(const Triangle2D& triangle); // Dessiner un triangle
    void setColor(int r, int g, int b); // Configurer la couleur

    void renderScene(const std::vector<Triangle2D>& triangles); // Rendu de la scène
};

#endif // RENDERER_H
