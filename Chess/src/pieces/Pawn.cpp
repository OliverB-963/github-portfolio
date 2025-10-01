//
// Created by olbai on 30/06/2025.
//

#include "pieces/Pawn.hpp"

#include <array>

#include "Board.hpp"

Pawn::Pawn(const PieceType type, const PieceColour colour, const Move position, const bool beenMoved)
    : Piece(type, colour, position), beenMoved(beenMoved) {
}

void Pawn::calculateMoves(Board &board) {
    moves.clear();

    const bool isWhite = colour == PieceColour::White;
    int colourMultiplier; // for going up or down correctly for the colour

    if (!isWhite)
        colourMultiplier = 1;
    else
        colourMultiplier = -1;

    if (colour == PieceColour::White && currentPosition.x == 0
            || colour == PieceColour::Black && currentPosition.x == 7) {
        calculatePromotionMoves();
        return;
    }

    // attack left
    calculateAttackMove(board, Move({currentPosition.x + colourMultiplier, currentPosition.y - 1}));

    // attack right
    calculateAttackMove(board, Move({currentPosition.x + colourMultiplier, currentPosition.y + 1}));

    // move forward one //TODO deal with pawn promotion
    if (0 <= currentPosition.x + colourMultiplier && currentPosition.x + colourMultiplier <= 7
            && board.getPiece(currentPosition.x + colourMultiplier, currentPosition.y) == nullptr) {

        moves.emplace_back(std::array{currentPosition.x + colourMultiplier, currentPosition.y}, MoveType::SingleMove);

        if (!beenMoved && 0 <= currentPosition.x + colourMultiplier * 2 && currentPosition.x + colourMultiplier * 2 <= 7
                && board.getPiece(currentPosition.x + colourMultiplier * 2, currentPosition.y) == nullptr)

            moves.emplace_back(std::array{currentPosition.x + colourMultiplier * 2, currentPosition.y}, MoveType::DoubleMove);
    }
}

bool Pawn::isAttackingPosition(const Move &coord) const {
    return MovesCollisionCheck(moves, coord);
}

void Pawn::calculateAttackMove(Board& board, const Move &newMove) {
    if (0 <= newMove.x && newMove.x <= 7 && 0 <= newMove.y && newMove.y <= 7) {
        if (const Piece* possiblePiece = board.getPiece(newMove);
            possiblePiece != nullptr) {

            if (possiblePiece->getPieceColour() != colour) {
                moves.emplace_back(newMove, MoveType::Attacking);
                board.checkForCheck(currentPosition, newMove);

            } else
                moves.emplace_back(newMove, MoveType::Friendly);
        }
        else if (enpassantPossible(board, newMove))
            moves.emplace_back(newMove, MoveType::Enpassant);
        else
            moves.emplace_back(newMove, MoveType::None);
    }
}

bool Pawn::enpassantPossible(Board& board, const Move &enpassantMove) const {
    if (board.enpassantLocation == nullptr || !board.enpassantLocation->coordEqualTo(enpassantMove)) return false;

    if (currentPosition.x == 6 || currentPosition.x == 1) return false;

    if (const Piece* enpassantPawn = board.getPiece(currentPosition.x, board.enpassantLocation->y);
            enpassantPawn->getPieceColour() != colour) return true;

    return false;
}

void Pawn::calculatePromotionMoves() {
    moves.emplace_back(currentPosition, MoveType::PromotionQueen);
    moves.emplace_back(currentPosition, MoveType::PromotionKnight);
    moves.emplace_back(currentPosition, MoveType::PromotionRook);
    moves.emplace_back(currentPosition, MoveType::PromotionBishop);
}



bool Pawn::getBeenMoved() const {return beenMoved;}
void Pawn::setBeenMoved(const bool newBeenMoved) {beenMoved = newBeenMoved;}