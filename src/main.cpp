#include "sdl/renderer.h"
#include "scene/scene3d.h"
#include "geometry/pave3d.h"
#include "geometry/sphere3d.h"
#include "geometry/point3d.h"
#include <SDL2/SDL.h>
#include <iostream>
#include <memory> // Pour std::make_shared
#include <cmath>  // Pour M_PI

// Dimensions de l'écran
const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 900;

// Pas de mouvement et de rotation 
const int MOVE_STEP = 10;
const float ROTATE_STEP = M_PI / 18; // 10 degrés en radians

/**
 * @brief Fonction principale.
 */
int main() {
    try {

        Renderer renderer(SCREEN_WIDTH, SCREEN_HEIGHT);

        Scene3D scene(
            Point3D(0, 0, -200),   // Position de l'œil
            Point3D(0, 0, 0),      // Point de visée
            100.0f                 // Distance du plan de projection
        );

        // Ajout d'un pavé à la scène
        auto cube = std::make_shared<Pave3D>(
            Point3D(-25, -25, 50), // Origine du pavé
            200, 200, 200,         // Dimensions : longueur, largeur, hauteur
            Couleur(255, 0, 0)     // Couleur rouge
        );
        scene.addCube(cube);

        // Ajout d'une sphère à la scène
        auto sphere = std::make_shared<Sphere3D>(
            Point3D(-150, -50, 50),  // Centre
            100,                    // Rayon
            40                     // Subdivisions
        );
        scene.addSphere(sphere);

        // Variables de translation spécifiques
        Point2D cubeTranslation(0, 0);
        Point2D sphereTranslation(0, 0);
        float cubeTranslationZ = 0;
        float sphereTranslationZ = 0;
        Point2D cameraTranslation(0, 0);

        // Variable pour gérer la sélection d'objet
        int selectedObject = 0; // 0 = cube, 1 = sphère

        bool running = true;
        SDL_Event event;

        while (running) {

            while (SDL_PollEvent(&event)) {
                if (event.type == SDL_QUIT) {
                    running = false;
                } else if (event.type == SDL_KEYDOWN) {
                    switch (event.key.keysym.sym) {

                        // Changer l'objet sélectionné
                        case SDLK_TAB:
                            selectedObject = (selectedObject + 1) % 2;
                            break;

                        // Translation en X, Y et Z
                        case SDLK_UP:
                            if (selectedObject == 0) {
                                cubeTranslation = cubeTranslation + Point2D(0, -MOVE_STEP);
                            } else {
                                sphereTranslation = sphereTranslation + Point2D(0, -MOVE_STEP);
                            }
                            break;
                        case SDLK_DOWN:
                            if (selectedObject == 0) {
                                cubeTranslation = cubeTranslation + Point2D(0, MOVE_STEP);
                            } else {
                                sphereTranslation = sphereTranslation + Point2D(0, MOVE_STEP);
                            }
                            break;
                        case SDLK_LEFT:
                            if (selectedObject == 0) {
                                cubeTranslation = cubeTranslation + Point2D(-MOVE_STEP, 0);
                            } else {
                                sphereTranslation = sphereTranslation + Point2D(-MOVE_STEP, 0);
                            }
                            break;
                        case SDLK_RIGHT:
                            if (selectedObject == 0) {
                                cubeTranslation = cubeTranslation + Point2D(MOVE_STEP, 0);
                            } else {
                                sphereTranslation = sphereTranslation + Point2D(MOVE_STEP, 0);
                            }
                            break;
                        case SDLK_KP_1:
                            if (selectedObject == 0) {
                                cubeTranslationZ += MOVE_STEP;
                            } else {
                                sphereTranslationZ += MOVE_STEP;
                            }
                            break;
                        case SDLK_KP_2:
                            if (selectedObject == 0) {
                                cubeTranslationZ -= MOVE_STEP;
                            } else {
                                sphereTranslationZ -= MOVE_STEP;
                            }
                            break;

                        // Rotation en X de l'objet
                        case SDLK_a:
                            if (selectedObject == 0) {
                                cube->rotate(ROTATE_STEP, 'x', cube->center());
                            } else {
                                for (auto& quad : sphere->getQuads()) {
                                    quad.rotate(ROTATE_STEP, 'x', sphere->getCenter());
                                }
                            }
                            break;
                        case SDLK_z:
                            if (selectedObject == 0) {
                                cube->rotate(-ROTATE_STEP, 'x', cube->center());
                            } else {
                                for (auto& quad : sphere->getQuads()) {
                                    quad.rotate(-ROTATE_STEP, 'x', sphere->getCenter());
                                }
                            }
                            break;

                        // Rotation en Y de l'objet
                        case SDLK_e:
                            if (selectedObject == 0) {
                                cube->rotate(ROTATE_STEP, 'y', cube->center());
                            } else {
                                for (auto& quad : sphere->getQuads()) {
                                    quad.rotate(ROTATE_STEP, 'y', sphere->getCenter());
                                }
                            }
                            break;
                        case SDLK_r:
                            if (selectedObject == 0) {
                                cube->rotate(-ROTATE_STEP, 'y', cube->center());
                            } else {
                                for (auto& quad : sphere->getQuads()) {
                                    quad.rotate(-ROTATE_STEP, 'y', sphere->getCenter());
                                }
                            }
                            break;

                        // Rotation en Z de l'objet
                        case SDLK_t:
                            if (selectedObject == 0) {
                                cube->rotate(ROTATE_STEP, 'z', cube->center());
                            } else {
                                for (auto& quad : sphere->getQuads()) {
                                    quad.rotate(ROTATE_STEP, 'z', sphere->getCenter());
                                }
                            }
                            break;
                        case SDLK_y:
                            if (selectedObject == 0) {
                                cube->rotate(-ROTATE_STEP, 'z', cube->center());
                            } else {
                                for (auto& quad : sphere->getQuads()) {
                                    quad.rotate(-ROTATE_STEP, 'z', sphere->getCenter());
                                }
                            }
                            break;

                        // Translation de la caméra
                        case SDLK_w:
                            scene.setEye(scene.getEye() + Point3D(0, MOVE_STEP, 0));
                            cameraTranslation = cameraTranslation + Point2D(0, -MOVE_STEP);
                            break;
                        case SDLK_x:
                            scene.setEye(scene.getEye() + Point3D(0, -MOVE_STEP, 0));
                            cameraTranslation = cameraTranslation + Point2D(0, MOVE_STEP);
                            break;
                        case SDLK_c:
                            scene.setEye(scene.getEye() + Point3D(0, 0, MOVE_STEP));
                            break;
                        case SDLK_v:
                            scene.setEye(scene.getEye() + Point3D(0, 0, -MOVE_STEP));
                            break;
                        case SDLK_b:
                            scene.setEye(scene.getEye() + Point3D(MOVE_STEP, 0, 0));
                        cameraTranslation = cameraTranslation + Point2D(-MOVE_STEP, 0);
                            break;
                        case SDLK_n:
                            scene.setEye(scene.getEye() + Point3D(-MOVE_STEP, 0, 0));
                            cameraTranslation = cameraTranslation + Point2D(MOVE_STEP, 0);
                            break;
                        
                        // Quitter le programme
                        case SDLK_ESCAPE:
                            running = false;
                            break;
                    }
                }
            }

            // Effacer l'écran
            renderer.clear({0, 0, 0, 255}); // Fond noir

            // Rendre le cube
            renderer.renderCube(cube, cubeTranslation + cameraTranslation, cubeTranslationZ, scene);

            // Rendre la sphère
            renderer.renderSphere(sphere, sphereTranslation + cameraTranslation, sphereTranslationZ, scene);

            // Mettre à jour l'affichage
            renderer.present();
        }
    } catch (const std::exception& e) {
        // Gestion des erreurs
        std::cerr << "Erreur : " << e.what() << "\n";
        return -1;
    }

    return 0;
}