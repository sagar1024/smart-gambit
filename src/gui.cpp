// #include <iostream>
// #include <fstream>

// #include "gui.h"
// #include "movegen.h"
// #include "evaluation.h"
// #include "search.h"

// #include <SFML/Graphics.hpp>
// #include <SFML/Window.hpp>
// #include <SFML/System.hpp>

// // Constants
// const int WINDOW_SIZE = 800;
// const int SQUARE_SIZE = WINDOW_SIZE / 8;
// const std::string PIECE_TEXTURE_FILE = "pieces.png";

// // Constructor
// GUI::GUI() : window(sf::VideoMode(WINDOW_SIZE, WINDOW_SIZE), "SmartGambit Chess Engine"), selectedPiece(-1), isWhiteTurn(true), mode(PLAY_MODE)
// {
//     loadTextures(); // Load textures for pieces
//     resetGame();    // Initialize the game
// }

// // Load textures for the pieces
// void GUI::loadTextures()
// {
//     if (!piecesTexture.loadFromFile(PIECE_TEXTURE_FILE))
//     {
//         std::cerr << "Error loading texture: " << PIECE_TEXTURE_FILE << std::endl;
//     }

//     for (int i = 0; i < 32; ++i)
//     {
//         piecesSprites[i].setTexture(piecesTexture);
//         piecesSprites[i].setScale(sf::Vector2f(
//             static_cast<float>(SQUARE_SIZE) / piecesTexture.getSize().x,
//             static_cast<float>(SQUARE_SIZE) / piecesTexture.getSize().y));
//     }
// }

// // Main game loop
// void GUI::run()
// {
//     displayModeSelection(); // Ask user to select Play/Analyze mode

//     while (window.isOpen())
//     {
//         sf::Event event;
//         while (window.pollEvent(event))
//         {
//             if (event.type == sf::Event::Closed)
//             {
//                 window.close();
//             }
//             else if (event.type == sf::Event::MouseButtonPressed)
//             {
//                 handleMouseClick(event.mouseButton.x, event.mouseButton.y);
//             }
//         }

//         window.clear();
//         drawBoard();
//         drawPieces();
//         window.display();

//         if (isGameOver() && mode == PLAY_MODE)
//         {
//             showEndGameMessage();
//             resetGame();
//         }
//     }
// }

// // Display mode selection to the user (Play or Analyze)
// void GUI::displayModeSelection()
// {
//     std::cout << "Select mode:\n";
//     std::cout << "1. Play against the engine\n";
//     std::cout << "2. Analyze a chess position\n";
//     std::cout << "Enter 1 or 2: ";
//     int selection;
//     std::cin >> selection;

//     if (selection == 1)
//     {
//         mode = PLAY_MODE;
//         std::cout << "You selected Play Mode.\n";
//         displayColorSelection(); // Ask for color
//     }
//     else if (selection == 2)
//     {
//         mode = ANALYZE_MODE;
//         std::cout << "You selected Analyze Mode.\n";
//         loadAnalyzeMode(); // Start Analyze Mode
//     }
//     else
//     {
//         std::cerr << "Invalid selection. Defaulting to Play Mode.\n";
//         mode = PLAY_MODE;
//         displayColorSelection();
//     }
// }

// // Ask the user for their preferred color (White/Black)
// void GUI::displayColorSelection()
// {
//     std::cout << "Select your color:\n";
//     std::cout << "1. White\n";
//     std::cout << "2. Black\n";
//     std::cout << "Enter 1 or 2: ";
//     int selection;
//     std::cin >> selection;

//     if (selection == 1)
//     {
//         isWhiteTurn = true; // Player starts with white
//     }
//     else if (selection == 2)
//     {
//         isWhiteTurn = false; // Engine starts with white
//         makeEngineMove();    // Engine plays first
//     }
//     else
//     {
//         std::cerr << "Invalid selection. Defaulting to White.\n";
//         isWhiteTurn = true;
//     }
// }

