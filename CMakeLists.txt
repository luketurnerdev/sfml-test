cmake_minimum_required(VERSION 3.30)
project(sfmlTest)

set(CMAKE_CXX_STANDARD 20)

# Path to SFML
set(SFML_DIR "C:/SFML")

# Include directories
include_directories(
        ${SFML_DIR}/include
        ${PROJECT_SOURCE_DIR}/headers
)

# Link directories
link_directories(${SFML_DIR}/lib)

# Executable
add_executable(sfmlTest
        main.cpp
        snakeGame.cpp
        snakeGame.h
        MoveableObject.cpp
        MoveableObject.h
        Position.h
        Food.h
        Food.cpp
        Utils.h
        Utils.cpp
        Boundary.h
        Boundary.cpp
        CollisionManager.h
        CollisionManager.cpp
        Player.h
        Player.cpp
        SpawnManager.h
        SpawnManager.cpp
)

# Link SFML dynamic libraries (no -s suffix)
target_link_libraries(sfmlTest
        sfml-graphics
        sfml-window
        sfml-system
)
