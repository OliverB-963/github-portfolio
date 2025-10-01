//
// Created by Oliver Bailey on 7/23/2025.
//

#include "ai_classes/AICalculator.hpp"

#include "Board.hpp"
#include "ai_classes/AIMove.hpp"

std::array<double, 6> AICalculator::pieceValues = {10, 30, 30, 50, 90, 0};

AICalculator::AICalculator(const int depth, const PieceColour colour)
    : colour_(colour), depth_(depth) {
    scoreMapper_ = std::make_unique<ScoreMapper>();
}

AIMove AICalculator::pickMove(Board &currentBoard) {
    if (depth_ == 1) throw std::runtime_error("depth 1 not worth it");

    std::vector<AIMove> allMoves = generateMoves(currentBoard);

    AIMove *bestMove = nullptr;
    double currentBestEval = -std::numeric_limits<double>::infinity();
    constexpr double alpha = -std::numeric_limits<double>::infinity();
    constexpr double beta = std::numeric_limits<double>::infinity();

    for (AIMove &move : allMoves) {
        Board tempBoard = currentBoard;
        tempBoard.makeMove(tempBoard.getPiece(move.piecePosition_), move.moveToMake_);
        tempBoard.swapPlayerTurn(true);

        const double eval = explore(tempBoard, 1, tempBoard.playerTurn == PieceColour::White,
                                    alpha, beta, depth_);

        if (AIMove::isBetter(currentBestEval, eval, currentBoard.playerTurn)) {
            currentBestEval = eval;
            bestMove = &move;
        }
    }

    if (bestMove == nullptr)
        throw std::runtime_error("done fucked");

    return *bestMove;
}

double AICalculator::explore(Board &board, int depth, bool maximising, double alpha, double beta, int maxDepth) { // NOLINT

    if (depth == maxDepth || board.gameFinished()) {
        return boardEvaluationCalc(board); // Base Case
    }

    // Recursive Case

    double bestEval = maximising ? -std::numeric_limits<double>::infinity() : std::numeric_limits<double>::infinity();

    std::vector<AIMove> allMoves = generateMoves(board); // NOLINT

    for (AIMove &move : allMoves) {
        Board tempBoard = board;
        tempBoard.makeMove(board.getPiece(move.piecePosition_), move.moveToMake_);
        tempBoard.swapPlayerTurn(true);

        double eval = explore(tempBoard, depth + 1, !maximising, alpha, beta, maxDepth);
        std::cout << eval << '\n';

        if (maximising) {
            alpha = std::max(alpha, eval);
        } else {
            beta = std::min(beta, eval);
        }
        bestEval = AIMove::isBetter(bestEval, eval, board.playerTurn);

        if (beta <= alpha) {
            break;
        }
    }

    return bestEval;
}

double AICalculator::boardEvaluationCalc(const Board &board) const {
    double totalEvaluation = 0;

    for (const Piece *piece : board) {
        if (piece != nullptr) {
            const double thing = piece->getPieceColour() == PieceColour::White ? 1 : -1;

            totalEvaluation += thing * scoreMapper_->calculateScore(piece);
            totalEvaluation += thing * pieceValues[scoreMapper_->pieceMapIndex(piece->getPieceType())];;
            totalEvaluation += thing * movesValue(piece);
        }
    }

    return totalEvaluation;
}

double AICalculator::movesValue(const Piece *piece) {
    return 0;
}


void AICalculator::replacePromotionMove(Piece *pawn) {
    std::vector<Move> moves = pawn->getMoves();

    for (const Move &move : pawn->getMoves()) {
        if (const PieceColour &pawnColour = pawn->getPieceColour();
                Move::moveTypeInVector(Piece::POSSIBLE_MOVETYPES, move.type) &&
                (pawnColour == PieceColour::White && move.x == 0
                || pawnColour == PieceColour::Black && move.x == 7)) {
            if (const int moveIndex = Move::moveIndexInVector(moves, move);
                moveIndex != -1) {
                moves.erase(moves.begin() + moveIndex);

                moves.emplace_back(move, MoveType::PromotionQueen);
                moves.emplace_back(move, MoveType::PromotionKnight);
                moves.emplace_back(move, MoveType::PromotionRook);
                moves.emplace_back(move, MoveType::PromotionBishop);
            }
        }
    }

    pawn->setMoves(moves);
}

std::vector<AIMove> AICalculator::generateMoves(Board &board) {
    std::vector<AIMove> allMoves;

    board.calculateMoves(false);

    for (Piece *piecePtr : board) {
        if (piecePtr == nullptr || piecePtr->getPieceColour() != board.playerTurn) continue;

        if (piecePtr->getPieceType() == PieceType::Pawn) replacePromotionMove(piecePtr);

        for (const Move &move : piecePtr->getPossibleMoves()) {
            allMoves.emplace_back(piecePtr->getPiecePosition(), move);
        }
    }

    return allMoves;
}

