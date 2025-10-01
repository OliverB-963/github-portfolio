//
// Created by olbai on 30/06/2025.
//

#ifndef KNIGHT_H
#define KNIGHT_H

#include "Piece.hpp"
#include "locators/MovementPath.hpp"

#include <vector>

class Knight final : public Piece{

public:
    Knight(PieceType type, PieceColour colour, Move position);

    void calculateMoves(Board &board) override;

    bool isAttackingPosition(const Move &coord) const override;
};



#endif //KNIGHT_H
