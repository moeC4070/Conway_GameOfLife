Conway's Game of Life

A C++ implementation of Conway's Game of Life, built with SDL3. Explore cellular automata through a graphical grid where simple rules create evolving patterns.

Overview

Conway's Game of Life is a cellular automaton introduced by mathematician John Conway. It simulates the evolution of cells across a grid, with each cell being either alive or dead.

Despite its simple rules, the simulation can produce fascinating patterns and complex behavior.

Features
🎮 Interactive graphical simulation powered by SDL3
🔲 A 60 × 30 grid of cells
🖱️ Click cells to toggle between alive and dead states
▶️ Press Space to start the simulation
🧬 Automatic generation updates based on Conway's rules
⚙️ C++20 implementation
🖥️ Resizable application window
Game Rules

Each cell interacts with its eight neighboring cells.

Underpopulation: A live cell with fewer than two live neighbors dies.
Survival: A live cell with two or three live neighbors survives.
Overpopulation: A live cell with more than three live neighbors dies.
Reproduction: A dead cell with exactly three live neighbors becomes alive.

These rules are applied repeatedly to generate new states and patterns.

Tech Stack
Language: C++20
Graphics and window management: SDL3
Build system: GNU Make
Compiler: g++
Getting Started
Prerequisites
A C++ compiler supporting C++20
GNU Make
SDL3 development files and libraries compatible with the project
A compatible environment for the provided Makefile

Build the project

The provided Makefile is configured to build a Windows executable.

make


The build configuration expects the SDL3 headers in include/ and the SDL3 library in lib/.

Run the application
make run


The executable is configured as build/GameOfLife.exe. Ensure the required SDL3 runtime libraries are available when launching the application.



This project explores:

Cellular automata and simulation logic
C++ programming and data structures
Event handling and real-time rendering
Integration of SDL3 into a C++ application
Build automation with Make
Author

moeC4070

GitHub: @moeC4070
Repository: Conway_GameOfLife
License

No license is currently specified in the repository. Please add a LICENSE file if you intend to define permissions for reuse and distribution.
