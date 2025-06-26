cmake_minimum_required(VERSION 3.31)

# Set the project name and version
project(flappy_bird_sfml LANGUAGES CXX)

# Set the C++ standard to C++20
set(CMAKE_CXX_STANDARD 20)

# Set the output directories for the executable and libraries
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Find and include the SFML library
include(FetchContent)
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 3.0.1
        GIT_SHALLOW ON
        EXCLUDE_FROM_ALL
        SYSTEM
)
FetchContent_MakeAvailable(SFML)

# Set the Executable target
add_executable(flappy_bird
        src/main.cpp
        src/Game.cpp
        src/AssetManager.cpp
        src/GameStateManager.cpp
        src/MenuState.cpp
        src/PlayState.cpp
        src/GameOverState.cpp
        src/Player.cpp
        src/Pipe.cpp
        src/PipeManager.cpp
        src/Background.cpp
        src/ScoreManager.cpp
)

# Include directories for the SFML library
target_include_directories(flappy_bird PRIVATE
        include
)

# Set the C++ standard and link SFML libraries
target_compile_features(flappy_bird PRIVATE cxx_std_20)
target_link_libraries(flappy_bird PRIVATE
        SFML::Graphics
        SFML::Window
        SFML::System
        SFML::Audio
        SFML::Network
)

# Copy assets to the output directory
file(COPY assets DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})