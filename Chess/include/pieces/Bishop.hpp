//
// Created by olbai on 30/06/2025.
//

#ifndef BISHOP_H
#define BISHOP_H

#include "Piece.hpp"
#include "locators/MovementPath.hpp"

#include <vector>

class Bishop final : public Piece{
    std::vector<MovementPath> movementPaths;

public:
    Bishop(PieceType type, PieceColour colour, const Move &position);

    void calculateMoves(Board &board) override;

    bool isAttackingPosition(const Move &coord) const override;
};



#endif //BISHOP_H
