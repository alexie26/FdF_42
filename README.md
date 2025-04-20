# 42fdf - 3D Wireframe Renderer

42fdf is a 3D wireframe rendering project built using the MiniLibX library. It parses map files to generate 3D projections and displays them in an interactive window.

## Features
- Parses `.fdf` map files to create 3D models.
- Supports isometric projections.
- Interactive controls for rotation, zoom, and color changes.
- Gradient-based color rendering.

## File Overview
## File Overview
- **`main.c`**: Entry point of the program, handles initialization, error handling, and cleanup.
- **`parsing.c`**: Parses the `.fdf` map files and extracts 3D data into the program's data structures.
- **`parsing2.c`**: Handles additional parsing logic, such as validating and processing map data.
- **`parsing_utils.c`**: Provides utility functions to assist with parsing, such as memory allocation and 	  error checking.
- **`render.c`**: Manages the rendering of 3D points and lines, including drawing connections between points.
- **`isometric.c`**: Converts 3D coordinates into 2D isometric projections for rendering.
- **`render_utils.c`**: Contains helper functions for rendering, such as initializing and updating line data.
- **`error_utils.c`**: Handles error messages and program termination in case of failures.
- **`hooks.c`**: Manages user input and event handling, such as key presses and mouse interactions.
- **`colors.c`**: Implements gradient-based color rendering and color interpolation.
- **`colors_utils.c`**: Provides utility functions for managing color modes and applying gradients.
- **`rotate.c`**: Handles rotation of the 3D model based on user input.
- **`max_min.c`**: Calculates the maximum and minimum values of the 3D data for scaling and normalization.


## How to Run
1. Compile the project using the provided Makefile:
   
   make

./fdf test_maps/example.fdf