// // Load Analyze Mode: ask user whether to import PGN or start with an empty board
// void GUI::loadAnalyzeMode()
// {
//     std::cout << "Analyze Mode:\n";
//     std::cout << "1. Import a PGN file\n";
//     std::cout << "2. Start with an empty board\n";
//     std::cout << "Enter 1 or 2: ";
//     int selection;
//     std::cin >> selection;

//     if (selection == 1)
//     {
//         std::string pgnFile;
//         std::cout << "Enter the PGN file path: ";
//         std::cin >> pgnFile;
//         importPGN(pgnFile); // Load the PGN file
//     }
//     else if (selection == 2)
//     {
//         board.resetBoard(); // Reset the board
//     }
//     else
//     {
//         std::cerr << "Invalid selection. Defaulting to an empty board.\n";
//         board.resetBoard();
//     }
// }

// // Import PGN file to set up the board
// void GUI::importPGN(const std::string &pgnFile)
// {
//     std::ifstream file(pgnFile);
//     if (!file.is_open())
//     {
//         std::cerr << "Error opening PGN file.\n";
//         return;
//     }

//     std::string line;
//     while (std::getline(file, line))
//     {
//         // PGN parsing logic goes here
//         std::cout << "Reading PGN file...\n";
//         // You can parse PGN and set up the board based on the game
//     }

//     file.close();
//     std::cout << "PGN imported successfully.\n";
// }

// // Draw the chessboard
// void GUI::drawBoard()
// {
//     for (int row = 0; row < 8; ++row)
//     {
//         for (int col = 0; col < 8; ++col)
//         {
//             sf::RectangleShape square(sf::Vector2f(SQUARE_SIZE, SQUARE_SIZE));
//             square.setPosition(col * SQUARE_SIZE, row * SQUARE_SIZE);
//             square.setFillColor((row + col) % 2 == 0 ? sf::Color::White : sf::Color::Black);
//             window.draw(square);
//         }
//     }
// }

// // Draw pieces on the board
// void GUI::drawPieces()
// {
//     for (int row = 0; row < 8; ++row)
//     {
//         for (int col = 0; col < 8; ++col)
//         {
//             int piece = board.getPieceAt(row, col);
//             if (piece != EMPTY)
//             {
//                 int spriteIndex = getSpriteIndex(piece);
//                 piecesSprites[spriteIndex].setPosition(col * SQUARE_SIZE, row * SQUARE_SIZE);
//                 window.draw(piecesSprites[spriteIndex]);
//             }
//         }
//     }
// }

// // Handle mouse clicks for selecting and moving pieces
// void GUI::handleMouseClick(int x, int y)
// {
//     int col = x / SQUARE_SIZE;
//     int row = y / SQUARE_SIZE;

//     int square = row * 8 + col;

//     if (selectedPiece == -1)
//     {
//         if (board.getPieceAt(row, col) != EMPTY)
//         {
//             selectedPiece = square;
//             validMoves = moveGen.getValidMoves(board);
//         }
//     }
//     else
//     {
//         board.makeMove(selectedPiece, square);
//         selectedPiece = -1;

//         if (mode == PLAY_MODE && isWhiteTurn)
//         {
//             makeEngineMove();
//         }
//     }
// }

// // Check if the game is over
// bool GUI::isGameOver()
// {
//     return moveGen.isCheckmate(board,kingSquare) || moveGen.isStalemate(board);
// }

// // Reset the game to initial state
// void GUI::resetGame()
// {
//     board.resetBoard();
//     isWhiteTurn = true;
//     selectedPiece = -1;
//     validMoves.clear();
// }

// // Show the endgame message
// void GUI::showEndGameMessage()
// {
//     if (moveGen.isCheckmate(board,kingSquare))
//     {
//         std::string winner = isWhiteTurn ? "Black" : "White";
//         std::cout << "Checkmate! " << winner << " wins!" << std::endl;
//     }
//     else if (moveGen.isStalemate(board))
//     {
//         std::cout << "Stalemate! It's a draw!" << std::endl;
//     }
// }

// Alternate code -

// #include <iostream>
// #include <fstream>

// #include "gui.h"
// #include "movegen.h"
// #include "evaluation.h"
// #include "search.h"

