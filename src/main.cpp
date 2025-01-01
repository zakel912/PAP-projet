#include "renderer.h"
#include "scene3d.h"
#include "../geometry/pave3d.h"
#include "../geometry/sphere3d.h"
#include <iostream>
#include <memory>
#include <SDL2/SDL.h>

int main() {
    try {
        // Renderer initialization
        int screenWidth = 1000;
        int screenHeight = 800;
        int pixelSize = 40;  // Define the size of each pixel
        Renderer renderer(screenWidth, screenHeight, pixelSize);  // Pass pixelSize to the constructor

        int screenOffsetX = static_cast<float>(screenWidth) / (2 * pixelSize);
        int screenOffsetY = static_cast<float>(screenHeight) / (2 * pixelSize);

        // Scene setup
        Scene3D scene(Point3D(0, 0, 10), Point3D(0, 0, 20), 5.0f);

        // Adding a cube to the scene
        auto cube = std::make_shared<Pave3D>(
            Quad3D(Point3D(-2, -2, 18), Point3D(2, -2, 18), Point3D(2, 2, 18), Point3D(-2, 2, 18), Couleur(255, 0, 0)),
            Quad3D(Point3D(-2, -2, 22), Point3D(2, -2, 22), Point3D(2, 2, 22), Point3D(-2, 2, 22), Couleur(255, 0, 0)),
            Quad3D(Point3D(-2, -2, 18), Point3D(-2, 2, 18), Point3D(-2, 2, 22), Point3D(-2, -2, 22), Couleur(0, 255, 0)),
            Quad3D(Point3D(2, -2, 18), Point3D(2, 2, 18), Point3D(2, 2, 22), Point3D(2, -2, 22), Couleur(0, 255, 0)),
            Quad3D(Point3D(-2, 2, 18), Point3D(2, 2, 18), Point3D(2, 2, 22), Point3D(-2, 2, 22), Couleur(0, 0, 255)),
            Quad3D(Point3D(-2, -2, 18), Point3D(2, -2, 18), Point3D(2, -2, 22), Point3D(-2, -2, 22), Couleur(0, 0, 255)),
            Couleur(255, 0, 0));
        scene.addCube(cube);
        std::cout << "Cube rouge ajouté à la scène.\n";

        // Adding a sphere to the scene
        auto sphere = std::make_shared<Sphere3D>(Point3D(screenOffsetX, screenOffsetY, 20), Couleur(0, 255, 0), 3, 20);
        scene.addSphere(sphere);
        std::cout << "Sphère verte ajoutée à la scène.\n";

        // Retrieve projected triangles
        auto triangles = scene.getProjectedTriangles();

        // Main rendering loop
        bool running = true;
        SDL_Event event;

        while (running) {
            while (SDL_PollEvent(&event)) {
                if (event.type == SDL_QUIT) {
                    running = false;
                }
            }

            // Clear the screen
            renderer.clear({0, 0, 0, 255});

            // Render the scene
            renderer.renderScene(triangles);

            // Present the rendered frame
            renderer.present();
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return -1;
    }

    return 0;
}