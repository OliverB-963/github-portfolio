//
// Created by Oliver Bailey on 01/07/2025.
//

#ifndef MOVEMENTPATH_H
#define MOVEMENTPATH_H

#include "Move.hpp"

#include <vector>

class MovementPath {
    const Move startPosition;
    const Move endPosition;
    const Move pinnedKingPosition;

public:
    MovementPath(Move startPosition, Move endPosition, Move pinPosition = Move({0, 0}, MoveType::None));

    bool pathCollidesWith(const Move& position) const;

    std::vector<Move> generateMoves() const;

    bool containsPin() const;

    static std::vector<Move> generateAllMoves(const std::vector<MovementPath> &movementPaths);

    friend std::ostream &operator<<(std::ostream &os, const MovementPath &movementPath);

};

#endif //MOVEMENTPATH_H
