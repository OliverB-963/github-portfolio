//
// Created by olbai on 23/07/2025.
//

#include "Piece.hpp"

#include "Board.hpp"

#include <memory>

const std::vector<std::array<int, 2>> Piece::BISHOP_MOVEMENTS = {{
    {1, 1},
    {1, -1},
    {-1, 1},
    {-1, -1}
}};

const std::vector<std::array<int, 2>> Piece::ROOK_MOVEMENTS = {{
    {1, 0},
    {-1, 0},
    {0, 1},
    {0, -1}
}};

std::vector<MovementPath> Piece::laserMovement(Board &board, const Piece *currentPiece, const std::vector<std::array<int, 2>> &movements) {
    std::vector<MovementPath> addedMoves;

    if (currentPiece == nullptr) return addedMoves;
    if (const PieceType pieceType = currentPiece->getPieceType();
        pieceType == PieceType::Pawn || pieceType == PieceType::Knight || pieceType == PieceType::King)
        throw std::runtime_error("This piece not allowed");


    std::array maxDistances{0, 0, 0, 0};
    std::array<std::unique_ptr<Move>, 4> piecesEncountered;

    // piecesEncounteredCount used to count how many pieces come across the path of the MovementPath to account for piece being pinned
    // 2 is the limit as only one piece can be pinned between another
    for (int j = 0; j < 4; ++j) {
        for (int i = 1; i < 8; ++i) {
            const int newX = currentPosition.x + i * movements[j][0];
            const int newY = currentPosition.y + i * movements[j][1];

            const Move moveTo({newX, newY});

            if (newX < 0 || newX > 7 || newY < 0 || newY > 7) {
                outOfBounds(board, maxDistances[j], piecesEncountered[j].get(), addedMoves, movements[j]);
                break;
            }
            maxDistances[j] = i;

            const MoveType moveType = board.getMoveType(this, moveTo);

            if (moveType == MoveType::Friendly) {
                friendly(board, piecesEncountered[j].get(), moveTo, addedMoves);
                break;

            } else if (moveType == MoveType::Attacking) {
                if (piecesEncountered[j] == nullptr) { // if it has found an enemy but could find another enemy behind it
                    piecesEncountered[j] = std::make_unique<Move>(moveTo);
                    // CONTINUE

                } else {
                    attacking(board, piecesEncountered[j].get(), moveTo, addedMoves, movements[j]);
                    break;
                }
            }

            if (maxDistances[j] == 7) {
                outOfBounds(board, maxDistances[j], piecesEncountered[j].get(), addedMoves, movements[j]);
            }
        }
    }

    return addedMoves;
}

void Piece::outOfBounds(Board &board, const int distance, const Move *pieceEncountered,
                        std::vector<MovementPath> &addedMoves, const std::array<int, 2> &movementModifiers) {
    if (distance == 0) return;

    if (pieceEncountered != nullptr) {
        // if enemy was previously found and then nothing behind it
        if (const Piece* piecePtr = board.getPiece(*pieceEncountered);
            piecePtr != nullptr && piecePtr->getPieceType() == PieceType::King) {
            const auto finalMove = Move({currentPosition.x + distance * movementModifiers[0],
                                             currentPosition.y + distance * movementModifiers[1]}, MoveType::Attacking);
            addedMoves.emplace_back(currentPosition,
                                    finalMove);
            board.checkForCheck(currentPosition, *pieceEncountered);
        } else {
            addedMoves.emplace_back(currentPosition,
                                    Move(*pieceEncountered, MoveType::Attacking));
        }
    } else // if nothing was found up to reaching the border
        addedMoves.emplace_back(currentPosition,
                                Move({currentPosition.x + distance * movementModifiers[0],
                                         currentPosition.y + distance * movementModifiers[1]}, MoveType::Empty));
}

void Piece::friendly(Board &board, const Move *pieceEncountered, const Move &newPosition,
                     std::vector<MovementPath> &addedMoves) {
    if (pieceEncountered != nullptr) { // if the path previously encountered an enemy and has now found a friendly behind it
        if (const Piece* piecePtr = board.getPiece(*pieceEncountered); // If the previously encountered enemy was the king
                piecePtr != nullptr && piecePtr->getPieceType() == PieceType::King) {
            addedMoves.emplace_back(currentPosition,
                Move({newPosition.x, newPosition.y}, MoveType::Friendly));
            board.checkForCheck(currentPosition, newPosition);
        } else {
            addedMoves.emplace_back(currentPosition,
                Move(*pieceEncountered, MoveType::Attacking));
        }
    } else {
        // if it has just found a friendly
        addedMoves.emplace_back(currentPosition,
            Move(newPosition, MoveType::Friendly));
    }
}

void Piece::attacking(Board &board, const Move *pieceEncountered, const Move &newPosition,
                      std::vector<MovementPath> &addedMoves, const std::array<int, 2> &movementModifiers) {

    if (const Piece* pinnedPiecePtr = board.getPiece(*pieceEncountered); // If the previously encountered enemy was the king
            pinnedPiecePtr != nullptr && pinnedPiecePtr->getPieceType() == PieceType::King) {
        addedMoves.emplace_back(currentPosition,
            Move({newPosition.x - movementModifiers[0], newPosition.y - movementModifiers[1]}, MoveType::Empty));
        board.checkForCheck(currentPosition, newPosition);

    } else if (const Piece* piecePtr = board.getPiece(newPosition);
        piecePtr != nullptr && piecePtr->getPieceType() == PieceType::King) {
        addedMoves.emplace_back(currentPosition, Move(*pieceEncountered, MoveType::Attacking),
                                Move(newPosition, MoveType::Attacking));

    } else {// if it has found an enemy behind the first but is not a k
        addedMoves.emplace_back(currentPosition,
                                Move(*pieceEncountered, MoveType::Attacking));
    }
}
