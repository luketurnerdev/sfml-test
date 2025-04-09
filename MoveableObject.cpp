//
// Created by luke on 9/04/2025.
//

#include "Player.h"
#include <SFML/Graphics.hpp>
#include <iostream>

// ":" section --> member initializer list
Player::Player(const sf::Texture& texture, const Position& startPos)
    : position_(startPos), texture_(texture), sprite_(texture_)
{
    sprite_.setPosition(sf::Vector2f(position_.x, position_.y));
}

const sf::Sprite& Player::getSprite() const {
    return sprite_;
}

const Position &Player::getPosition() const {
    return position_;
}

void Player::setPosition(const Position& newPos) {
    position_ = newPos;
    sprite_.setPosition(sf::Vector2f(position_.x, position_.y));
}