// #include <SFML/Graphics.hpp>
// #include <SFML/Window.hpp>
// #include <SFML/System.hpp>

// // Constants
// const int WINDOW_WIDTH = 800;
// const int WINDOW_HEIGHT = 1000; // Extra space for logo and menu
// const int SQUARE_SIZE = WINDOW_WIDTH / 8;
// const std::string PIECE_TEXTURE_FILE = "textures/pieces.png";
// const std::string LOGO_TEXTURE_FILE = "textures/logo.png";

// // Constructor
// GUI::GUI()
//     : window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "SmartGambit Chess Engine"),
//       selectedPiece(-1), isWhiteTurn(true), mode(PLAY_MODE)
// {
//     loadTextures(); // Load textures for logo and pieces
//     resetGame();    // Initialize the game
// }

// // Load textures for the logo and pieces
// void GUI::loadTextures()
// {
//     if (!logoTexture.loadFromFile(LOGO_TEXTURE_FILE))
//     {
//         std::cerr << "Error loading texture: " << LOGO_TEXTURE_FILE << std::endl;
//     }
//     logoSprite.setTexture(logoTexture);
//     logoSprite.setPosition(0, 0);
//     logoSprite.setScale(WINDOW_WIDTH / static_cast<float>(logoTexture.getSize().x),
//                         150 / static_cast<float>(logoTexture.getSize().y));

//     if (!piecesTexture.loadFromFile(PIECE_TEXTURE_FILE))
//     {
//         std::cerr << "Error loading texture: " << PIECE_TEXTURE_FILE << std::endl;
//     }

//     // Load individual piece sprites
//     for (int i = 0; i < 32; ++i)
//     {
//         piecesSprites[i].setTexture(piecesTexture);
//         piecesSprites[i].setScale(
//             static_cast<float>(SQUARE_SIZE) / piecesTexture.getSize().x,
//             static_cast<float>(SQUARE_SIZE) / piecesTexture.getSize().y);
//     }
// }

// // Main game loop
// void GUI::run()
// {
//     displayModeSelection(); // Ask user to select Play/Analyze mode

//     while (window.isOpen())
//     {
//         sf::Event event;
//         while (window.pollEvent(event))
//         {
//             if (event.type == sf::Event::Closed)
//             {
//                 window.close();
//             }
//             else if (event.type == sf::Event::MouseButtonPressed)
//             {
//                 handleMouseClick(event.mouseButton.x, event.mouseButton.y);
//             }
//         }

//         window.clear();
//         drawLogo(); // Draw logo at the top
//         drawMenu(); // Draw the menu or board based on the mode
//         window.display();

//         if (isGameOver() && mode == PLAY_MODE)
//         {
//             showEndGameMessage();
//             resetGame();
//         }
//     }
// }

// // Display mode selection to the user (Play or Analyze)
// void GUI::displayModeSelection()
// {
//     std::cout << "Select mode:\n";
//     std::cout << "1. Play against the engine\n";
//     std::cout << "2. Analyze a chess position\n";
//     std::cout << "Enter 1 or 2: ";
//     int selection;
//     std::cin >> selection;

//     if (selection == 1)
//     {
//         mode = PLAY_MODE;
//         displayColorSelection(); // Ask for color
//     }
//     else if (selection == 2)
//     {
//         mode = ANALYZE_MODE;
//         loadAnalyzeMode(); // Start Analyze Mode
//     }
//     else
//     {
//         std::cerr << "Invalid selection. Defaulting to Play Mode.\n";
//         mode = PLAY_MODE;
//         displayColorSelection();
//     }
// }

// // Ask the user for their preferred color (White/Black)
// void GUI::displayColorSelection()
// {
//     std::cout << "Select your color:\n";
//     std::cout << "1. White\n";
//     std::cout << "2. Black\n";
//     std::cout << "Enter 1 or 2: ";
//     int selection;
//     std::cin >> selection;

