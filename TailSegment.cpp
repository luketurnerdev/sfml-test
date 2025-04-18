//
// Created by luke on 18/04/2025.
//

#include "TailSegment.h"

#include <deque>

TailSegment::TailSegment(const sf::Texture &texture, const Position &startPos, size_t followDelay)
    : MoveableObject(texture, startPos), delayFrames_(followDelay) {}

void TailSegment::updateFromHistory(const std::deque<Position> &history, const sf::RenderWindow& window) {
    if (history.size() > delayFrames_) {
        setPosition(history[delayFrames_], window);
    }
}

