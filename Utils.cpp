//
// Created by luke on 9/04/2025.
//

#include "Utils.h"

#include <iostream>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include <random>;
#include "Boundary.h"
#include "position.h"

Position ClampToWindow(const Position& desiredPos, const sf::RenderWindow& window, sf::Sprite& sprite) {
    //desiredPos is where they tried to move
    // This method will return the actual allowed position based on the window bounds


    const float maxX = window.getSize().x - sprite.getGlobalBounds().size.x;
    const float maxY = window.getSize().y - sprite.getGlobalBounds().size.y;;

    Position allowedPosition {desiredPos.x, desiredPos.y};

    // Min bounds
    if (desiredPos.x < 0) {allowedPosition.x = 0;}
    if (desiredPos.y < 0) {allowedPosition.y = 0;}

    //Max bounds
    if (desiredPos.x > maxX) {
        allowedPosition.x = maxX;
    }
    if (desiredPos.y > maxY) {
        allowedPosition.y = maxY;
    }

    return allowedPosition;
}

Boundary DetermineSpriteBoundary(const sf::Sprite& sprite, const Position& spritePositionInSpace) {
    // Return the absolute position of the corner pixels of the sprite

    // Eg sprite is at {10,10} position, and it is 32 pixels wide and tall
    const Position topLeft = {spritePositionInSpace.x, spritePositionInSpace.y};
    const Position topRight = {spritePositionInSpace.x + sprite.getLocalBounds().size.x, spritePositionInSpace.y};
    const Position bottomLeft = {spritePositionInSpace.x,spritePositionInSpace.y + sprite.getLocalBounds().size.y};
    const Position bottomRight = {spritePositionInSpace.x + sprite.getLocalBounds().size.x, spritePositionInSpace.y + sprite.getLocalBounds().size.y};

    return Boundary{
        topLeft,
        topRight,
        bottomLeft,
        bottomRight
    };
}

int RandomNumber(int min, int max) {
    std::random_device rd; // random_device gets a seed from the hardware of the pc every compilation
    std::mt19937 gen(rd()); // Use the mersenne-twister engine to generate the number with the rd seed
    std::uniform_int_distribution<> distribution(min,max); // Generate a range of ints, with an even distribution (equal amount of chance of being chosen)

    return distribution(gen); // Generate the random number with our engine, within our range
}


Logger::Logger(float intervalInSeconds) : interval(intervalInSeconds) {}

void Logger::LogIfReady(const std::string& message) {
    if (clock.getElapsedTime().asSeconds() >= interval) {
        std::cout << message << std::endl;
        clock.restart();
    }
}

void LogBoundary(const Boundary& boundary, Logger& logger) {
    const std::string boundaryLog = std::format("Player boundary: [{}, {}], [{}, {}], [{}, {}], [{}, {}]", boundary.topLeftCorner.x, boundary.topLeftCorner.y, boundary.topRightCorner.x, boundary.topRightCorner.y, boundary.bottomLeftCorner.x, boundary.bottomLeftCorner.y, boundary.bottomRightCorner.x, boundary.bottomRightCorner.y);
    logger.LogIfReady(boundaryLog);
}
