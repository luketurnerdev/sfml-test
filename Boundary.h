//
// Created by luke on 12/04/2025.
//

#ifndef BOUNDARY_H
#define BOUNDARY_H
/*
 * This file should be a data definition of the boundary of a sprite (the player or an object)
 * The boundary of a sprite should be the x and y coords of the pixels where the sprite ends.
 */
#include "Position.h"
#include <SFML/Graphics.hpp>

// Forward declaration to avoid circular import

class MoveableObject;
struct Boundary {
    Position topLeftCorner;
    Position topRightCorner;
    Position bottomLeftCorner;
    Position bottomRightCorner;
};

sf::VertexArray CreateBoundarySquare(const Boundary& boundaryToDraw);

void DrawBoundarySquareOnScreenThisFrame(const MoveableObject& object, sf::RenderWindow& window);

#endif //BOUNDARY_H
