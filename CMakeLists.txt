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
add_executable(sfmlTest main.cpp
        Player.h
        Position.h
        snakeGame.cpp
        snakeGame.h
)

# Link SFML libraries (assuming you're using dynamic linking with DLLs)
target_link_libraries(sfmlTest
        sfml-graphics
        sfml-window
        sfml-system
)
