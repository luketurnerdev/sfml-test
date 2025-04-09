//
// Created by luke on 9/04/2025.
//

#include "MoveableObject.h"
#include <SFML/Graphics.hpp>

// ":" section --> member initializer list
MoveableObject::MoveableObject(const sf::Texture& texture, const Position& startPos)
    : position_(startPos), texture_(texture), sprite_(texture_)
{
    sprite_.setPosition(sf::Vector2f(position_.x, position_.y));
}

const sf::Sprite& MoveableObject::getSprite() const {
    return sprite_;
}

const Position &MoveableObject::getPosition() const {
    return position_;
}

void MoveableObject::setPosition(const Position& newPos) {
    position_ = newPos;
    sprite_.setPosition(sf::Vector2f(position_.x, position_.y));
}