//     if (selection == 1)
//     {
//         isWhiteTurn = true; // Player starts with white
//     }
//     else if (selection == 2)
//     {
//         isWhiteTurn = false; // Engine starts with white
//         makeEngineMove();    // Engine plays first
//     }
//     else
//     {
//         std::cerr << "Invalid selection. Defaulting to White.\n";
//         isWhiteTurn = true;
//     }
// }

// // Load Analyze Mode: ask user whether to import PGN or start with an empty board
// void GUI::loadAnalyzeMode()
// {
//     std::cout << "Analyze Mode:\n";
//     std::cout << "1. Import a PGN file\n";
//     std::cout << "2. Start with an empty board\n";
//     std::cout << "Enter 1 or 2: ";

//     int selection;
//     std::cin >> selection;

//     if (selection == 1)
//     {
//         std::string pgnFile;
//         std::cout << "Enter the PGN file path: ";
//         std::cin >> pgnFile;
//         importPGN(pgnFile); // Load the PGN file
//     }
//     else if (selection == 2)
//     {
//         board.resetBoard(); // Reset the board
//     }
//     else
//     {
//         std::cerr << "Invalid selection. Defaulting to an empty board.\n";
//         board.resetBoard();
//     }
// }

// // Draw the chessboard
// void GUI::drawBoard()
// {
//     for (int row = 0; row < 8; ++row)
//     {
//         for (int col = 0; col < 8; ++col)
//         {
//             sf::RectangleShape square(sf::Vector2f(SQUARE_SIZE, SQUARE_SIZE));
//             square.setPosition(col * SQUARE_SIZE, 150 + row * SQUARE_SIZE);                        // Adjust for logo
//             square.setFillColor((row + col) % 2 == 0 ? sf::Color::White : sf::Color(139, 69, 19)); // Light brown and dark brown
//             window.draw(square);
//         }
//     }
// }

// // Draw pieces on the board
// void GUI::drawPieces()
// {
//     for (int row = 0; row < 8; ++row)
//     {
//         for (int col = 0; col < 8; ++col)
//         {
//             int piece = board.getPieceAt(row, col);
//             if (piece != EMPTY)
//             {
//                 int spriteIndex = getSpriteIndex(piece);
//                 piecesSprites[spriteIndex].setPosition(col * SQUARE_SIZE, 150 + row * SQUARE_SIZE); // Adjust for logo
//                 window.draw(piecesSprites[spriteIndex]);
//             }
//         }
//     }
// }

// // Handle mouse clicks for selecting and moving pieces
// void GUI::handleMouseClick(int x, int y)
// {
//     int col = x / SQUARE_SIZE;
//     int row = (y - 150) / SQUARE_SIZE; // Adjust for logo

//     if (row < 0 || row >= 8 || col < 0 || col >= 8)
//         return;

//     int square = row * 8 + col;

//     if (selectedPiece == -1)
//     {
//         if (board.getPieceAt(row, col) != EMPTY)
//         {
//             selectedPiece = square;
//             validMoves = moveGen.getValidMoves(board);
//         }
//     }
//     else
//     {
//         board.makeMove(selectedPiece, square);
//         selectedPiece = -1;

//         if (mode == PLAY_MODE && isWhiteTurn)
//         {
//             makeEngineMove();
//         }
//     }
// }

// // Draw the SmartGambit logo
// void GUI::drawLogo()
// {
//     window.draw(logoSprite); // Always draw the logo at the top
// }

// // Display menu (Play or Analyze) or the chessboard based on the user's choice
// void GUI::drawMenu()
// {
//     if (mode == PLAY_MODE || mode == ANALYZE_MODE)
//     {
//         drawBoard();
//         drawPieces();
//     }
// }

// Alternate code -

#include "gui.h"
#include <iostream>

// Set the tile size for the chessboard squares (64x64 pixel tiles)
const float GUI::tileSize = 64.f;

// Constructor to load textures and initialize the window
// GUI::GUI() : window(sf::VideoMode(640, 720), "SmartGambit Chess Engine"), isWhiteTurn(true)
// {
//     loadTextures(); // Load all textures (pieces, board, logo)
// }

