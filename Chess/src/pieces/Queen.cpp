//
// Created by olbai on 30/06/2025.
//

#include "pieces/Queen.hpp"

Queen::Queen(const PieceType type, const PieceColour colour, const Move &position)
    : Piece(type, colour, position) {
}

void Queen::calculateMoves(Board &board) {
    movementPaths = laserMovement(board, this, BISHOP_MOVEMENTS);

    std::vector<MovementPath> temp = laserMovement(board, this, ROOK_MOVEMENTS);

    std::ranges::copy(temp, std::back_inserter(movementPaths));

    moves = MovementPath::generateAllMoves(movementPaths);
}

bool Queen::isAttackingPosition(const Move &coord) const {
    return MovesCollisionCheck(moves, coord);
}

std::ostream &Queen::print(std::ostream &os) const {
    Piece::print(os);

    // os << '\n';
    // for (const MovementPath &movementPath : movementPaths) {
    //     os << movementPath << ", "; TODO remove this
    // }

    return os;
}
