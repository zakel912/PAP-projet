#include <iostream>
#include <vector>
#include "scene3d.h"
#include "sdl/renderer.h"

int main() {
    try {
        const int windowWidth = 1000;
        const int windowHeight = 1000;
        const int pixelSize = 30; // Each pixel is 20x20

        // Calculate the center of the rendering window
        const int centerX = windowWidth / (2 * pixelSize);
        const int centerY = windowHeight / (2 * pixelSize);

        // Initialize the scene
        Scene3D scene(Point3D(0, 0, 0), Point3D(0, 0, 30), 5.0f);
        std::cout << "Scene initialized with:\n"
                  << "  Eye: (0, 0, 20)\n"
                  << "  Target: (0, 0, 30)\n"
                  << "  Projection plane distance: 5.0\n";

        // Add a red cube centered near the scene origin
        auto redCube = std::make_shared<Pave3D>(
            std::array<Quad3D, 6>{
                Quad3D(Point3D(-5, -5, 35), Point3D(5, -5, 35), Point3D(5, 5, 35), Point3D(-5, 5, 35), Couleur(255, 0, 0)),
                Quad3D(Point3D(-5, -5, 30), Point3D(5, -5, 30), Point3D(5, 5, 30), Point3D(-5, 5, 30), Couleur(255, 0, 0)),
                Quad3D(Point3D(-5, -5, 35), Point3D(-5, 5, 35), Point3D(-5, 5, 30), Point3D(-5, -5, 30), Couleur(255, 0, 0)),
                Quad3D(Point3D(5, -5, 35), Point3D(5, 5, 35), Point3D(5, 5, 30), Point3D(5, -5, 30), Couleur(255, 0, 0)),
                Quad3D(Point3D(-5, 5, 35), Point3D(5, 5, 35), Point3D(5, 5, 30), Point3D(-5, 5, 30), Couleur(255, 0, 0)),
                Quad3D(Point3D(-5, -5, 35), Point3D(5, -5, 35), Point3D(5, -5, 30), Point3D(-5, -5, 30), Couleur(255, 0, 0))
            },
            Couleur(255, 0, 0)
        );
        scene.addCube(redCube);

        // Add a green sphere centered closer to the cube
        auto greenSphere = std::make_shared<Sphere3D>(
            Point3D(centerX, centerY, 10), Couleur(0, 255, 0), 7.0f, 10);
        scene.addSphere(greenSphere);

        // Get projected triangles
        std::vector<Triangle2D> projectedTriangles = scene.getProjectedTriangles();

        // Initialize SDL renderer
        Renderer renderer(windowWidth, windowHeight, pixelSize);

        // Center the projected 2D triangles
        for (auto& triangle : projectedTriangles) {
            triangle.getP1().setX(triangle.getP1().getX() + centerX);
            triangle.getP1().setY(triangle.getP1().getY() + centerY);

            triangle.getP2().setX(triangle.getP2().getX() + centerX);
            triangle.getP2().setY(triangle.getP2().getY() + centerY);

            triangle.getP3().setX(triangle.getP3().getX() + centerX);
            triangle.getP3().setY(triangle.getP3().getY() + centerY);
        }

        // Render the scene
        renderer.renderScene(projectedTriangles);

        // Pause before exiting
        SDL_Delay(5000);
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }

    return 0;
}
