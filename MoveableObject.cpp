﻿//
// Created by luke on 9/04/2025.
//

#include "MoveableObject.h"
#include "Utils.h"
#include <SFML/Graphics.hpp>

// ":" section --> member initializer list
MoveableObject::MoveableObject(const sf::Texture& texture, const Position& startPos, float movementIncrement)
    : position_(startPos), movementIncrement_(movementIncrement), texture_(texture), sprite_(texture_)
{
    sprite_.setPosition(sf::Vector2f(position_.x, position_.y));
}

float MoveableObject::getMovementIncrement() const {
    return movementIncrement_;
}

const sf::Sprite& MoveableObject::getSprite() const {
    return sprite_;
}

const Position &MoveableObject::getPosition() const {
    return position_;
}

void MoveableObject::setPosition(const Position& newPos, const sf::RenderWindow& window) {
    Position validPos = ClampToWindow(newPos, window, sprite_);
    position_ = validPos;
    sprite_.setPosition(sf::Vector2f(position_.x, position_.y));
}


