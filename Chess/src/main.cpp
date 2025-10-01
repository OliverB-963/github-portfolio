#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "Board.hpp"
#include "helpers/TextureManager.hpp"

#include "ai_classes/AICalculator.hpp"

int main()
{
    constexpr float SQUARE_LENGTH = 100;
    sf::RenderWindow window(sf::VideoMode(800, 800), "SFML works!", sf::Style::Close);

    const TextureManager textureManager;

    // rnbq1k1r/pp1Pbppp/2p5/8/2B5/8/PPP1NnPP/RNBQK2R w KQ - 1 8
    Board board(window, textureManager, SQUARE_LENGTH);
    board.setPosition("k7/5r2/8/8/8/8/PPP5/K7 b - - 1 8"); //FenProcessor::STARTING_FEN

    while (window.isOpen()) {
        window.clear(sf::Color::Black);
        board.draw();
        board.gameLoop();
        window.display();
    }

    return 0;
}