#ifndef RENDERER_H
#define RENDERER_H

#include <SDL2/SDL.h>
#include <vector>
#include "../geometry/triangle2d.h"

class Renderer {
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    int width, height;
    int pixelSize; // Taille des pixels

public:
    Renderer(int width, int height, int pixelSize = 1);
    ~Renderer();

    void clear(const SDL_Color& color);
    void drawPixel(int x, int y, const SDL_Color& color);
    void renderScene(const std::vector<Triangle2D>& triangles);
    void present();
    void fillTriangle(const Triangle2D& triangle, const SDL_Color& color);

};


#endif // RENDERER_H
