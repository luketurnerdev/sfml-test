//
// Created by luke on 9/04/2025.
//
#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include "position.h"
class Player {
public:
    //Constructor
    Player(const sf::Texture& texture, const Position& startPos);

    // Getter for sprite (so we can draw it elsewhere)
    const sf::Sprite& getSprite() const;

    // position stuff
    const Position& getPosition() const;
    void setPosition(const Position& newPos);

private:
    Position position_;
    const sf::Texture texture_;
    sf::Sprite sprite_;
};

#endif //PLAYER_H
