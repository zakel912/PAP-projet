#ifndef RENDERER_H
#define RENDERER_H

#include <SDL2/SDL.h>
#include <vector>
#include "../geometry/triangle2d.h"
#include "../scene/scene3d.h"

class Renderer {
public:
    Renderer(int width, int height, int pixelSize = 1);
    ~Renderer();

    void clear(const SDL_Color& color);
    void renderScene(const Scene3D& scene);
    void present();

private:
    int width_;
    int height_;
    int pixelSize_;
    SDL_Window* window_;
    SDL_Renderer* renderer_;

    void drawPixel(int x, int y, const SDL_Color& color);
    void fillTriangle(const Triangle2D& triangle, const SDL_Color& color);
};

#endif
