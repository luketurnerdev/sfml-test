﻿//
// Created by luke on 9/04/2025.
//
#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include "position.h"
class MoveableObject {
public:
    //Constructor
    MoveableObject(const sf::Texture& texture, const Position& startPos, float movementIncrement = 0.0f);

    // Getter for sprite (so we can draw it elsewhere)
    const sf::Sprite& getSprite() const;

    // position stuff
    const Position& getPosition() const;
    void setPosition(const Position& newPos, const sf::RenderWindow& window);

    // Movement
    void setMovementIncrement(float);
    float getMovementIncrement() const;

private:
    Position position_;

    // Default value because some of our instances (i.e., food) don't need movespeed
    float movementIncrement_ = 0.0f;
    const sf::Texture texture_;
    sf::Sprite sprite_;
};

#endif //PLAYER_H
