//
// Created by Oliver Bailey on 7/24/2025.
//

#ifndef SCOREMAPPER_HPP
#define SCOREMAPPER_HPP

#include <array>
#include <memory>

#include "ScoreMap.hpp"

class ScoreMapper {
    std::array<std::unique_ptr<ScoreMap>, 6> scoreMaps;

public:
    ScoreMapper();

    double calculateScore(const Piece *piece) const;

    static int pieceMapIndex(const PieceType &pieceType);

private:
    void loadLocationScores() const;
};



#endif //SCOREMAPPER_HPP
