// #ifndef GUI_H
// #define GUI_H

// #include <SFML/Graphics.hpp>

// #include "board.h"
// #include "movegen.h"
// #include <vector>
// #include <string>

// enum GameMode
// {
//     PLAY_MODE,
//     ANALYZE_MODE
// };

// class GUI
// {
// public:
//     GUI();
//     void run();

//     //Defining functions
//     void drawLogo();
//     void drawMenu();

// private:
//     // Window and GUI elements
//     sf::RenderWindow window;
//     sf::Texture logoTexture;
//     sf::Sprite logoSprite;
//     sf::Texture piecesTextures[12];   // 6 piece types for both white and black
//     sf::RectangleShape squares[8][8]; // Board squares
//     sf::Font font;
//     sf::Text menuText;

//     // Game state
//     Board board;
//     MoveGenerator moveGen;
//     std::vector<sf::Sprite> piecesSprites;
//     int selectedPiece;
//     bool isWhiteTurn;
//     GameMode mode;

//     // Load resources
//     void loadTextures();
//     void loadLogo();
//     void drawBoard();
//     void drawPieces();
//     void handleMouseClick(int x, int y);
//     void displayModeSelection();
//     void displayColorSelection();
//     void loadAnalyzeMode();
//     void importPGN(const std::string &pgnFile);
//     bool isGameOver();
//     void resetGame();
//     void makeEngineMove();
//     void showEndGameMessage();
// };

// #endif // GUI_H

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
