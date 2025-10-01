//
// Created by olbai on 23/07/2025.
//

#include "Piece.hpp"

#include "pieces/Pawn.hpp"
#include "pieces/Knight.hpp"
#include "pieces/Bishop.hpp"
#include "pieces/Rook.hpp"
#include "pieces/Queen.hpp"
#include "pieces/King.hpp"

#include <memory>

std::unique_ptr<Piece> Piece::setPiece(char pieceLetter, const Move& position) {
    const bool isWhite = std::isupper(pieceLetter);
    pieceLetter = std::tolower(pieceLetter);

    std::unique_ptr<Piece> piecePtr = nullptr;

    switch (pieceLetter) {
        case 'p':
            // checking if pawn is on starting rank
            bool beenMoved;
            if (isWhite)
                beenMoved = position.x != 6;
            else
                beenMoved = position.x != 1;

            piecePtr = std::make_unique<Pawn>(PieceType::Pawn, PieceColour::None, position, beenMoved);
            break;
        case 'n':
            piecePtr = std::make_unique<Knight>(PieceType::Knight, PieceColour::None, position);
            break;
        case 'b':
            piecePtr = std::make_unique<Bishop>(PieceType::Bishop, PieceColour::None, position);
            break;
        case 'r':
            piecePtr = std::make_unique<Rook>(PieceType::Rook, PieceColour::None, position, false);
            break;
        case 'q':
            piecePtr = std::make_unique<Queen>(PieceType::Queen, PieceColour::None, position);
            break;
        case 'k':
            piecePtr = std::make_unique<King>(PieceType::King, PieceColour::None, position, false);
            break;
        default:
            throw std::invalid_argument("Error parsing castling fen input!: " + pieceLetter + '\n');

    }

    if (piecePtr != nullptr) {
        if (isWhite)
            piecePtr->colour = PieceColour::White;
        else
            piecePtr->colour = PieceColour::Black;
    }

    return piecePtr;
}

std::unique_ptr<Piece> Piece::setPiece(Piece *piece, const Move& position) {
    const char pieceLetter = piece->getPieceLetter();
    const bool isWhite = std::isupper(pieceLetter);
    const char pieceTypeLetter = std::tolower(pieceLetter);

    std::unique_ptr<Piece> piecePtr = nullptr;

    switch (pieceTypeLetter) {
        case 'p': {
            const Pawn* pawnPieceRawPtr = dynamic_cast<Pawn*>(piece);
            // checking if pawn is on starting rank
            piecePtr = std::make_unique<Pawn>(PieceType::Pawn, PieceColour::None, position, pawnPieceRawPtr->getBeenMoved());
            break;
        } case 'n':
            piecePtr = std::make_unique<Knight>(PieceType::Knight, PieceColour::None, position);
            break;
        case 'b':
            piecePtr = std::make_unique<Bishop>(PieceType::Bishop, PieceColour::None, position);
            break;
        case 'r': {
            const Rook* rookPieceRawPtr = dynamic_cast<Rook*>(piece);
            piecePtr = std::make_unique<Rook>(PieceType::Rook, PieceColour::None, position, rookPieceRawPtr->getBeenMoved());
            break;
        } case 'q':
            piecePtr = std::make_unique<Queen>(PieceType::Queen, PieceColour::None, position);
            break;
        case 'k': {
            const King* kingPieceRawPtr = dynamic_cast<King*>(piece);
            piecePtr = std::make_unique<King>(PieceType::King, PieceColour::None, position, kingPieceRawPtr->getBeenMoved());
            break;
        } default:
            throw std::invalid_argument("Error parsing castling fen input!: " + pieceLetter + '\n');
    }

    if (piecePtr != nullptr) {
        if (isWhite)
            piecePtr->colour = PieceColour::White;
        else
            piecePtr->colour = PieceColour::Black;
    }

    return piecePtr;
}

char Piece::pieceToLetter(const Piece& piece) {
    char pieceLetter;
    switch (piece.getPieceType()) {
        case PieceType::Pawn:
            pieceLetter = 'p';
            break;
        case PieceType::Knight:
            pieceLetter = 'n';
            break;
        case PieceType::Bishop:
            pieceLetter = 'b';
            break;
        case PieceType::Rook:
            pieceLetter = 'r';
            break;
        case PieceType::Queen:
            pieceLetter = 'q';
            break;
        case PieceType::King:
            pieceLetter = 'k';
            break;
        default:
            throw std::invalid_argument("Error passed PieceType does not exist: \n");
    }

    if (piece.getPieceColour() == PieceColour::White) {
        pieceLetter = std::toupper(pieceLetter);
    }
    return pieceLetter;
}

std::string Piece::getPieceId() const {
    if (colour == PieceColour::White) {
        switch (type) {
            case PieceType::Pawn:
                return "Chess_plt60";
            case PieceType::Knight:
                return "Chess_nlt60";
            case PieceType::Bishop:
                return "Chess_blt60";
            case PieceType::Rook:
                return "Chess_rlt60";
            case PieceType::Queen:
                return "Chess_qlt60";
            case PieceType::King:
                return "Chess_klt60";
            default:
                return "";
        }
    }

    switch (type) {
        case PieceType::Pawn:
            return "Chess_pdt60";
        case PieceType::Knight:
            return "Chess_ndt60";
        case PieceType::Bishop:
            return "Chess_bdt60";
        case PieceType::Rook:
            return "Chess_rdt60";
        case PieceType::Queen:
            return "Chess_qdt60";
        case PieceType::King:
            return "Chess_kdt60";

        default:
            return "";
    }
}

std::string Piece::getPawnPromotionId(const int pawnPromotionValue, const PieceColour &colour) {
    if (colour == PieceColour::White) {
        switch (pawnPromotionValue) {
            case 1:
                return "Chess_nlt60";
            case 3:
                return "Chess_blt60";
            case 2:
                return "Chess_rlt60";
            case 0:
                return "Chess_qlt60";
            default:
                return "";
        }
    }

    switch (pawnPromotionValue) {
        case 1:
            return "Chess_ndt60";
        case 3:
            return "Chess_bdt60";
        case 2:
            return "Chess_rdt60";
        case 0:
            return "Chess_qdt60";
        default:
            return "";
    }
}

char Piece::getPawnPromotionLetter(const MoveType &promotionType, const PieceColour &colour) {
    char pieceLetter;
    switch (promotionType) {
        case MoveType::PromotionKnight:
            pieceLetter = 'n';
            break;
        case MoveType::PromotionBishop:
            pieceLetter = 'b';
            break;
        case MoveType::PromotionRook:
            pieceLetter = 'r';
            break;
        case MoveType::PromotionQueen:
            pieceLetter = 'q';
            break;
        default:
            throw std::invalid_argument("Error passed PieceType does not exist: \n");
    }

    if (colour == PieceColour::White) {
        pieceLetter = std::toupper(pieceLetter);
    }
    return pieceLetter;
}