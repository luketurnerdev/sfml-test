//
// Created by luke on 9/04/2025.
//
#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include "position.h"
class MoveableObject {
public:
    //Constructor
    MoveableObject(const sf::Texture& texture, const Position& startPos);

    // // Getter for movement speed increment
    // float& getMovementIncrement() const;

    // Getter for sprite (so we can draw it elsewhere)
    const sf::Sprite& getSprite() const;

    // position stuff
    const Position& getPosition() const;
    void setPosition(const Position& newPos);

private:
    Position position_;
    float movementIncrement_;
    const sf::Texture texture_;
    sf::Sprite sprite_;
};

#endif //PLAYER_H