// Constructor definition that takes the render window reference
GUI::GUI(sf::RenderWindow &window) : window(window)
{
    // Load textures for pieces, board, and logo
    loadTextures();

    // Set up initial game state (optional)
    isWhiteTurn = true;
    board.setupInitialPosition();
}

// Main loop for running the GUI
void GUI::run()
{
    while (window.isOpen())
    {
        handleMenu(); // Display and handle main menu interaction
        window.clear();
        drawBoard(); // Draw the chessboard and pieces
        drawPieces();

        window.display();
    }
}

// Function to load all textures
void GUI::loadTextures()
{
    // Load chessboard texture
    if (!boardTexture.loadFromFile("texture/board.png"))
    {
        std::cerr << "Error loading board texture" << std::endl;
    }

    // Load piece textures for white and black pieces
    if (!whitePiecesTexture.loadFromFile("texture/white_pieces.png") ||
        !blackPiecesTexture.loadFromFile("texture/black_pieces.png"))
    {
        std::cerr << "Error loading piece textures" << std::endl;
    }

    // Load SmartGambit logo texture
    if (!logoTexture.loadFromFile("texture/logo.png"))
    {
        std::cerr << "Error loading logo texture" << std::endl;
    }

    // Create sprites for the board and logo
    boardSprite.setTexture(boardTexture);
    logoSprite.setTexture(logoTexture);
    logoSprite.setPosition(0, 0); // Position logo at the top

    // Initialize piece textures (map for each type of piece)
    pieceTextures["whitePawn"].loadFromFile("texture/white_pawn.png");
    pieceTextures["whiteKnight"].loadFromFile("texture/white_knight.png");
    pieceTextures["whiteBishop"].loadFromFile("texture/white_bishop.png");
    pieceTextures["whiteRook"].loadFromFile("texture/white_rook.png");
    pieceTextures["whiteQueen"].loadFromFile("texture/white_queen.png");
    pieceTextures["whiteKing"].loadFromFile("texture/white_king.png");

    pieceTextures["blackPawn"].loadFromFile("texture/black_pawn.png");
    pieceTextures["blackKnight"].loadFromFile("texture/black_knight.png");
    pieceTextures["blackBishop"].loadFromFile("texture/black_bishop.png");
    pieceTextures["blackRook"].loadFromFile("texture/black_rook.png");
    pieceTextures["blackQueen"].loadFromFile("texture/black_queen.png");
    pieceTextures["blackKing"].loadFromFile("texture/black_king.png");
}

// // Function to draw the chessboard
// void GUI::drawBoard()
// {
//     window.draw(boardSprite); // Draw the chessboard texture
//     window.draw(logoSprite);  // Draw the SmartGambit logo
// }

void GUI::drawBoard()
{
    // Chessboard starts at the top-left corner
    float squareSize = boardTexture.getSize().x / 8.0f; // Assuming the texture is 8x8 squares

    // Loop through the rows and columns of the chessboard
    for (int row = 0; row < 8; ++row)
    {
        for (int col = 0; col < 8; ++col)
        {
            // Create a rectangle shape for each square
            sf::RectangleShape square(sf::Vector2f(squareSize, squareSize));

            // Set the position of the square
            square.setPosition(col * squareSize, row * squareSize);

            // Alternate the colors between light and dark brown
            if ((row + col) % 2 == 0)
            {
                square.setFillColor(sf::Color(139, 69, 19)); // Dark brown
            }
            else
            {
                square.setFillColor(sf::Color(222, 184, 135)); // Light brown
            }

            // Draw the square
            window.draw(square);
        }
    }

    // Draw the SmartGambit logo at the top of the window
    window.draw(logoSprite);

    // Draw the pieces on the chessboard after the board squares
    drawPieces();
}

