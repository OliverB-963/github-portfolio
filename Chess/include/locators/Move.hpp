//
// Created by Oliver Bailey on 01/07/2025.
//

#ifndef MOVE_H
#define MOVE_H

#include "Position.hpp"

#include <array>
#include <string>

enum class MoveType {
    Empty, Attacking , Friendly, Enpassant,
    SingleMove, DoubleMove, KingMove, Castling,
    PromotionQueen, PromotionKnight, PromotionRook, PromotionBishop,
    Pin, None
};

class Move {
    static const std::string NOTATION_LETTERS;
    static const std::string NOTATION_NUMBERS;

public:
    int x;
    int y;
    MoveType type;

    explicit Move(const std::array<int, 2>& position);

    Move(const std::array<int, 2>& position, MoveType type);

    Move(const Move& position, MoveType type);

    Move& operator=(const Move& other);

    static Move copy(const Move& other);

    static bool moveTypeInVector(const std::vector<MoveType> &moveTypes, const MoveType &moveTypeToCheck);

    /* returns -1 if not found */
    static int moveIndexInVector(const std::vector<Move> &moves, const Move &moveToCheck);

    static MoveType getPromotionType(int promotionID);

    char getPromotionLetter() const;

    bool isPromotion() const;

    friend std::ostream &operator<<(std::ostream &os, const Move &move);

    std::string str() const;

    /** Doesn't compare Move type */
    bool coordEqualTo(const Move& otherMove) const;

    Position toPosition(float squareSize, bool correctCentre = false) const;

    std::string getNotation() const;

    static Move notationToPosition(const std::string &notation);
};

inline std::ostream &operator<<(std::ostream &os, const MoveType &pieceType) {
    switch (pieceType) {
        case MoveType::Empty:
            os << "Empty";
            break;
        case MoveType::Attacking:
            os << "Attacking";
            break;
        case MoveType::Friendly:
            os << "Friendly";
            break;
        case MoveType::Enpassant:
            os << "Enpassant";
            break;
        case MoveType::SingleMove:
            os << "SingleMove";
            break;
        case MoveType::DoubleMove:
            os << "DoubleMove";
            break;
        case MoveType::KingMove:
            os << "KingMove";
            break;
        case MoveType::Castling:
            os << "Castling";
            break;
        case MoveType::Pin:
            os << "Pin";
            break;
        case MoveType::None:
            os << "None";
            break;
        case MoveType::PromotionQueen:
            os << "PromotionQueen";
            break;
        case MoveType::PromotionKnight:
            os << "PromotionKnight";
            break;
        case MoveType::PromotionRook:
            os << "PromotionRook";
            break;
        case MoveType::PromotionBishop:
            os << "PromotionBishop";
            break;
    }

    return os;
}

#endif //MOVE_H