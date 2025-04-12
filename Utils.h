//
// Created by luke on 9/04/2025.
//
#include <SFML/Graphics.hpp>

#include "Boundary.h"
#include "Position.h"

#ifndef UTILS_H
#define UTILS_H

Position ClampToWindow(const Position& desiredPos, const sf::RenderWindow& window, sf::Sprite& sprite);
Boundary DetermineSpriteBoundary(const sf::Sprite& sprite, const Position& spritePositionInSpace);
class Logger {
public:
    explicit Logger(const float intervalInSeconds);
    void LogIfReady(const std::string& message);

private:
    float interval;
    sf::Clock clock;
};

void LogBoundary(const Boundary& boundary, Logger& logger);

#endif //UTILS_H
