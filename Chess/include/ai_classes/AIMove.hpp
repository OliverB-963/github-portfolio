//
// Created by Oliver Bailey on 7/24/2025.
//

#ifndef AIMOVE_HPP
#define AIMOVE_HPP

#include <iosfwd>

#include "Piece.hpp"
#include "locators/Move.hpp"

class Move;
class Piece;

class AIMove {
public:
    Move piecePosition_;
    Move moveToMake_;

    AIMove(const Move &piecePosition, const Move &moveToMake);

    std::string asNotation() const;

    friend std::ostream &operator<<(std::ostream &os, const AIMove &aiMove);

    static double maxEvaluation(const std::vector<double> &evaluations, PieceColour playerColour);

    static bool isBetter(double currentBest, double evaluation, const PieceColour &turnColour);
};



#endif //AIMOVE_HPP
