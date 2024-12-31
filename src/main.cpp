#include "renderer.h"
#include "scene3d.h"
#include <SDL2/SDL.h>
#include <memory> // For std::make_shared

int main(int argc, char* argv[]) {
    const int width = 800;
    const int height = 600;

    // Création de la scène
    Point3D eyePosition(0, 0, -10);        // Position de l'œil derrière la scène
    Point3D lookAt(0, 0, 0);               // Point regardé
    float projectionPlaneDistance = 1.0f; // Distance du plan de projection

    Scene3D scene(eyePosition, lookAt, projectionPlaneDistance);

    // Ajout d'objets à la scène
    auto cube = std::make_shared<Pave3D>(/* Initialize cube with quads and color */);
    scene.addCube(cube);

    auto sphere = std::make_shared<Sphere3D>(Point3D(2, 2, 2), Couleur(255, 0, 0), 1.0f, 10);
    scene.addSphere(sphere);

    // Création du renderer
    Renderer renderer(&scene, width, height);

    // Initialisation de SDL2
    if (!renderer.initialize()) {
        return -1;
    }

    // Boucle principale
    bool running = true;
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }

        // Rendu de la scène
        renderer.render();
    }

    // Nettoyage
    renderer.cleanup();

    return 0;
}
