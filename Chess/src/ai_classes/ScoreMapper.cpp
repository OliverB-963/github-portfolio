//
// Created by Oliver Bailey on 7/24/2025.
//

#include "ai_classes/ScoreMapper.hpp"

ScoreMapper::ScoreMapper() {
    for (int i = 0; i < 6; ++i) {
        scoreMaps[i] = std::make_unique<ScoreMap>();
    }

    loadLocationScores();
}

void ScoreMapper::loadLocationScores() const {
    std::ifstream dataFile("../resources/ai_data/LocationScores.txt");

    if (!dataFile.is_open()) throw std::runtime_error("File not found");
    if (!dataFile.good()) throw std::runtime_error("File not good?");

    std::string line, value;
    int count = 0;

    while (std::getline(dataFile, line)) {
        if (line.empty())
            count++;
        else
            scoreMaps[count]->loadValues(line);
    }
}

double ScoreMapper::calculateScore(const Piece *piece) const {
    return scoreMaps[pieceMapIndex(piece->getPieceType())]->
        getEvaluation(
            piece->getPiecePosition(),
            piece->getPieceColour() == PieceColour::White
            );
}

int ScoreMapper::pieceMapIndex(const PieceType &pieceType) {
    switch (pieceType) {
        case PieceType::Pawn:
            return 0;
        case PieceType::Knight:
            return 1;
        case PieceType::Bishop:
            return 2;
        case PieceType::Rook:
            return 3;
        case PieceType::Queen:
            return 4;
        case PieceType::King:
            return 5;
        default:
            throw std::runtime_error("map index error");
    }
}
