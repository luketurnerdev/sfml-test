//
// Created by luke on 9/04/2025.
//
#include <SFML/Graphics/RenderWindow.hpp>

#include "Position.h"

#ifndef UTILS_H
#define UTILS_H

Position ClampToWindow(const Position& desiredPos, const sf::RenderWindow& window, sf::Sprite& sprite);

#endif //UTILS_H