// Function to draw the chess pieces
void GUI::drawPieces()
{
    for (int row = 0; row < boardSize; ++row)
    {
        for (int col = 0; col < boardSize; ++col)
        {
            int piece = board.getPieceAt(row, col); // Get the piece from the board
            sf::Sprite pieceSprite;

            // Map the piece type to the corresponding sprite
            if (piece == PAWN_W)
                pieceSprite.setTexture(pieceTextures["whitePawn"]);
            else if (piece == KNIGHT_W)
                pieceSprite.setTexture(pieceTextures["whiteKnight"]);
            // Add other piece mappings...

            // Set the position of the piece on the board
            pieceSprite.setPosition(col * tileSize, (row + 1) * tileSize); // Adjust based on grid size
            window.draw(pieceSprite);                                      // Draw each piece
        }
    }
}

// Handle input for piece movement
void GUI::handleInput()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();

        if (event.type == sf::Event::MouseButtonPressed)
        {
            // Handle piece selection and movement
        }
    }
}

// Handle main menu for selecting Play, Analyze, or Exit
void GUI::handleMenu()
{
    sf::Font font;
    if (!font.loadFromFile("texture/font.ttf"))
    {
        std::cerr << "Error loading font" << std::endl;
    }

    // Create menu buttons for "Play", "Analyze", and "Exit"
    sf::Text playButton("Play", font, 30);
    sf::Text analyzeButton("Analyze", font, 30);
    sf::Text exitButton("Exit", font, 30);

    // Position buttons on the window
    playButton.setPosition(50, 500);
    analyzeButton.setPosition(50, 550);
    exitButton.setPosition(50, 600);

    window.draw(playButton);
    window.draw(analyzeButton);
    window.draw(exitButton);

    // Handle user clicking on buttons (mouse input)
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        if (playButton.getGlobalBounds().contains(mousePos.x, mousePos.y))
        {
            playMode(isWhite);
        }
        else if (analyzeButton.getGlobalBounds().contains(mousePos.x, mousePos.y))
        {
            analyzeMode();
        }
        else if (exitButton.getGlobalBounds().contains(mousePos.x, mousePos.y))
        {
            window.close();
        }
    }
}

// Without taking "bool isWhite" into consideration
//  void GUI::playMode()
//  {
//      bool gameActive = true;
//      bool pieceSelected = false;
//      sf::Vector2i selectedPiecePos;
//      Move bestMove;

//     while (gameActive && window.isOpen())
//     {
//         sf::Event event;
//         while (window.pollEvent(event))
//         {
//             if (event.type == sf::Event::Closed)
//             {
//                 window.close();
//             }

//             if (event.type == sf::Event::MouseButtonPressed)
//             {
//                 if (event.mouseButton.button == sf::Mouse::Left)
//                 {
//                     sf::Vector2i clickPos = sf::Mouse::getPosition(window);

//                     // Convert mouse click position to board grid coordinates
//                     int col = clickPos.x / tileSize;
//                     int row = (clickPos.y - tileSize) / tileSize; // offset due to logo

//                     if (row >= 0 && row < boardSize && col >= 0 && col < boardSize)
//                     {
//                         if (!pieceSelected)
//                         {
//                             // Select the piece
//                             if (board.getPieceAt(row, col) != EMPTY)
//                             {
//                                 pieceSelected = true;
//                                 selectedPiecePos = sf::Vector2i(col, row);
//                             }
//                         }
//                         else
//                         {
//                             // // Move the selected piece
//                             // board.makeMove(selectedPiecePos.y, selectedPiecePos.x, row, col);
//                             // pieceSelected = false;

//                             // // Check if the game is over (checkmate or stalemate)
//                             // if (moveGen.isCheckmate(board,kingSquare))
//                             // {
//                             //     std::cout << (isWhiteTurn ? "White won!" : "Black won!") << std::endl;
//                             //     gameActive = false;
//                             // }
//                             // else if (moveGen.isStalemate(board))
//                             // {
//                             //     std::cout << "Stalemate!" << std::endl;
//                             //     gameActive = false;
//                             // }

//                             // isWhiteTurn = !isWhiteTurn; // Toggle turn
//                             // Move the selected piece
//                             int fromSquare = selectedPiecePos.y * 8 + selectedPiecePos.x; // Convert selected piece position to square index
//                             int toSquare = row * 8 + col;                                 // Convert destination position to square index

