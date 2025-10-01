//
// Created by olbai on 02/07/2025.
//

#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <bits/stdc++.h>
#include "SFML/Graphics.hpp"
#include <string>

class TextureManager {
    static const std::array<std::string, 12> chessPieceIds;

    std::unordered_map<std::string, sf::Texture> pieceTextures;

public:
    TextureManager();

    const sf::Texture &getTexture(const std::string &id) const;
};



#endif //TEXTUREMANAGER_H
