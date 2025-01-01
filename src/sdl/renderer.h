#ifndef RENDERER_H
#define RENDERER_H

#include <SDL2/SDL.h>
#include <vector>
#include "../geometry/triangle2d.h"

/**
 * @class Renderer
 * @brief A class to manage SDL rendering of 2D triangles.
 */
class Renderer {
    private:
        SDL_Window* window;         // SDL window instance.
        SDL_Renderer* renderer;     // SDL renderer instance.
        int pixelSize;              // Pixel size for rendering.
    public:
        /**
         * @brief Constructor for the Renderer.
         * @param width Width of the SDL window.
         * @param height Height of the SDL window.
         * @param pixelSize Size of each pixel for rendering.
         */
        Renderer(int width, int height, int pixelSize = 1);

        /**
         * @brief Destructor for the Renderer.
         */
        ~Renderer();

        /**
         * @brief Clears the screen with the specified color.
         * @param color The SDL color to fill the screen.
         */
        void clear(const SDL_Color& color);

        /**
         * @brief Draws a pixel at the specified position with the given color.
         * @param x X-coordinate of the pixel.
         * @param y Y-coordinate of the pixel.
         * @param color The SDL color of the pixel.
         */
        void drawPixel(int x, int y, const SDL_Color& color);

        /**
         * @brief Fills a triangle using rasterization.
         * @param triangle The 2D triangle to fill.
         * @param color The SDL color of the triangle.
         */
        void fillTriangle(const Triangle2D& triangle, const SDL_Color& color);

        /**
         * @brief Renders all the triangles in the scene.
         * @param triangles A vector of projected 2D triangles.
         */
        void renderScene(const std::vector<Triangle2D>& triangles);

        /**
         * @brief Presents the rendered content on the screen.
         */
        void present();
};

#endif // RENDERER_H