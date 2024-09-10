#ifndef GUI_H
#define GUI_H

#include <SFML/Graphics.hpp>
#include "board.h"
#include "search.h"

class GUI
{
public:
    GUI();
    void run();

private:
    sf::RenderWindow window;
    sf::Texture piecesTexture;
    sf::Sprite boardSprite;
    sf::Sprite piecesSprites[32];
    Board board;
    SearchEngine searchEngine;
    bool isWhiteTurn;

    int selectedPiece;
    std::vector<std::pair<int, int>> validMoves;

    void loadTextures();
    void drawBoard();
    void drawPieces();
    void handleMouseClick(int x, int y);
    void highlightValidMoves();
    void movePiece(int from, int to);
    void makeEngineMove();
    bool isGameOver();
    void showEndGameMessage();
    void resetGame();
};

#endif // GUI_H