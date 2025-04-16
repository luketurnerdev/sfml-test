//
// Created by luke on 9/04/2025.
//

#include "MoveableObject.h"
#include "Utils.h"
#include <SFML/Graphics.hpp>

// ":" section --> member initializer list
MoveableObject::MoveableObject(const sf::Texture& texture, const Position& startPos, float movementIncrement, MovementDirection startingMoveDirection)
    : position_(startPos), movementIncrement_(movementIncrement), texture_(texture), sprite_(texture_), currentMovementDirection_(startingMoveDirection)
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

const Boundary &MoveableObject::getBoundary() const {
    return boundary_;
}

const MoveableObject::MovementDirection& MoveableObject::getCurrentMovementDirection() const {
    return currentMovementDirection_;
}


// Setters
void MoveableObject::setPosition(const Position& newPos, const sf::RenderWindow& window) {
    const Position validPos = ClampToWindow(newPos, window, sprite_);
    position_ = validPos;
    // Update sprite position and boundary
    sprite_.setPosition(sf::Vector2f(position_.x, position_.y));

    // Also update the boundary box
    setBoundary();
}

void MoveableObject::setCurrentMovementDirection(MoveableObject::MovementDirection newDirection) {
    currentMovementDirection_ = newDirection;
}

void MoveableObject::setBoundary() {
    const Boundary boundary = DetermineSpriteBoundary(sprite_, position_);
    boundary_ = boundary;
}



