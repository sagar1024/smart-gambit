// #include "board.h"
// #include "movegen.h"
// #include "evaluation.h"
// #include "search.h"
// #include "gui.h"

// #include <iostream>

// // Constants for window and board
// const int WINDOW_SIZE = 800;
// const int SQUARE_SIZE = WINDOW_SIZE / 8;

// // Constructor
// GUI::GUI(int searchDepth)
//     : window(sf::VideoMode(WINDOW_SIZE, WINDOW_SIZE), "Chess Engine"),
//       searchEngine(searchDepth), // Pass the search depth parameter here
//       isWhiteTurn(true),
//       selectedPiece(-1)
// {
//     loadTextures();
// }

// // Load textures for the board and pieces
// void GUI::loadTextures()
// {
//     if (!piecesTexture.loadFromFile("pieces.png"))
//     {
//         std::cerr << "Error loading texture!" << std::endl;
//     }

//     // Initialize piecesSprites with the corresponding textures
//     for (int i = 0; i < 32; ++i)
//     {
//         piecesSprites[i].setTexture(piecesTexture);
//         // Set the texture rects for the pieces here
//         // e.g., piecesSprites[i].setTextureRect(sf::IntRect(0, 0, SQUARE_SIZE, SQUARE_SIZE));
//     }

//     // Load the board texture if necessary
// }

// // Run the main game loop
// void GUI::run()
// {
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

//         if (isGameOver())
//         {
//             showEndGameMessage();
//             resetGame();
//         }
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
//             square.setPosition(col * SQUARE_SIZE, row * SQUARE_SIZE);
//             square.setFillColor((row + col) % 2 == 0 ? sf::Color::White : sf::Color::Black);
//             window.draw(square);
//         }
//     }
// }

// void GUI::drawPieces()
// {
//     for (int row = 0; row < 8; ++row)
//     {
//         for (int col = 0; col < 8; ++col)
//         {
//             int piece = board.getPieceAt(row, col);
//             int spriteIndex;

//             switch (piece)
//             {
//             case PAWN_W:
//                 spriteIndex = 0;
//                 break;
//             case KNIGHT_W:
//                 spriteIndex = 1;
//                 break;
//             case BISHOP_W:
//                 spriteIndex = 2;
//                 break;
//             case ROOK_W:
//                 spriteIndex = 3;
//                 break;
//             case QUEEN_W:
//                 spriteIndex = 4;
//                 break;
//             case KING_W:
//                 spriteIndex = 5;
//                 break;
//             case PAWN_B:
//                 spriteIndex = 6;
//                 break;
//             case KNIGHT_B:
//                 spriteIndex = 7;
//                 break;
//             case BISHOP_B:
//                 spriteIndex = 8;
//                 break;
//             case ROOK_B:
//                 spriteIndex = 9;
//                 break;
//             case QUEEN_B:
//                 spriteIndex = 10;
//                 break;
//             case KING_B:
//                 spriteIndex = 11;
//                 break;
//             default:
//                 spriteIndex = -1;
//                 break; //Or handle erroR
//             }

//             if (spriteIndex != -1)
//             {
//                 // Valid piece
//                 piecesSprites[spriteIndex].setPosition(col * SQUARE_SIZE, row * SQUARE_SIZE);
//                 window.draw(piecesSprites[spriteIndex]);
//             }
//         }
//     }
// }

// void GUI::handleMouseClick(int x, int y)
// {
//     int col = x / SQUARE_SIZE;
//     int row = y / SQUARE_SIZE;

//     int square = row * 8 + col;

//     if (selectedPiece == -1)
//     {
//         // Select a piece
//         if (board.getPieceAt(row, col) != EMPTY)
//         {
//             selectedPiece = square;

//             // Compute valid moves for the selected piece
//             std::vector<int> moveSquares = board.getValidMoves(selectedPiece);

//             // Convert move squares to row/col pairs and store in validMoves
//             validMoves.clear();
//             for (int moveSquare : moveSquares) {
//                 int moveRow = moveSquare / 8;
//                 int moveCol = moveSquare % 8;
//                 validMoves.push_back({moveRow, moveCol});
//             }
//         }
//     }
//     else
//     {
//         // Try to move the selected piece
//         movePiece(selectedPiece, square);
//         selectedPiece = -1;

//         if (isWhiteTurn)
//         {
//             makeEngineMove();
//         }
//     }
// }

// // Highlight valid moves for the selected piece
// void GUI::highlightValidMoves()
// {
//     for (auto &move : validMoves)
//     {
//         sf::RectangleShape highlight(sf::Vector2f(SQUARE_SIZE, SQUARE_SIZE));
//         highlight.setPosition((move.second % 8) * SQUARE_SIZE, (move.second / 8) * SQUARE_SIZE);
//         highlight.setFillColor(sf::Color(0, 255, 0, 128)); // Semi-transparent green
//         window.draw(highlight);
//     }
// }

// // Move the piece on the board
// void GUI::movePiece(int from, int to)
// {
//     board.makeMove(from, to);
//     isWhiteTurn = !isWhiteTurn;
// }

// // Make the engine's move
// void GUI::makeEngineMove()
// {
//     Board::Move bestMove = search.searchBestMove(board);
//     board.makeMove(bestMove.from, bestMove.to);
//     isWhiteTurn = !isWhiteTurn;
// }

