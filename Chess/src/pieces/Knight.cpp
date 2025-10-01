//
// Created by olbai on 30/06/2025.
//

#include "pieces/Knight.hpp"

#include "Board.hpp"

Knight::Knight(const PieceType type, const PieceColour colour, const Move position)
    : Piece(type, colour, position) {
}

void Knight::calculateMoves(Board &board) {
    constexpr std::array<std::array<int, 2>, 8> thing{ //TODO rename
        {
            {1, -2},
            {-1, -2},
            {-2, -1},
            {-2, 1},
            {-1, 2},
            {1, 2},
            {2, 1},
            {2, -1}
        }};

    moves.clear();

    for (std::array<int, 2> thing2 : thing) { // TODO rename
        if (0 <= currentPosition.x + thing2[0] && currentPosition.x + thing2[0] <= 7
                && 0 <= currentPosition.y + thing2[1] && currentPosition.y + thing2[1] <= 7) {
            const MoveType moveType = board.getMoveType(this,
                Move({currentPosition.x + thing2[0], currentPosition.y + thing2[1]}));

            board.checkForCheck(currentPosition, Move({currentPosition.x + thing2[0], currentPosition.y + thing2[1]}));

            moves.emplace_back(std::array{currentPosition.x + thing2[0], currentPosition.y + thing2[1]}, moveType);
        }
    }
}

bool Knight::isAttackingPosition(const Move &coord) const {
    return MovesCollisionCheck(moves, coord);
}
