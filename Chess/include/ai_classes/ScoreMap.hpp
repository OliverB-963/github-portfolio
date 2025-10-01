//
// Created by Oliver Bailey on 7/24/2025.
//

#ifndef SCOREMAP_HPP
#define SCOREMAP_HPP

#include "Piece.hpp"
#include <array>

class ScoreMap {
    std::array<int, 8> coordConversion = {7, 6, 5, 4, 3, 2, 1, 0};
    std::array<std::array<double, 8>, 8> scores_ = {};
    int currentIndex = 0;

public:
    void loadValues(const std::string &dataStream);

    double getEvaluation(const Move &coord, bool flipScores) const;
};



#endif //SCOREMAP_HPP
