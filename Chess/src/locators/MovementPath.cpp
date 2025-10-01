//
// Created by Oliver Bailey on 01/07/2025.
//

#include "locators/MovementPath.hpp"

MovementPath::MovementPath(const Move startPosition, const Move endPosition, const Move pinPosition)
    : startPosition(startPosition), endPosition(endPosition), pinnedKingPosition(pinPosition) {}

bool MovementPath::pathCollidesWith(const Move &position) const {
    // If the move path is of a bishops
    if (startPosition.x != endPosition.x && startPosition.y != endPosition.y
            && (startPosition.x < position.x <= endPosition.x || endPosition.x < position.x <= startPosition.x)
            && (startPosition.y < position.y <= endPosition.y || endPosition.y < position.y <= startPosition.y)) {
        return true;
    }
    // If the move path is of a rooks going vertically
    if (startPosition.x != endPosition.x
            && (startPosition.x < position.x <= endPosition.x || endPosition.x < position.x <= startPosition.x)) {
        return true;
    }
    // If the move path is of a rooks going horizontally
    if (startPosition.y != endPosition.y
            && (startPosition.y < position.y <= endPosition.y || endPosition.y < position.y <= startPosition.y)) {
        return true;
    }

    return false;
}

std::vector<Move> MovementPath::generateMoves() const {
    std::vector<Move> movesOnPath;
    std::array directionMultiplier{endPosition.x - startPosition.x, endPosition.y - startPosition.y}; // -5, 5
    int distance;

    if (startPosition.x != endPosition.x) // If the move path is of a rooks going vertically
        distance = std::abs(endPosition.x - startPosition.x);
    else
        distance = std::abs(endPosition.y - startPosition.y);

    directionMultiplier[0] /= distance;
    directionMultiplier[1] /= distance;

    for (int i = 1; i < distance; ++i) {
        movesOnPath.emplace_back(std::array{startPosition.x + i * directionMultiplier[0], startPosition.y + i * directionMultiplier[1]}, MoveType::Empty);
    }
    movesOnPath.emplace_back(endPosition, endPosition.type);

    return movesOnPath;
}

bool MovementPath::containsPin() const {
    return pinnedKingPosition.type != MoveType::None;
}

std::vector<Move> MovementPath::generateAllMoves(const std::vector<MovementPath> &movementPaths) {
    std::vector<Move> allMoves;

    for (const MovementPath& movementPath : movementPaths) {
        std::vector<Move> temp = movementPath.generateMoves();

        std::ranges::copy(temp, std::back_inserter(allMoves));
    }

    return allMoves;
}

std::ostream &operator<<(std::ostream &os, const MovementPath &movementPath) {
    return os << "{" << movementPath.startPosition << " <-> " << movementPath.endPosition << "}";
}