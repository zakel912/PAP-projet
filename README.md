# **PAP Project 5**

Ce projet permet la visualisation d'bjets 3D, comme des pavés et des sphères, avec SDL2 pour le rendu.

---

## **Compilation et exécution**

### **Compiler les tests des classes objets (Point2d, Point3d, Triangle2D, etc..)**
Chaque test est dans `src/geometry/geometry_test`. Exemple :
```bash
g++ main_point2d.cpp point2d.cpp -o main

g++ main_point3d.cpp point3d.cpp -o main

g++ main_triangle2d.cpp triangle2d.cpp point2d.cpp ../couleur.cpp -o main

g++ main_triangle3d.cpp triangle3d.cpp point3d.cpp ../couleur.cpp -o main

g++ main_quad3d.cpp quad3d.cpp triangle3d.cpp point3d.cpp ../couleur.cpp -o main

g++ main_sphere3d.cpp sphere3d.cpp quad3d.cpp triangle3d.cpp point3d.cpp ../couleur.cpp -o main

g++ main_pave3d.cpp pave3d.cpp quad3d.cpp triangle3d.cpp point3d.cpp ../couleur.cpp -o main./main
```

### **Compiler les tests d'affichage des objets (Un cube, Une sphère, etc..)**
Chaque test est dans `src/geometry/object_test` et pour la scène dans src/scene/. Exemple :
```bash
g++ -o triangle2d_test main_triangle2d.cpp ../triangle2d.cpp ../point3d.cpp ../point2d.cpp ../../couleur.cpp -lSDL2

g++ -o triangle3d_test main_triangle3d.cpp ../triangle3d.cpp ../point3d.cpp ../point2d.cpp ../../couleur.cpp -lSDL2

g++ -o quad3d_test main_quad3d.cpp ../quad3d.cpp ../triangle3d.cpp ../point3d.cpp ../point2d.cpp ../../couleur.cpp -lSDL2

g++ -o pave3d_test main_pave3d.cpp ../pave3d.cpp ../quad3d.cpp ../triangle3d.cpp ../point3d.cpp ../point2d.cpp ../../couleur.cpp -lSDL2

g++ -o sphere3d_test main_sphere3d.cpp ../sphere3d.cpp ../pave3d.cpp ../quad3d.cpp ../triangle3d.cpp ../point3d.cpp ../point2d.cpp ../../couleur.cpp -lSDL2

g++ main_scene3d.cpp ../geometry/pave3d.cpp ../geometry/sphere3d.cpp ../geometry/triangle2d.cpp ../geometry/point3d.cpp ../geometry/point2d.cpp ../geometry/quad3d.cpp ../geometry/triangle3d.cpp  ../couleur.cpp scene3d.cpp -o main
```

### **Compiler le programme principale src/main.cpp**
```bash
g++ -o main main.cpp sdl/renderer.cpp scene/scene3d.cpp geometry/pave3d.cpp geometry/sphere3d.cpp geometry/point3d.cpp geometry/point2d.cpp geometry/quad3d.cpp geometry/triangle3d.cpp couleur.cpp -lSDL2
./main
```

### Dépendances
Installez SDL2 avant de compiler :
```bash
sudo apt-get install libsdl2-dev
```

## Fonctionnalités principales pour le programme principale

### Rendu dynamique
- Visualisation en 3D d'un cube rouge et d'une sphère verte.
- Application d'un dégradé de couleurs basé sur la profondeur et la position des faces.

### Interaction clavier
- **Déplacement de l'objet sélectionné :**
  - Flèches : Déplacer vers le haut, le bas, la gauche ou la droite.
  - KP_1 / KP_2 : Avancer ou reculer sur l'axe Z.
- **Rotation de l'objet :**
  - A / Z : Rotation autour de l'axe X.
  - E / R : Rotation autour de l'axe Y.
  - T / Y : Rotation autour de l'axe Z.
- **Déplacement de la caméra :**
  - W / X : Déplacer la caméra vers le haut ou le bas.
  - B / N : Déplacer la caméra vers la droite ou la gauche.
  - C / V : Avancer ou reculer la caméra.
- **Autres commandes :**
  - TAB : Alterner entre le pavé et la sphère.
  - ÉCHAP : Quitter le programme.

### Personnalisation
- Modifiez les dimensions de l'écran en ajustant SCREEN_WIDTH et SCREEN_HEIGHT.
- Changez la position et la taille des objets directement dans le fichier main.cpp.
- Ajustez les vitesses de déplacement et de rotation en modifiant MOVE_STEP et ROTATE_STEP.


### Auteur
EL MRANI Zakaria & Sié KAMBIRE
