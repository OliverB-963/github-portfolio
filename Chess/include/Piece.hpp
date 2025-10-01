//
// Created by olbai on 30/06/2025.
//

#ifndef PIECE_H
#define PIECE_H

#include "locators/Move.hpp"

#include <string>

#include "helpers/TextureManager.hpp"
#include "locators/MovementPath.hpp"

enum class PieceType {
    Pawn, Knight, Bishop, Rook, Queen, King
};

enum class PieceColour {
    None, White, Black
};

class Board;

class Piece {
public:
    virtual ~Piece() = default;

protected:
    static const std::vector<std::array<int, 2>> BISHOP_MOVEMENTS;
    static const std::vector<std::array<int, 2>> ROOK_MOVEMENTS;

    std::vector<Move> moves;
    PieceType type;
    PieceColour colour;

    Move currentPosition;

    std::vector<MovementPath> laserMovement(Board &board, const Piece *currentPiece, const std::vector<std::array<int, 2>> &movements);

    static bool MovesCollisionCheck(const std::vector<Move> &moves, const Move &coordToCheck);

    virtual std::ostream &print(std::ostream &os) const;

public:
    static const std::vector<MoveType> POSSIBLE_MOVETYPES;
    static const std::vector<MoveType> DRAWABLE_MOVETYPES;

    Piece(PieceType type, PieceColour colour, const Move &position);

    virtual void calculateMoves(Board &board);

    [[nodiscard]] virtual bool isAttackingPosition(const Move& coord) const;

    void removeIllegalMoves(const Board &board);

    [[nodiscard]] std::vector<Move> getPossibleMoves(const std::vector<MoveType> &moveTypesToShow = POSSIBLE_MOVETYPES) const;

    [[nodiscard]] bool hasMove(const Move& possibleMove) const;
    Move getMove(const Move& moveToGet) const;

    [[nodiscard]] bool hasLegalMoves() const;

    // --- Other ---

    char getPieceLetter() const;
    static char pieceToLetter(const Piece& piece);

    static std::unique_ptr<Piece> setPiece(char pieceLetter, const Move& position);
    static std::unique_ptr<Piece> setPiece(Piece *piece, const Move& position);

    [[nodiscard]] std::string getPieceId() const;

    static std::string getPawnPromotionId(int pawnPromotionValue, const PieceColour &colour);
    static char getPawnPromotionLetter(const MoveType &promotionType, const PieceColour &colour);

    std::vector<Move> getMoves() const;
    void setMoves(const std::vector<Move>& otherMoves);

    [[nodiscard]] const PieceType &getPieceType() const;
    [[nodiscard]] const PieceColour &getPieceColour() const;
    [[nodiscard]] const Move &getPiecePosition() const;

    virtual bool getBeenMoved() const;
    virtual void setBeenMoved(bool value);

    friend std::ostream &operator<<(std::ostream &os, const Piece &piece);

private:
    void outOfBounds(Board &board,  int distance, const Move *pieceEncountered,
        std::vector<MovementPath> &addedMoves, const std::array<int, 2> &movementModifiers);

    void friendly(Board &board, const Move *pieceEncountered, const Move &newPosition,
                  std::vector<MovementPath> &addedMoves);

    void attacking(Board &board, const Move *pieceEncountered, const Move &newPosition,
                   std::vector<MovementPath> &addedMoves, const std::array<int, 2> &movementModifiers);
};

inline std::ostream &operator<<(std::ostream &os, const PieceType &pieceType) {
    switch (pieceType) {
        case PieceType::Pawn:
            os << "Pawn";
            break;
        case PieceType::Knight:
            os << "Knight";
            break;
        case PieceType::Bishop:
            os << "Bishop";
            break;
        case PieceType::Rook:
            os << "Rook";
            break;
        case PieceType::Queen:
            os << "Queen";
            break;
        case PieceType::King:
            os << "King";
            break;
    }

    return os;
}

inline std::ostream &operator<<(std::ostream &os, const PieceColour &pieceColour) {
    switch (pieceColour) {
        case PieceColour::White:
            os << "White";
            break;
        case PieceColour::Black:
            os << "Black";
            break;
        case PieceColour::None:
            os << "None";
            break;
    }

    return os;
}


#endif //PIECE_H
