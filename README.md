# Flappy Bird SFML

A simple Flappy Bird clone built with C++ and [SFML](https://www.sfml-dev.org/).

## Features

- Basic Flappy Bird gameplay (WIP)
- Uses SFML for graphics, audio, and input
- Easy to build with CMake

## Prerequisites

- C++20 compatible compiler (e.g., GCC, Clang, MSVC)
- [CMake](https://cmake.org/) 3.31 or newer
- Git

## Building and Running

1. **Clone the repository:**
   ```sh
   git clone https://github.com/rahulc0dy/flappy-bird-sfml.git
   cd flappy-bird-sfml
   ```

2. **Configure and build the project:**
   ```sh
   cmake -S . -B build
   cmake --build build
   ```

3. **Run the game:**
   ```sh
   ./build/bin/flappy_bird
   ```
   On Windows, run:
   ```
   .\build\bin\flappy_bird.exe
   ```

## Assets

All required assets (sprites, fonts, sounds) are included in the `assets` directory and are automatically copied to the build output.

## Notes

- The project uses SFML 3.0.1, which is fetched automatically by CMake.
- Make sure your system supports OpenGL and audio playback.

## License

This project is for educational purposes.
