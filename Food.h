//
// Created by luke on 9/04/2025.
//

#ifndef FOOD_H
#define FOOD_H
#include "MoveableObject.h"

class Food : public MoveableObject {
public:
    Food(const sf::Texture& texture, const Position& spawnPos);

private:

};
#endif //FOOD_H
