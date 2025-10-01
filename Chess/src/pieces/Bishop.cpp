//
// Created by olbai on 30/06/2025.
//

#include "pieces/Bishop.hpp"

#include <array>

#include "Board.hpp"

Bishop::Bishop(const PieceType type, const PieceColour colour, const Move &position)
    : Piece(type, colour, position) {
}

void Bishop::calculateMoves(Board &board) {
    movementPaths = laserMovement(board, this, BISHOP_MOVEMENTS);

    moves = MovementPath::generateAllMoves(movementPaths);
}

bool Bishop::isAttackingPosition(const Move &coord) const {
    return MovesCollisionCheck(moves, coord);

}
