//
// Created by olbai on 30/06/2025.
//

#include "pieces/Rook.hpp"

#include "Board.hpp"

Rook::Rook(const PieceType type, const PieceColour colour, const Move position, const bool beenMoved)
    : Piece(type, colour, position), beenMoved(beenMoved) {
}

void Rook::calculateMoves(Board &board) {
    movementPaths = laserMovement(board, this, ROOK_MOVEMENTS);

    moves = MovementPath::generateAllMoves(movementPaths);
}

bool Rook::isAttackingPosition(const Move &coord) const {
    return MovesCollisionCheck(moves, coord);
}


bool Rook::getBeenMoved() const {return beenMoved;}
void Rook::setBeenMoved(const bool newBeenMoved) {beenMoved = newBeenMoved;}