#ifndef GUI_H
#define GUI_H

#include <SFML/Graphics.hpp>
#include "board.h"
#include "movegen.h"
#include "evaluation.h"
#include "search.h"
#include <map>
#include <string>

class GUI
{
public:
    GUI(sf::RenderWindow &window); // Constructor to load textures and initialize the window

    void run(); // Main loop for running the GUI (handling play and analyze modes)

    bool isWhite;

    // Play Mode and Analyze Mode
    void playMode(bool isWhite);    // Play game logic
    void analyzeMode(); // Analyze game logic

    void highlightSquare(sf::Vector2i square);
    void showGameOverScreen(bool isWhiteWinner);
    void restartGame();

    bool isGameOver;

private:
    // Window and textures
    sf::RenderWindow &window; //Refrence to the window(Important!)
    sf::Texture boardTexture, whitePiecesTexture, blackPiecesTexture, logoTexture;
    std::map<std::string, sf::Texture> pieceTextures;

    // Sprites for board, pieces, and logo
    sf::Sprite boardSprite;
    sf::Sprite logoSprite;
    std::map<std::string, sf::Sprite> pieceSprites;

    // Chessboard grid constants
    static const int boardSize = 8;
    static const float tileSize;

    // Board state
    Board board;
    MoveGenerator moveGen;
    Evaluation evaluation;
    Search search;
    int kingSquare;
    bool isWhiteTurn;

    // Helper functions
    void loadTextures(); // Load textures for pieces, board, and logo
    void drawBoard();    // Draw the chessboard
    void drawPieces();   // Draw the chess pieces based on the board state
    void handleInput();  // Handle user input for piece movement
    void handleMenu();   // Handle the main menu for Play, Analyze, or Exit

    bool isPieceOnSquare(const sf::Vector2i& square); // Declaration
};

#endif // GUI_H
