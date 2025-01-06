#ifndef RENDERER_H
#define RENDERER_H

#include <SDL2/SDL.h>
#include <vector>
#include <algorithm>
#include "../geometry/triangle2d.h"
#include "../scene/scene3d.h"

/**
 * @class Renderer
 * @brief Classe pour gérer le rendu graphique 2D des objets projetés depuis une scène 3D.
 *
 * Cette classe utilise SDL pour dessiner les objets projetés en 2D à partir d'une scène 3D.
 * Elle fournit des méthodes pour configurer l'écran, dessiner des formes et afficher le rendu.
 */
class Renderer {

private:
    int width_;               // Largeur de la fenêtre de rendu.
    int height_;              // Hauteur de la fenêtre de rendu.
    int pixelSize_;           // Taille des pixels utilisés pour le rendu.
    SDL_Window* window_;      // Pointeur vers la fenêtre SDL.
    SDL_Renderer* renderer_;  // Pointeur vers le renderer SDL.

    /**
     * @brief Trie les triangles projetés par profondeur.
     * @param triangles Les triangles à trier.
     */
    void sortTrianglesByDepth(std::vector<Triangle2D>& triangles) const;

    /**
     * @brief Projette un point 3D sur le plan 2D.
     * @param point3D Le point 3D à projeter.
     * @param eye La position de la caméra (œil).
     * @param projectionPlaneDistance La distance du plan de projection.
     * @return Le point projeté en 2D.
     */
    Point2D projectPoint(const Point3D& point3D, const Point3D& eye, float projectionPlaneDistance) const;

    /**
     * @brief Projette un triangle 3D sur le plan 2D.
     * @param triangle Le triangle 3D à projeter.
     * @param eye La position de la caméra (œil).
     * @param projectionPlaneDistance La distance du plan de projection.
     * @return Le triangle projeté en 2D.
     */
    Triangle2D projectTriangle(const Triangle3D& triangle, const Point3D& eye, float projectionPlaneDistance) const;  

public:
    /**
     * @brief Constructeur du renderer.
     * @param width Largeur de la fenêtre.
     * @param height Hauteur de la fenêtre.
     * @param pixelSize Taille des pixels pour le rendu (par défaut : 1).
     * @throw std::runtime_error Si l'initialisation de SDL ou la création de la fenêtre échoue.
     */
    Renderer(int width, int height, int pixelSize = 1);

    /**
     * @brief Destructeur du renderer.
     *
     * Libère les ressources SDL (fenêtre et renderer).
     */
    ~Renderer();

    /**
     * @brief Rendu d'une scène 3D en 2D.
     * @param scene La scène 3D à projeter et rendre.
     * @param translation2D La translation à appliquer aux objets projetés dans l'espace 2D.
     */
    void renderScene(const Scene3D& scene, const Point2D& translation2D);

    /**
     * @brief Présente l'image rendue à l'écran.
     */
    void present();

    /**
     * @brief Efface l'écran avec une couleur donnée.
     * @param color Couleur utilisée pour effacer l'écran (structure SDL_Color).
     */
    void clear(const SDL_Color& color);

    /**
     * @brief Récupère les triangles projetés des cubes de la scène.
     * @param scene La scène contenant le cube.
     * @return Un vecteur de triangles 2D projetés.
     */
    std::vector<Triangle2D> getProjectedTrianglesFromCubes(const Scene3D& scene) const;

    /**
     * @brief Récupère les triangles projetés des sphères de la scène.
     * @param scene La scène contenant la sphère.
     * @return Un vecteur de triangles 2D projetés.
     */
    std::vector<Triangle2D> getProjectedTrianglesFromSpheres(const Scene3D& scene) const;

    /**
     * @brief Récupère tous les triangles projetés de la scène.
     * @param scene La scène 3D à partir de laquelle les triangles sont projetés.
     * @return Un vecteur de triangles 2D projetés triés par profondeur.
     */
    std::vector<Triangle2D> getProjectedTriangles(const Scene3D& scene) const;

