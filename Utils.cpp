//
// Created by luke on 9/04/2025.
//

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>

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