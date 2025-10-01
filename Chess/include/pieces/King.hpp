//
// Created by olbai on 30/06/2025.
//

#ifndef KING_H
#define KING_H

#include "Piece.hpp"
#include "locators/Move.hpp"

#include <vector>

class King final : public Piece {
    bool beenMoved;

public:
    King(PieceType type, PieceColour colour, Move position, bool beenMoved);

    void calculateMoves(Board &board) override;

    bool isAttackingPosition(const Move &coord) const override;

    bool getBeenMoved() const override;
    void setBeenMoved(bool newBeenMoved) override;

    void addCastleMove(int x, int y);
};

#endif //KING_H