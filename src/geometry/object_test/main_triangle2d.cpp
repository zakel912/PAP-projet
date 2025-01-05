#include <SDL2/SDL.h>
#include <iostream>
#include "../triangle2d.h" // Incluez votre classe Triangle2D ici
#include "../point2d.h"    // Incluez votre classe Point2D ici
#include "../../couleur.h"    // Incluez votre classe Couleur ici

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int PIXEL_SIZE = 5;

void renderTriangle(SDL_Renderer* renderer, const Triangle2D& triangle) {
    SDL_SetRenderDrawColor(renderer, triangle.getColor().getRouge(),
                                      triangle.getColor().getVert(),
                                      triangle.getColor().getBleu(),
                                      255);

    // Tracer les lignes entre les sommets
    Point2D p1 = triangle.getP1();
    Point2D p2 = triangle.getP2();
    Point2D p3 = triangle.getP3();

    SDL_RenderDrawLine(renderer, p1.getX(), p1.getY(), p2.getX(), p2.getY());
    SDL_RenderDrawLine(renderer, p2.getX(), p2.getY(), p3.getX(), p3.getY());
    SDL_RenderDrawLine(renderer, p3.getX(), p3.getY(), p1.getX(), p1.getY());
}

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "Erreur : impossible d'initialiser SDL: " << SDL_GetError() << "\n";
        return -1;
    }

    SDL_Window* window = SDL_CreateWindow("Triangle2D Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
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

    // Triangle initial
    Triangle2D triangle(Point2D(100, 100), Point2D(200, 100), Point2D(150, 200), Couleur(255, 0, 0));

    bool running = true;
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            } else if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_UP:
                        triangle.translate(Point2D(0, -10));
                        break;
                    case SDLK_DOWN:
                        triangle.translate(Point2D(0, 10));
                        break;
                    case SDLK_LEFT:
                        triangle.translate(Point2D(-10, 0));
                        break;
                    case SDLK_RIGHT:
                        triangle.translate(Point2D(10, 0));
                        break;
                }
            }
        }

        // Efface l'écran
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Affiche le triangle
        renderTriangle(renderer, triangle);

        // Présente le rendu
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}