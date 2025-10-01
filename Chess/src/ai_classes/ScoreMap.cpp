//
// Created by Oliver Bailey on 7/24/2025.
//

#include "ai_classes/ScoreMap.hpp"

void ScoreMap::loadValues(const std::string &dataStream) {
    std::stringstream valueStream(dataStream);
    std::string value;

    int count = 0;
    while (std::getline(valueStream, value, ',')) {
        scores_[currentIndex][count] = std::stod(value);
        count++;
    }

    currentIndex++;
}

double ScoreMap::getEvaluation(const Move &coord, const bool flipScores) const {
    const int x = (flipScores) ? coord.x : coordConversion[coord.x];

    return scores_[x][coord.y];
}
