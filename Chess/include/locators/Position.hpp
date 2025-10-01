//
// Created by Oliver Bailey on 05/07/2025.
//

#ifndef COORD_H
#define COORD_H

#include "SFML/Graphics.hpp"

class Move;

class Position {
public:
    int x;
    int y;

    explicit Position(sf::Vector2i posToConvert);

    double distanceBetween(Position otherPosition) const;

    std::string str() const;

    // friend std::ostream& operator<<(std::ostream& os, const Position& position);
};

#endif //COORD_H
