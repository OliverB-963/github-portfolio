//
// Created by Oliver Bailey on 01/07/2025.
//

#include "locators/Move.hpp"

#include <sstream>
#include <cmath>
#include <iostream>

const std::string Move::NOTATION_LETTERS = "abcdefgh";
const std::string Move::NOTATION_NUMBERS = "87654321";

Move::Move(const std::array<int, 2> &position)
    : x(position[0]), y(position[1]), type(MoveType::None) {}

Move::Move(const std::array<int, 2> &position, const MoveType type)
    : x(position[0]), y(position[1]), type(type) {}

Move::Move(const Move &position, const MoveType type)
    : x(position.x), y(position.y), type(type){}

Move Move::copy(const Move &other) {
    return Move({other.x, other.y}, other.type);
}

bool Move::moveTypeInVector(const std::vector<MoveType> &moveTypes, const MoveType &moveTypeToCheck) {
    for (const MoveType &moveType : moveTypes) {
        if (moveType == moveTypeToCheck) return true;
    }
    return false;
}

int Move::moveIndexInVector(const std::vector<Move> &moves, const Move &moveToCheck) {
    for (int i = 0; i < moves.size(); ++i) {
        if (const Move &move = moves.at(i);
            move.coordEqualTo(moveToCheck) && move.type == moveToCheck.type) return i;
    }
    return -1;
}


MoveType Move::getPromotionType(const int promotionID) {
    switch (promotionID) {
        case 1:
            return MoveType::PromotionKnight;
        case 3:
            return MoveType::PromotionBishop;
        case 2:
            return MoveType::PromotionRook;
        case 0:
            return MoveType::PromotionQueen;
        default:
            throw std::invalid_argument("Error passed promotionID does not exist: \n");
    }
}

char Move::getPromotionLetter() const {
    switch (type) {
        case MoveType::PromotionKnight:
            return 'n';
        case MoveType::PromotionBishop:
            return 'b';
        case MoveType::PromotionRook:
            return 'r';
        case MoveType::PromotionQueen:
            return 'q';
        default:
            throw std::invalid_argument("Error passed promotionID does not exist: \n");
    }
}

bool Move::isPromotion() const {
    if (type == MoveType::PromotionQueen || type == MoveType::PromotionKnight
            || type == MoveType::PromotionRook || type == MoveType::PromotionBishop) return true;
    return false;
}


Move &Move::operator=(const Move &other) {
    if (this == &other) {
        return *this;
    }

    x = other.x;
    y = other.y;
    type = other.type;

    return *this;
}

std::ostream &operator<<(std::ostream &os, const Move &move) {
    return os << move.type << ": " << "(" << move.x << ", " << move.y << ")";
}


std::string Move::str() const {
    std::stringstream ss;
    ss << "(" << x << ", " << y << ")";
    return ss.str();
}


bool Move::coordEqualTo(const Move& otherMove) const {
    if (x == otherMove.x && y == otherMove.y)
        return true;
    return false;
}

Position Move::toPosition(const float squareSize, const bool correctCentre) const {
    const int squareSizeInt = static_cast<int>(squareSize);
    const int halfSquareSize = correctCentre ? static_cast<int>(std::round(0.5*squareSize)) : 0;
    return Position(sf::Vector2i{y * squareSizeInt + halfSquareSize, x * squareSizeInt + halfSquareSize});
}


std::string Move::getNotation() const {
    std::string tempStr(1, NOTATION_LETTERS[y]);
    tempStr += NOTATION_NUMBERS[x];
    return tempStr;
}

Move Move::notationToPosition(const std::string &notation) {
    const int letterPosition = NOTATION_LETTERS.find(notation[0]);
    const int numberPosition = NOTATION_NUMBERS.find(notation[1]);
    return Move({numberPosition, letterPosition});
}