// // Check if the game is over
// bool GUI::isGameOver()
// {
//     return board.isCheckmate() || board.isStalemate();
// }

// // Display the end game message
// void GUI::showEndGameMessage()
// {
//     if (board.isCheckmate())
//     {
//         std::string winner = isWhiteTurn ? "Black" : "White";
//         std::cout << "Checkmate! " << winner << " wins!" << std::endl;
//     }
//     else if (board.isStalemate())
//     {
//         std::cout << "Stalemate! It's a draw!" << std::endl;
//     }
// }

// // Reset the game to the initial state
// void GUI::resetGame()
// {
//     board.resetBoard();
//     isWhiteTurn = true;
//     selectedPiece = -1;
//     validMoves.clear();
// }

// Alternate code -

#include "gui.h"
#include "search.h"
#include "move.h"
#include "movegen.h"
#include "evaluation.h"

#include <iostream>

// GUI constructor
GUI::GUI() : selectedPiece(-1), isWhiteTurn(true)
{
    resetGame(); // Initialize the game
}

// Select between Play or Analyze mode
void GUI::selectMode()
{
    int modeChoice;
    std::cout << "Select mode: 1. Play  2. Analyze" << std::endl;
    std::cin >> modeChoice;

    if (modeChoice == 1)
    {
        playMode();
    }
    else if (modeChoice == 2)
    {
        analyzeMode();
    }
    else
    {
        std::cout << "Invalid choice!" << std::endl;
    }
}

// Play mode logic
void GUI::playMode()
{
    int colorChoice;
    std::cout << "Choose your color: 1. White  2. Black" << std::endl;
    std::cin >> colorChoice;

    if (colorChoice == 1)
    {
        isWhiteTurn = true;
    }
    else if (colorChoice == 2)
    {
        isWhiteTurn = false;
        makeEngineMove(); // Engine makes the first move as black
    }
    else
    {
        std::cout << "Invalid choice!" << std::endl;
    }

    // Game loop
    while (!isGameOver())
    {
        int x, y;
        std::cout << "Enter mouse click coordinates (x y): ";
        std::cin >> x >> y;
        handleMouseClick(x, y); // Handle player move
        makeEngineMove();       // Engine makes its move
    }

    showEndGameMessage(); // Display the game result
}

// Analyze mode logic
void GUI::analyzeMode()
{
    int choice;
    std::cout << "Select analysis option: 1. Load PGN  2. Start with initial board" << std::endl;
    std::cin >> choice;

    if (choice == 1)
    {
        loadPGN();
    }
    else if (choice == 2)
    {
        board.resetBoard(); // Set up the initial board position
    }
    else
    {
        std::cout << "Invalid choice!" << std::endl;
        return;
    }

    // Analysis loop
    while (true)
    {
        int x, y;
        std::cout << "Enter mouse click coordinates (x y): ";
        std::cin >> x >> y;
        handleMouseClick(x, y); // User moves pieces freely

        // After each move, ask the engine for the best move
        Move bestMove = search.searchBestMove(board, 3, isWhiteTurn);
        std::cout << "Engine suggests: " << bestMove.from << " -> " << bestMove.to << std::endl;
    }
}

// Handle mouse click events for piece selection and movement
void GUI::handleMouseClick(int x, int y)
{
    int col = x / BOARD_SIZE;
    int row = y / BOARD_SIZE;
    int square = row * 8 + col;

    if (selectedPiece == -1)
    {
        // Select a piece
        if (board.getPieceAt(row, col) != EMPTY)
        {
            selectedPiece = square;

            // Compute valid moves for the selected piece
            validMoves = moveGen.getValidMoves(board);
        }
    }
    else
    {
        // Try to move the selected piece
        board.makeMove(selectedPiece, square);
        selectedPiece = -1;

        if (isWhiteTurn)
        {
            makeEngineMove(); // Let the engine move after the player
        }
    }
}

// Make the engine's move
void GUI::makeEngineMove()
{
    Move bestMove = search.searchBestMove(board, 3, isWhiteTurn);
    board.makeMove(bestMove.from, bestMove.to);
    isWhiteTurn = !isWhiteTurn;
}

// Check if the game is over
// bool GUI::isGameOver()
// {
//     return moveGen.isCheckmate(board, kingSquare) || moveGen.isStalemate(board);
// }
bool GUI::isGameOver()
{
    kingSquare = isWhiteTurn ? board.whiteKingSquare : board.blackKingSquare;
    return moveGen.isCheckmate(board, kingSquare);
}

// Display the end game message
void GUI::showEndGameMessage()
{
    if (moveGen.isCheckmate(board,kingSquare))
    {
        std::string winner = isWhiteTurn ? "Black" : "White";
        std::cout << "Checkmate! " << winner << " wins!" << std::endl;
    }
    else if (moveGen.isStalemate(board))
    {
        std::cout << "Stalemate! It's a draw!" << std::endl;
    }
}

// Reset the game to the initial state
void GUI::resetGame()
{
    board.resetBoard();
    isWhiteTurn = true;
    selectedPiece = -1;
    validMoves.clear();
}

// Load a PGN file for analysis
void GUI::loadPGN()
{
    std::string filename;
    std::cout << "Enter PGN file path: ";
    std::cin >> filename;

    // Parse and load the PGN file
    // You will need to implement PGN parsing or use a third-party library.
    // Once loaded, set the board state.
}