//                             board.makeMove(fromSquare, toSquare); // Use the updated makeMove function
//                             pieceSelected = false;

//                             // Check if the game is over (checkmate or stalemate)
//                             if (moveGen.isCheckmate(board, kingSquare))
//                             {
//                                 std::cout << (isWhiteTurn ? "White won!" : "Black won!") << std::endl;
//                                 gameActive = false;
//                             }
//                             else if (moveGen.isStalemate(board))
//                             {
//                                 std::cout << "Stalemate!" << std::endl;
//                                 gameActive = false;
//                             }

//                             isWhiteTurn = !isWhiteTurn; // Toggle turn
//                         }
//                     }
//                 }
//             }
//         }

//         // Drawing the board, pieces, and game information
//         window.clear();
//         drawBoard();
//         drawPieces();

//         // Display turn information
//         sf::Font font;
//         font.loadFromFile("texture/font.ttf");
//         sf::Text turnText(isWhiteTurn ? "White to move" : "Black to move", font, 30);
//         turnText.setPosition(10, 650); // Position below the board
//         window.draw(turnText);

//         // Display result or back button
//         sf::Text backButton("Back to Home", font, 30);
//         backButton.setPosition(400, 650); // Position back to home button

//         window.draw(backButton);
//         if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
//         {
//             sf::Vector2i mousePos = sf::Mouse::getPosition(window);
//             if (backButton.getGlobalBounds().contains(mousePos.x, mousePos.y))
//             {
//                 return; // Exit to main menu
//             }
//         }

//         window.display();
//     }
// }

void GUI::playMode(bool isWhite)
{
    bool gameActive = true;
    bool pieceSelected = false;
    sf::Vector2i selectedPiecePos;
    Move bestMove;

    // Set the turn based on the player's choice
    this->isWhiteTurn = isWhite; // Start with the selected color

    while (gameActive && window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    sf::Vector2i clickPos = sf::Mouse::getPosition(window);

                    // Convert mouse click position to board grid coordinates
                    int col = clickPos.x / tileSize;
                    int row = (clickPos.y - tileSize) / tileSize; // offset due to logo

                    if (row >= 0 && row < boardSize && col >= 0 && col < boardSize)
                    {
                        if (!pieceSelected)
                        {
                            // Select the piece if it's the player's turn
                            Piece piece = board.getPieceAt(row, col);
                            if (piece != EMPTY && (isWhiteTurn == isWhite) && ((isWhite && isWhitePiece(piece)) || (!isWhite && isBlackPiece(piece))))
                            {
                                pieceSelected = true;
                                selectedPiecePos = sf::Vector2i(col, row);
                            }
                        }
                        else
                        {
                            // Move the selected piece
                            int fromSquare = selectedPiecePos.y * 8 + selectedPiecePos.x; // Convert selected piece position to square index
                            int toSquare = row * 8 + col;                                 // Convert destination position to square index

                            board.makeMove(fromSquare, toSquare); // Use the updated makeMove function
                            pieceSelected = false;

                            // Check if the game is over (checkmate or stalemate)
                            if (moveGen.isCheckmate(board, kingSquare))
                            {
                                std::cout << (isWhiteTurn ? "White won!" : "Black won!") << std::endl;
                                gameActive = false;
                            }
                            else if (moveGen.isStalemate(board))
                            {
                                std::cout << "Stalemate!" << std::endl;
                                gameActive = false;
                            }

                            isWhiteTurn = !isWhiteTurn; // Toggle turn
                        }
                    }
                }
            }
        }

        // Drawing the board, pieces, and game information
        window.clear();
        drawBoard();
        drawPieces();

        // Display turn information
        sf::Font font;
        font.loadFromFile("texture/font.ttf");
        sf::Text turnText(isWhiteTurn ? "White to move" : "Black to move", font, 30);
        turnText.setPosition(10, 650); // Position below the board
        window.draw(turnText);

        // Display result or back button
        sf::Text backButton("Back to Home", font, 30);
        backButton.setPosition(400, 650); // Position back to home button

        window.draw(backButton);
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            if (backButton.getGlobalBounds().contains(mousePos.x, mousePos.y))
            {
                return; // Exit to main menu
            }
        }

        window.display();
    }
}

