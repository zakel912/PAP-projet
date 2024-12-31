/**
 * @file renderer.h
 * @brief Déclaration de la classe Renderer pour le rendu de la scène 3D en 2D à l'aide de SDL2.
 */

#ifndef RENDERER_H
#define RENDERER_H

#include <SDL2/SDL.h>
#include "scene3d.h"
#include "triangle2d.h"

/**
 * @class Renderer
 * @brief Classe pour gérer le rendu de la scène 3D en 2D à l'aide de SDL2.
 */
class Renderer {
private:
    SDL_Window* window_;           ///< Pointeur vers la fenêtre SDL.
    SDL_Renderer* renderer_;       ///< Pointeur vers le renderer SDL.
    int window_width_;             ///< Largeur de la fenêtre.
    int window_height_;            ///< Hauteur de la fenêtre.
    Scene3D* scene_;               ///< Pointeur vers la scène 3D à rendre.

    /**
     * @brief Dessine un triangle 2D sur la fenêtre SDL.
     * @param triangle Le triangle 2D à dessiner.
     */
    void drawTriangle(const Triangle2D& triangle) const;

public:
    /**
     * @brief Constructeur de la classe Renderer.
     * @param scene Pointeur vers la scène 3D à rendre.
     * @param window_width Largeur de la fenêtre.
     * @param window_height Hauteur de la fenêtre.
     */
    Renderer(Scene3D* scene, int window_width = 800, int window_height = 600);

    /**
     * @brief Destructeur de la classe Renderer.
     */
    ~Renderer();

    /**
     * @brief Initialise SDL2 pour le rendu.
     * @return true si l'initialisation a réussi, false sinon.
     */
    bool initialize();

    /**
     * @brief Effectue le rendu de la scène.
     */
    void render();

    /**
     * @brief Nettoie et ferme SDL2.
     */
    void cleanup();
};

#endif // RENDERER_H
