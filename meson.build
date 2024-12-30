project('3d_scene', 'cpp', version: '1.0', default_options: ['cpp_std=c++17'])

# SDL2 dependency
sdl2_dep = dependency('sdl2')

# Include directories
inc_dirs = include_directories(
    'src/geometry',
    'src/scene',
    'src/sdl',
)

# Sources
sources = files(
    'src/main.cpp',
    'src/geometry/point3d.cpp',
    'src/geometry/triangle3d.cpp',
    'src/geometry/quad3d.cpp',
    'src/geometry/pave3d.cpp',
    'src/geometry/sphere3d.cpp',
    'src/scene/scene3d.cpp',
)

# Build the executable
executable(
    'main',
    sources: sources,
    include_directories: inc_dirs,
    dependencies: sdl2_dep,
    cpp_args: ['-DSDL_MAIN_HANDLED']
)