    /**
     * @brief Vérifie si un point est visible depuis la caméra.
     * @param point Le point à vérifier.
     * @param eye La position de l'œil.
     * @return Vrai si le point est visible, faux sinon.
     */
    bool isPointVisible(const Point3D& point, const Point3D& eye) const;

    /**
     * @brief Accesseur pour la hauteur de la fenêtre.
     * @return La hauteur de la fenêtre.
     */
    int getHeight() const { return height_; }

    /**
     * @brief Accesseur pour la largeur de la fenêtre.
     * @return La largeur de la fenêtre.
     */
    int getWidth() const { return width_; }

    /**
     * @brief Accesseur pour le renderer SDL.
     * @return Un pointeur constant vers le renderer SDL.
     */
    SDL_Renderer* getRenderer() const { return renderer_; }

    /**
     * @brief Rend le pavé 3D en le projetant en 2D et en le dessinant sur l'écran.
     * @param cube Un pointeur partagé vers l'objet Pave3D à rendre.
     * @param translation2D La translation en 2D à appliquer (déplacement sur l'écran).
     * @param translationZ La translation en profondeur (axe Z) à appliquer.
     * @param scene La scène 3D contenant les informations sur la caméra et la projection.
     */
    void renderCube(const std::shared_ptr<Pave3D>& cube, const Point2D& translation2D, float translationZ, const Scene3D& scene);
    
    /**
     * @brief Rend la sphère 3D en la projetant en 2D et en la dessinant sur l'écran.
     * @param sphere Un pointeur partagé vers l'objet Sphere3D à rendre.
     * @param translation La translation en 2D à appliquer (déplacement sur l'écran).
     * @param translationZ La translation en profondeur (axe Z) à appliquer.
     * @param scene La scène 3D contenant les informations sur la caméra et la projection.
     */
    void renderSphere(const std::shared_ptr<Sphere3D>& sphere, const Point2D& translation, float translationZ, const Scene3D& scene);

    /**
     * @brief Dessine un triangle rempli avec la couleur spécifiée.
     * @param renderer Pointeur vers le SDL_Renderer utilisé pour le rendu.
     * @param p1 Premier sommet du triangle en 2D.
     * @param p2 Deuxième sommet du triangle en 2D.
     * @param p3 Troisième sommet du triangle en 2D.
     * @param color Couleur du triangle.
     */
    void drawFilledTriangle(SDL_Renderer* renderer, const Point2D& p1, const Point2D& p2, const Point2D& p3, const Couleur& color);

    /**
     * @brief Rendu d'un triangle 3D après application de la translation et de la projection.
     * @param triangle Triangle 3D à rendre.
     * @param color Couleur du triangle.
     * @param translation Translation 2D à appliquer après la projection.
     * @param translationZ Translation en Z à appliquer avant la projection.
     * @param scene Scène 3D contenant les informations de caméra et de projection.
     */
    void renderTriangle(const Triangle3D& triangle, const Couleur& color, const Point2D& translation, float translationZ, const Scene3D& scene);

    /**
     * @brief Rendu d'un triangle 3D avec calcul automatique de la couleur.
     * @param triangle Triangle 3D à rendre.
     * @param translation Translation 2D à appliquer après la projection.
     * @param translationZ Translation en Z à appliquer avant la projection.
     * @param scene Scène 3D contenant les informations de caméra et de projection.
     */
    void renderTriangleWithColor(const Triangle3D& triangle, const Point2D& translation, float translationZ, const Scene3D& scene);

    /**
     * @brief Calcule la couleur d'un triangle 3D en fonction de divers paramètres.
     * @param triangle Triangle 3D dont la couleur doit être calculée.
     * @return Couleur calculée pour le triangle.
     */
    Couleur computeTriangleColor(const Triangle3D& triangle) const;


};

#endif // RENDERER_H