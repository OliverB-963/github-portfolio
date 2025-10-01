//
// Created by Oliver Bailey on 7/23/2025.
//

#ifndef AICALCULATOR_HPP
#define AICALCULATOR_HPP

#include "ScoreMapper.hpp"
#include "AIMove.hpp"

#include <memory>

class Board;

class AICalculator {
    static std::array<double, 6> pieceValues;

    const PieceColour colour_;
    const int depth_;
    int moveCount = 0;

    std::unique_ptr<ScoreMapper> scoreMapper_;

public:
    AICalculator(int depth, PieceColour colour);

    AIMove pickMove(Board &currentBoard);

    double boardEvaluationCalc(const Board &board) const;

private:
    double explore(Board &board, int depth, bool maximising, double alpha, double beta,
                   int maxDepth);

    static void replacePromotionMove(Piece *pawn);

    static std::vector<AIMove> generateMoves(Board &board);

    static double movesValue(const Piece *piece);
};

#endif //AICALCULATOR_HPP
