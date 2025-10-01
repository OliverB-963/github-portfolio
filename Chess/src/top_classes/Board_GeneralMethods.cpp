//
// Created by olbai on 23/07/2025.
//

#include "Board.hpp"

/* --- Small Stuff --- */
void Board::calculateMoves(const bool simulation) const {
    chessLogic->calculateMoves(simulation);
}

void Board::setPosition(const std::string &fen) const {
    fenProcessor->setBoard(fen);
}

void Board::draw() const {
    boardDisplay->all();
}

void Board::print() const {
    boardDisplay->printBoard();
}

std::string Board::getFen() const {
    return fenProcessor->boardToFen();
}

void Board::makeMove(Piece *piece, const Move &moveToMake) const {
    chessLogic->makeMove(piece, moveToMake);
}

bool Board::isCheckmate() const {
    if (!isStalemate() || checkLocation == nullptr) return false;

    for (int x = 0; x < 8; ++x) {
        for (int y = 0; y < 8; ++y) {
            if (const Piece* piecePtr = grid[x][y].get();
                piecePtr != nullptr && piecePtr->getPieceType() == PieceType::King && piecePtr->getPieceColour() == playerTurn
                    && checkLocation->coordEqualTo(piecePtr->getPiecePosition()))
                return true;
        }
    }
    return false;
}

bool Board::isStalemate() const {
    for (int x = 0; x < 8; ++x) {
        for (int y = 0; y < 8; ++y) {
            if (const Piece* piecePtr = grid[x][y].get();
                piecePtr != nullptr && piecePtr->getPieceColour() == playerTurn
                && !piecePtr->getPossibleMoves().empty())
                return false;
        }
    }
    return true;
}

bool Board::gameFinished() const {
    if (checkLocation == nullptr) return false;

    for (int x = 0; x < 8; ++x) {
        for (int y = 0; y < 8; ++y) {
            if (const Piece* piecePtr = grid[x][y].get();
                piecePtr != nullptr && piecePtr->getPieceColour() == playerTurn
                && (piecePtr->getPieceType() == PieceType::King && !checkLocation->coordEqualTo(piecePtr->getPiecePosition())
                    || !piecePtr->getPossibleMoves().empty()))
            return false;
        }
    }

    return true;
}

void Board::checkForCheck(const Move &startCoord, const Move &endCoord) {
    if (checkLocation != nullptr && checkLocation->coordEqualTo(endCoord)) return;

    const Piece *movingPiece = getPiece(startCoord);
    const Piece *attackedPiece = getPiece(endCoord);

    if (movingPiece == nullptr || attackedPiece == nullptr) return;
    if (attackedPiece->getPieceType() != PieceType::King) return;
    if (movingPiece->getPieceColour() == attackedPiece->getPieceColour()) return;

    checkLocation = std::make_unique<Move>(endCoord);
}