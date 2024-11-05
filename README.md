# Fdf Project

## Overview
The **Fdf** project at 42 involves creating a C program that generates a 3D graphical representation of a terrain map from an input file. This project allows you to work with basic graphics programming in C, using data from `.fdf` files to render a 3D terrain model in an isometric perspective. The project develops your skills in graphics transformations, memory handling, and rendering techniques.

## Project Objectives
- Understand the basics of 3D projection and isometric transformations.
- Learn to implement graphic rendering techniques from scratch.
- Manage image data dynamically and work with coordinate transformations.
- Develop a reusable graphic renderer that can handle other 3D projections in future projects.

## Project Requirements
- **Language**: C
- **Libraries**: mlx (MiniLibX)
- **Compilation Flags**: -Wall -Wextra -Werror
- **Output**: Executable file that reads `.fdf` files and displays them in a graphical window
- **Makefile**: Required with rules `all`, `clean`, `fclean`, `re`, and possibly `bonus`.

## Learning Goals
- Understand the mathematical concepts behind isometric projections.
- Develop memory management skills to handle graphical and pixel manipulation.
- Improve understanding of graphics programming concepts such as line-drawing algorithms.
- Enhance skills with Makefiles, compilation flags, and shell commands.

## Instructions

You will implement the main functions needed to read a `.fdf` file and render it in a 3D isometric view. Key components include:

- **File Parsing**: Read and parse the `.fdf` file, which contains a matrix of height values for the terrain.
- **Coordinate Transformation**: Apply transformations to convert 3D points into 2D coordinates using an isometric projection.
- **Graphics Rendering**: Render each line segment with appropriate depth based on the height values.

### Bonus Part: Additional 3D Effects
For additional functionality, you may add features such as:

- **Zoom and Rotation**: Allow the user to zoom in/out and rotate the map for better visualization.
- **Custom Projection**: Experiment with different types of projections (such as perspective or custom angles).
- **Interactive Controls**: Add keyboard or mouse support for interactive viewing.

## Cloning the Repository
To clone the repository with its submodules, use the following command:

```bash
git clone --recurse-submodules git@github.com:JaigonzaDev/Fdf.git Fdf