void GUI::analyzeMode()
{
    bool analyzeActive = true;
    sf::Vector2i selectedPiecePos;
    bool pieceSelected = false;

    while (analyzeActive && window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    sf::Vector2i clickPos = sf::Mouse::getPosition(window);
                    int col = clickPos.x / tileSize;
                    int row = (clickPos.y - tileSize) / tileSize;

                    if (row >= 0 && row < boardSize && col >= 0 && col < boardSize)
                    {
                        if (!pieceSelected)
                        {
                            if (board.getPieceAt(row, col) != EMPTY)
                            {
                                pieceSelected = true;
                                selectedPiecePos = sf::Vector2i(col, row);
                            }
                        }
                        else
                        {
                            int fromSquare = selectedPiecePos.y * 8 + selectedPiecePos.x;
                            int toSquare = row * 8 + col;
                            board.makeMove(fromSquare, toSquare);
                            pieceSelected = false;
                        }
                    }
                }
            }
        }

        // Drawing the board, pieces, and analysis buttons
        window.clear();
        drawBoard();
        drawPieces();

        sf::Font font;
        font.loadFromFile("texture/font.ttf");

        // Button: Import PGN
        sf::Text importPGNButton("Import PGN", font, 20);
        importPGNButton.setPosition(10, 650);
        window.draw(importPGNButton);

        // Button: Undo Move
        sf::Text undoMoveButton("Undo Move", font, 20);
        undoMoveButton.setPosition(150, 650);
        window.draw(undoMoveButton);

        // Button: Reset Board
        sf::Text resetButton("Reset Board", font, 20);
        resetButton.setPosition(250, 650);
        window.draw(resetButton);

        // Button: Evaluation
        sf::Text evaluationButton("Evaluation", font, 20);
        evaluationButton.setPosition(350, 650);
        window.draw(evaluationButton);

        // Button: Best Move
        sf::Text bestMoveButton("Best Move", font, 20);
        bestMoveButton.setPosition(450, 650);
        window.draw(bestMoveButton);

        // Handle button clicks
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            if (importPGNButton.getGlobalBounds().contains(mousePos.x, mousePos.y))
            {
                // Logic for importing PGN (this could be implemented by reading PGN files)
                std::cout << "Import PGN clicked" << std::endl;
            }
            else if (undoMoveButton.getGlobalBounds().contains(mousePos.x, mousePos.y))
            {
                // Undo the last move
                board.undoMove();
            }
            else if (resetButton.getGlobalBounds().contains(mousePos.x, mousePos.y))
            {
                // Reset the board
                board.reset();
            }
            else if (evaluationButton.getGlobalBounds().contains(mousePos.x, mousePos.y))
            {
                // Evaluate the current position
                int eval = evaluation.evaluate(board);
                std::cout << (eval > 0 ? "White is better" : (eval < 0 ? "Black is better" : "Equal")) << std::endl;
            }
            else if (bestMoveButton.getGlobalBounds().contains(mousePos.x, mousePos.y))
            {
                // Display the best move for the current position
                // Move bestMove = search.searchBestMove(board, 3, isWhiteTurn);
                // std::cout << "Best move: from (" << bestMove.from.x << ", " << bestMove.from.y << ") to (" << bestMove.to.x << ", " << bestMove.to.y << ")" << std::endl;

                // Display the best move for the current position
                Move bestMove = search.searchBestMove(board, 3, isWhiteTurn);

                // Convert from and to into row and column
                int fromRow = bestMove.from / BOARD_SIZE;
                int fromCol = bestMove.from % BOARD_SIZE;
                int toRow = bestMove.to / BOARD_SIZE;
                int toCol = bestMove.to % BOARD_SIZE;

                std::cout << "Best move: from (" << fromRow << ", " << fromCol << ") to (" << toRow << ", " << toCol << ")" << std::endl;
            }
        }
    }

    window.display();
}
