// #ifndef GUI_H
// #define GUI_H

// #include "board.h"
// #include "movegen.h"
// #include "search.h"
// #include "move.h"

// #include <iostream>
// #include <vector>

// class GUI
// {
// private:
//     Board board;
//     MoveGenerator moveGen;
//     Search search;
//     std::vector<std::pair<int, int>> validMoves;
//     int selectedPiece;
//     bool isWhiteTurn;
//     int kingSquare;

// public:
//     GUI();
//     void selectMode();
//     void playMode();
//     void analyzeMode();
//     void handleMouseClick(int x, int y);
//     void makeEngineMove();
//     bool isGameOver();
//     void showEndGameMessage();
//     void resetGame();
//     void loadPGN();
// };

// #endif

#ifndef GUI_H
#define GUI_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include <vector>
#include "board.h"
#include "movegen.h"
#include "search.h"

// Enumeration to define different modes
enum GameMode
{
    PLAY_MODE,
    ANALYZE_MODE
};

// GUI class definition
class GUI
{
public:
    // Constructor
    GUI();

    // Run the main GUI loop
    void run();

private:
    // SFML window for the GUI
    sf::RenderWindow window;

    // Texture for the chess pieces
    sf::Texture piecesTexture;

    // Sprites for the chess pieces
    sf::Sprite piecesSprites[32];

    // Game mode: play or analyze
    GameMode mode;

    // Board and move generator
    Board board;
    MoveGenerator moveGen;
    Search search;
    std::vector<std::pair<int, int>> validMoves;
    int kingSquare;

    // Selected piece for movement (-1 if none)
    int selectedPiece;

    // Flag for tracking the player's turn (true = white's turn)
    bool isWhiteTurn;

    // Load textures for the chess pieces
    void loadTextures();

    // Draw the chessboard on the window
    void drawBoard();

    // Draw the chess pieces on the window
    void drawPieces();

    // Handle mouse clicks for selecting and moving pieces
    void handleMouseClick(int x, int y);

    // Check if the game is over (checkmate or stalemate)
    bool isGameOver();

    // Reset the game to the initial state
    void resetGame();

    // Show the endgame message
    void showEndGameMessage();

    // Display mode selection (play or analyze)
    void displayModeSelection();

    // Display color selection for Play Mode
    void displayColorSelection();

    // Load Analyze Mode: ask user for PGN import or empty board
    void loadAnalyzeMode();

    // Import PGN file to set up the board
    void importPGN(const std::string &pgnFile);

    // Make a move for the chess engine
    void makeEngineMove(); // You may implement this in your engine logic

    // Get the sprite index for a given piece
    int getSpriteIndex(int piece); // Helper function to map pieces to texture sprites
};

#endif // GUI_H
