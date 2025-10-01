//
// Created by olbai on 04/07/2025.
//

#ifndef FENPROCESSOR_H
#define FENPROCESSOR_H

#include "pieces/King.hpp"
#include "pieces/Rook.hpp"

#include <string>

class Board;

class FenProcessor {
    Board& board;

public:
    static const std::string STARTING_FEN;

    explicit FenProcessor(Board& board);

    void setBoard(const std::string& fen) const;

    std::string boardToFen() const;

private:
    void setPieces(const std::string &BoardFenSection) const;
    void setCastling(const std::string &castlingFenSection) const;
    static void checkKingRookPair(King* kingPtr, Rook* rookPtr, const PieceColour& pieceColour);

    std::string piecesForFen() const;
    std::string castlingForFen() const;
};



#endif //FENPROCESSOR_H
