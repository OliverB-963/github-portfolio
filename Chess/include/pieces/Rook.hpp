//
// Created by olbai on 30/06/2025.
//

#ifndef ROOK_H
#define ROOK_H

#include "Piece.hpp"
#include "locators/MovementPath.hpp"

#include <vector>

class Rook final : public Piece{
    std::vector<MovementPath> movementPaths;
    bool beenMoved;

public:
    Rook(PieceType type, PieceColour colour, Move position, bool beenMoved);

    void calculateMoves(Board &board) override;

    bool isAttackingPosition(const Move &coord) const override;

    bool getBeenMoved() const override;
    void setBeenMoved(bool newBeenMoved) override;
};



#endif //ROOK_H
