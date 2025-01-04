#include "renderer.h"
#include "scene3d.h"
#include "../geometry/pave3d.h"
#include <iostream>
#include <SDL2/SDL.h>

// Configuration initiale
struct Config {
    int screenWidth = 800;
    int screenHeight = 600;
    int pixelSize = 10;
    Point3D cameraPosition = Point3D(0, 0, 5);
    Point3D lookAtPosition = Point3D(0, 0, 0);
    float projectionPlaneDistance = 5.0f;
};

// Fonction principale
int main(int argc, char* argv[]) {
    try {
        // Configuration par défaut
        Config config;

        // Lecture des arguments (si fournis)
        if (argc > 1) config.screenWidth = std::stoi(argv[1]);
        if (argc > 2) config.screenHeight = std::stoi(argv[2]);
        if (argc > 3) config.pixelSize = std::stoi(argv[3]);
        if (argc > 4) config.cameraPosition = Point3D(std::stof(argv[4]), std::stof(argv[5]), std::stof(argv[6]));
        if (argc > 7) config.lookAtPosition = Point3D(std::stof(argv[7]), std::stof(argv[8]), std::stof(argv[9]));
        if (argc > 10) config.projectionPlaneDistance = std::stof(argv[10]);

        // Initialisation du renderer
        Renderer renderer(config.screenWidth, config.screenHeight, config.pixelSize);

        // Initialisation de la scène
        Scene3D scene(config.cameraPosition, config.lookAtPosition, config.projectionPlaneDistance);

        // Ajout d'un cube
        Pave3D cube(
            Quad3D(Point3D(-1, -1, 2), Point3D(1, -1, 2), Point3D(1, 1, 2), Point3D(-1, 1, 2), Couleur(255, 0, 0)),
            Quad3D(Point3D(-1, -1, 4), Point3D(1, -1, 4), Point3D(1, 1, 4), Point3D(-1, 1, 4), Couleur(255, 0, 0)),
            Quad3D(Point3D(-1, -1, 2), Point3D(-1, 1, 2), Point3D(-1, 1, 4), Point3D(-1, -1, 4), Couleur(0, 255, 0)),
            Quad3D(Point3D(1, -1, 2), Point3D(1, 1, 2), Point3D(1, 1, 4), Point3D(1, -1, 4), Couleur(0, 255, 0)),
            Quad3D(Point3D(-1, 1, 2), Point3D(1, 1, 2), Point3D(1, 1, 4), Point3D(-1, 1, 4), Couleur(0, 0, 255)),
            Quad3D(Point3D(-1, -1, 2), Point3D(1, -1, 2), Point3D(1, -1, 4), Point3D(-1, -1, 4), Couleur(0, 0, 255))
        );
        scene.addCube(cube);

        bool running = true;
        SDL_Event event;

        while (running) {
            while (SDL_PollEvent(&event)) {
                if (event.type == SDL_QUIT) {
                    running = false;
                }
                if (event.type == SDL_KEYDOWN) {
                    switch (event.key.keysym.sym) {
                        case SDLK_w: scene.setEye(scene.getEye() + Point3D(0, 1, 0)); break;
                        case SDLK_s: scene.setEye(scene.getEye() + Point3D(0, -1, 0)); break;
                        case SDLK_a: scene.setEye(scene.getEye() + Point3D(-1, 0, 0)); break;
                        case SDLK_d: scene.setEye(scene.getEye() + Point3D(1, 0, 0)); break;
                        case SDLK_q: scene.setEye(scene.getEye() + Point3D(0, 0, -1)); break;
                        case SDLK_e: scene.setEye(scene.getEye() + Point3D(0, 0, 1)); break;
                    }
                }
            }

            renderer.clear({0, 0, 0, 255});
            renderer.renderScene(scene);
            renderer.present();
        }
    } catch (const std::exception& e) {
        std::cerr << "Erreur : " << e.what() << std::endl;
        return -1;
    }

    return 0;
}
