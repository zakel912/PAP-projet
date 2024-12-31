#include "renderer.h"
#include <stdexcept>
#include <iostream>

Renderer::Renderer(int width, int height) : width_(width), height_(height) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        throw std::runtime_error("SDL_Init Error: " + std::string(SDL_GetError()));
    }

    window_ = SDL_CreateWindow("3D Scene Renderer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width_, height_, SDL_WINDOW_SHOWN);
    if (!window_) {
        throw std::runtime_error("SDL_CreateWindow Error: " + std::string(SDL_GetError()));
    }

    renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer_) {
        SDL_DestroyWindow(window_);
        throw std::runtime_error("SDL_CreateRenderer Error: " + std::string(SDL_GetError()));
    }
}

Renderer::~Renderer() {
    SDL_DestroyRenderer(renderer_);
    SDL_DestroyWindow(window_);
    SDL_Quit();
}

void Renderer::clear() {
    SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 255); // Fond noir
    SDL_RenderClear(renderer_);
}

void Renderer::present() {
    SDL_RenderPresent(renderer_);
}

void Renderer::setColor(int r, int g, int b) {
    SDL_SetRenderDrawColor(renderer_, r, g, b, 255);
}

void Renderer::drawTriangle(const Triangle2D& triangle) {
    setColor(triangle.getColor().getRouge(), triangle.getColor().getVert(), triangle.getColor().getBleu());

    // Dessin des lignes reliant les sommets
    const auto& p1 = triangle.getP1();
    const auto& p2 = triangle.getP2();
    const auto& p3 = triangle.getP3();

    SDL_RenderDrawLine(renderer_, p1.getX(), p1.getY(), p2.getX(), p2.getY());
    SDL_RenderDrawLine(renderer_, p2.getX(), p2.getY(), p3.getX(), p3.getY());
    SDL_RenderDrawLine(renderer_, p3.getX(), p3.getY(), p1.getX(), p1.getY());
}

void Renderer::renderScene(const std::vector<Triangle2D>& triangles) {
    clear();

    for (const auto& triangle : triangles) {
        drawTriangle(triangle);
    }

    present();
}