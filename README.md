# 42fdf - 3D Wireframe Renderer

42fdf is a 3D wireframe rendering project built using the MiniLibX library. It parses map files to generate 3D projections and displays them in an interactive window.

## Features
- Parses `.fdf` map files to create 3D models.
- Supports isometric projections.
- Interactive controls for rotation, zoom, and color changes.
- Gradient-based color rendering.

## File Overview
- **`main.c`**: Entry point of the program, handles initialization and cleanup.
- **`colors_utils.c`**: Manages color gradients and color modes.
- **`render.c`**: Handles rendering of 3D points and lines.
- **`parsing_utils.c`**: Parses map files and prepares data structures.
- **`fdf.h`**: Header file containing all function prototypes and structure definitions.

## How to Run
1. Compile the project using the provided Makefile:
   make

./fdf test_maps/example.fdf