cmake_minimum_required(VERSION 3.31)

set(CMAKE_SYSTEM_NAME Windows)
set(CMAKE_C_COMPILER ${CMAKE_CURRENT_SOURCE_DIR}/mingw64/bin/gcc.exe)
set(CMAKE_CXX_COMPILER ${CMAKE_CURRENT_SOURCE_DIR}/mingw64/bin/g++.exe)

project(flappy_bird_sfml)

set(CMAKE_CXX_STANDARD 20)

add_executable(flappy_bird_sfml
        src/main.cpp
)

# Link directories
link_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/lib
        ${CMAKE_CURRENT_SOURCE_DIR}/bin
)

# SFML
target_link_libraries(flappy_bird_sfml PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/libsfml-graphics.a
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/libsfml-audio.a
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/libsfml-window.a
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/libsfml-system.a
)


target_include_directories(flappy_bird_sfml PRIVATE
    include
)

# Copy assets to the output directory
file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})

# Copy SFML DLLs to the output directory
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/bin/sfml-graphics-3.dll
     ${CMAKE_CURRENT_SOURCE_DIR}/bin/sfml-audio-3.dll
     ${CMAKE_CURRENT_SOURCE_DIR}/bin/sfml-window-3.dll
     ${CMAKE_CURRENT_SOURCE_DIR}/bin/sfml-system-3.dll
     DESTINATION ${CMAKE_BINARY_DIR}
)
