//
// Created by olbai on 30/06/2025.
//

#ifndef PAWN_H
#define PAWN_H

#include "Piece.hpp"
#include "locators/MovementPath.hpp"

#include <vector>

class Pawn final : public Piece{
    bool beenMoved;

public:
    Pawn(PieceType type, PieceColour colour, Move position, bool beenMoved);

    void calculateMoves(Board &board) override;

    bool isAttackingPosition(const Move &coord) const override;

    bool getBeenMoved() const override;
    void setBeenMoved(bool newBeenMoved) override;

private:
    void calculateAttackMove(Board &board, const Move &newMove);

    void calculatePromotionMoves();

    bool enpassantPossible(Board &board, const Move &enpassantMove) const;
};



#endif //PAWN_H
