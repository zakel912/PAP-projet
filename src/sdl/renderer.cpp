#include "renderer.h"
#include <stdexcept>

// Constructeur
Renderer::Renderer(Scene3D* scene, int window_width, int window_height)
    : scene_(scene), window_width_(window_width), window_height_(window_height), window_(nullptr), renderer_(nullptr) {}

// Destructeur
Renderer::~Renderer() {
    cleanup();
}

// Initialise SDL2
bool Renderer::initialize() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        throw std::runtime_error("Impossible d'initialiser SDL2 : " + std::string(SDL_GetError()));
    }

    window_ = SDL_CreateWindow("3D Renderer",
                               SDL_WINDOWPOS_CENTERED,
                               SDL_WINDOWPOS_CENTERED,
                               window_width_,
                               window_height_,
                               SDL_WINDOW_SHOWN);
    if (!window_) {
        throw std::runtime_error("Impossible de créer la fenêtre : " + std::string(SDL_GetError()));
    }

    renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer_) {
        throw std::runtime_error("Impossible de créer le renderer : " + std::string(SDL_GetError()));
    }

    return true;
}

// Dessine un triangle 2D
void Renderer::drawTriangle(const Triangle2D& triangle) const {
    // Récupérer la couleur du triangle
    Couleur color = triangle.getColor();
    SDL_SetRenderDrawColor(renderer_, color.getRouge(), color.getVert(), color.getBleu(), SDL_ALPHA_OPAQUE);

    // Dessiner les lignes du triangle
    SDL_RenderDrawLine(renderer_,
                       static_cast<int>(triangle.getP1().getX()), static_cast<int>(triangle.getP1().getY()),
                       static_cast<int>(triangle.getP2().getX()), static_cast<int>(triangle.getP2().getY()));

    SDL_RenderDrawLine(renderer_,
                       static_cast<int>(triangle.getP2().getX()), static_cast<int>(triangle.getP2().getY()),
                       static_cast<int>(triangle.getP3().getX()), static_cast<int>(triangle.getP3().getY()));

    SDL_RenderDrawLine(renderer_,
                       static_cast<int>(triangle.getP3().getX()), static_cast<int>(triangle.getP3().getY()),
                       static_cast<int>(triangle.getP1().getX()), static_cast<int>(triangle.getP1().getY()));
}

// Effectue le rendu de la scène
void Renderer::render() {
    // Effacer l'écran
    SDL_SetRenderDrawColor(renderer_, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer_);

    // Obtenir les triangles projetés de la scène
    auto projectedTriangles = scene_->getProjectedTriangles();

    // Dessiner chaque triangle
    for (const auto& triangle : projectedTriangles) {
        drawTriangle(triangle);
    }

    // Mettre à jour l'affichage
    SDL_RenderPresent(renderer_);
}

// Nettoie et ferme SDL2
void Renderer::cleanup() {
    if (renderer_) {
        SDL_DestroyRenderer(renderer_);
        renderer_ = nullptr;
    }

    if (window_) {
        SDL_DestroyWindow(window_);
        window_ = nullptr;
    }

    SDL_Quit();
}
