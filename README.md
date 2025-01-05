# PAP_project_5

Compiler : g++ -g -Wall -Wextra -o prog main.cpp geometry/*.cpp sdl/renderer.cpp scene/scene3d.cpp couleur.cpp $(pkg-config --cflags --libs sdl2)

commande pour lancer les test et sdl :

g++ main_point2d.cpp point2d.cpp -o main

g++ main_point3d.cpp point3d.cpp -o main

g++ main_triangle2d.cpp triangle2d.cpp point2d.cpp ../couleur.cpp -o main

g++ main_triangle3d.cpp triangle3d.cpp point3d.cpp ../couleur.cpp -o main

g++ main_quad3d.cpp quad3d.cpp triangle3d.cpp point3d.cpp ../couleur.cpp -o main

g++ main_sphere3d.cpp sphere3d.cpp quad3d.cpp triangle3d.cpp point3d.cpp ../couleur.cpp -o main

g++ main_pave3d.cpp pave3d.cpp quad3d.cpp triangle3d.cpp point3d.cpp ../couleur.cpp -o main

g++ main_scene3d.cpp ../geometry/pave3d.cpp ../geometry/sphere3d.cpp ../geometry/triangle2d.cpp ../geometry/point3d.cpp ../geometry/point2d.cpp ../geometry/quad3d.cpp ../geometry/triangle3d.cpp  ../couleur.cpp scene3d.cpp -o main

meson compile -C build

./build/3d_scene

g++ -o pave3d_test main_pave3d.cpp ./geometry/pave3d.cpp ./geometry/quad3d.cpp ./geometry/triangle3d.cpp ./geometry/point3d.cpp ./geometry/point2d.cpp couleur.cpp -lSDL2

g++ -o sphere3d_test main_sphere3d.cpp ./geometry/sphere3d.cpp ./geometry/pave3d.cpp ./geometry/quad3d.cpp ./geometry/triangle3d.cpp ./geometry/point3d.cpp ./geometry/point2d.cpp couleur.cpp -lSDL2
