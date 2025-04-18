//
// Created by luke on 18/04/2025.
//

#ifndef TAILSEGMENT_H
#define TAILSEGMENT_H


#include <deque>

#include "MoveableObject.h"

class TailSegment : public MoveableObject {
public:
    TailSegment(const sf::Texture& texture, const Position& startPos, size_t followDelay);
    void updateFromHistory(const std::deque<Position>& history, const sf::RenderWindow& window);
private:
    size_t delayFrames_;

};
#endif //TAILSEGMENT_H
