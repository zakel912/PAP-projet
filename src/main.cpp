#include "sdl/renderer.h"
#include "scene/scene3d.h"
#include "geometry/pave3d.h"
#include "geometry/sphere3d.h"
#include <SDL2/SDL.h>
#include <iostream>
#include <memory> // Pour std::make_shared
#include <cmath>  // Pour M_PI

// Dimensions de l'écran
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

// Pas de mouvement et de rotation
const int MOVE_STEP = 10;
const float ROTATE_STEP = M_PI / 18; // 10 degrés en radians

/**
 * @brief Fonction principale.
 */
int main() {
    try {
        // Initialisation du renderer
        Renderer renderer(SCREEN_WIDTH, SCREEN_HEIGHT);

        // Initialisation de la scène avec une caméra
        Scene3D scene(
            Point3D(0, 0, -200),   // Position de l'œil
            Point3D(0, 0, 0),      // Point de visée
            100.0f                 // Distance du plan de projection
        );

        // Ajout d'un pavé à la scène
        auto cube = std::make_shared<Pave3D>(
            Point3D(-25, -25, 50), // Origine du pavé
            100, 100, 100,         // Dimensions : longueur, largeur, hauteur
            Couleur(255, 0, 0)     // Couleur rouge
        );
        scene.addCube(cube);

        // Ajout d'une sphère à la scène
        auto sphere = std::make_shared<Sphere3D>(
            Point3D(50, 50, 100),  // Centre
            50,                    // Rayon
            16                     // Subdivisions
        );
        scene.addSphere(sphere);

        // Variables de translation spécifiques
        Point2D cubeTranslation(0, 0);      // Translation spécifique au cube
        Point2D sphereTranslation(0, 0);    // Translation spécifique à la sphère
        float cubeTranslationZ = 0;      // Translation spécifique au cube en Z
        float sphereTranslationZ = 0;    // Translation spécifique à la sphère en Z

        // Variable pour gérer la sélection d'objet
        int selectedObject = 0; // 0 pour le cube, 1 pour la sphère

        // Boucle principale
        bool running = true;
        SDL_Event event;

        while (running) {
            // Gestion des événements
            while (SDL_PollEvent(&event)) {
                if (event.type == SDL_QUIT) {
                    running = false;
                } else if (event.type == SDL_KEYDOWN) {
                    switch (event.key.keysym.sym) {
                        // Changer l'objet sélectionné
                        case SDLK_TAB:
                            selectedObject = (selectedObject + 1) % 2;
                            break;

                        // Translation en X et Y
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
                        case SDLK_k: // Translation en Z positif (vers l'observateur)
                            if (selectedObject == 0) {
                                cubeTranslationZ += MOVE_STEP;
                            } else {
                                sphereTranslationZ += MOVE_STEP;
                            }
                            break;
                        case SDLK_l: // Translation en Z négatif (éloignement)
                            if (selectedObject == 0) {
                                cubeTranslationZ -= MOVE_STEP;
                            } else {
                                sphereTranslationZ -= MOVE_STEP;
                            }
                            break;


                        // Rotation en X
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

                        // Rotation en Y
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

                        // Translation de la caméra
                        case SDLK_w:
                            scene.setEye(scene.getEye() + Point3D(0, MOVE_STEP, 0));
                            break;
                        case SDLK_x:
                            scene.setEye(scene.getEye() + Point3D(0, -MOVE_STEP, 0));
                            break;
                        case SDLK_c:
                            scene.setEye(scene.getEye() + Point3D(0, 0, MOVE_STEP));
                            break;
                        case SDLK_v:
                            scene.setEye(scene.getEye() + Point3D(0, 0, -MOVE_STEP));
                            break;
                        case SDLK_b:
                            scene.setEye(scene.getEye() + Point3D(MOVE_STEP, 0, 0));
                            break;
                        case SDLK_n:
                            scene.setEye(scene.getEye() + Point3D(-MOVE_STEP, 0, 0));
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
            renderer.renderCube(cube, cubeTranslation, cubeTranslationZ, scene);

            // Rendre la sphère
            renderer.renderSphere(sphere, sphereTranslation, sphereTranslationZ, scene);

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
