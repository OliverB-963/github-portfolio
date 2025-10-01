//
// Created by olbai on 30/06/2025.
//

#ifndef QUEEN_H
#define QUEEN_H

#include "Piece.hpp"
#include "locators/MovementPath.hpp"

#include <vector>

class Queen final : public Piece{
    std::vector<MovementPath> movementPaths;

public:
    Queen(PieceType type, PieceColour colour, const Move &position);

    void calculateMoves(Board &board) override;

    bool isAttackingPosition(const Move &coord) const override;

    std::ostream &print(std::ostream &os) const override;
};



#endif //QUEEN_H
