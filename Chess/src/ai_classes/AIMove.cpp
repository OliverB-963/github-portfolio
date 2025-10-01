//
// Created by Oliver Bailey on 7/24/2025.
//

#include "ai_classes/AIMove.hpp"

#include "Piece.hpp"

AIMove::AIMove(const Move &piecePosition, const Move &moveToMake)
    : piecePosition_(piecePosition), moveToMake_(Move::copy(moveToMake)) {}

// std::string AIMove::asNotation() const {
//     std::string thing = piece_->getPiecePosition().getNotation() + moveToMake_.getNotation();
//
//     if (moveToMake_.isPromotion()) {
//         thing += moveToMake_.getPromotionLetter();
//     }
//
//     return thing;
// }

double AIMove::maxEvaluation(const std::vector<double> &evaluations, const PieceColour playerColour) {
    double maxEvaluation = evaluations[0];

    for (const double eval : evaluations) {
        if (isBetter(maxEvaluation, eval, playerColour)) {
            maxEvaluation = eval;
    }}

    return maxEvaluation;
}


// std::ostream &operator<<(std::ostream &os, const AIMove &aiMove) {
//     return os << aiMove.piece_->getPieceType() << " " << aiMove.piece_->getPiecePosition() << ": " << aiMove.moveToMake_;
// }

bool AIMove::isBetter(const double currentBest, const double evaluation, const PieceColour &turnColour) {
    if (turnColour == PieceColour::White)
        return evaluation > currentBest;
    else
        return evaluation < currentBest;
}
