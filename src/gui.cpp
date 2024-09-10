#include "gui.h"
#include <iostream>

// Constants for window and board
const int WINDOW_SIZE = 800;
const int SQUARE_SIZE = WINDOW_SIZE / 8;

// Constructor
GUI::GUI() : window(sf::VideoMode(WINDOW_SIZE, WINDOW_SIZE), "Chess Engine"), isWhiteTurn(true), selectedPiece(-1) {
    loadTextures();
}

// Load textures for the board and pieces
void GUI::loadTextures() {
    if (!piecesTexture.loadFromFile("pieces.png")) {
        std::cerr << "Error loading texture!" << std::endl;
    }

    // Initialize piecesSprites with the corresponding textures
    for (int i = 0; i < 32; ++i) {
        piecesSprites[i].setTexture(piecesTexture);
        // Set the texture rects for the pieces here
        // e.g., piecesSprites[i].setTextureRect(sf::IntRect(0, 0, SQUARE_SIZE, SQUARE_SIZE));
    }

    // Load the board texture if necessary
}

// Run the main game loop
void GUI::run() {
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::MouseButtonPressed) {
                handleMouseClick(event.mouseButton.x, event.mouseButton.y);
            }
        }

        window.clear();
        drawBoard();
        drawPieces();
        window.display();

        if (isGameOver()) {
            showEndGameMessage();
            resetGame();
        }
    }
}

// Draw the chessboard
void GUI::drawBoard() {
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            sf::RectangleShape square(sf::Vector2f(SQUARE_SIZE, SQUARE_SIZE));
            square.setPosition(col * SQUARE_SIZE, row * SQUARE_SIZE);
            square.setFillColor((row + col) % 2 == 0 ? sf::Color::White : sf::Color::Black);
            window.draw(square);
        }
    }
}

// Draw the pieces on the board
void GUI::drawPieces() {
    for (int i = 0; i < 32; ++i) {
        // Position and draw each piece sprite
        piecesSprites[i].setPosition(/* Set correct position based on board state */);
        window.draw(piecesSprites[i]);
    }
}

// Handle mouse click events for piece selection and movement
void GUI::handleMouseClick(int x, int y) {
    int col = x / SQUARE_SIZE;
    int row = y / SQUARE_SIZE;

    int square = row * 8 + col;

    if (selectedPiece == -1) {
        // Select a piece
        if (board.getPieceAt(row, col) != EMPTY) {
            selectedPiece = square;
            // Compute valid moves for the selected piece
            validMoves = board.getValidMoves(selectedPiece);
        }
    } else {
        // Try to move the selected piece
        movePiece(selectedPiece, square);
        selectedPiece = -1;

        if (isWhiteTurn) {
            makeEngineMove();
        }
    }
}

// Highlight valid moves for the selected piece
void GUI::highlightValidMoves() {
    for (auto &move : validMoves) {
        sf::RectangleShape highlight(sf::Vector2f(SQUARE_SIZE, SQUARE_SIZE));
        highlight.setPosition((move.second % 8) * SQUARE_SIZE, (move.second / 8) * SQUARE_SIZE);
        highlight.setFillColor(sf::Color(0, 255, 0, 128));  // Semi-transparent green
        window.draw(highlight);
    }
}

// Move the piece on the board
void GUI::movePiece(int from, int to) {
    board.makeMove(from, to);
    isWhiteTurn = !isWhiteTurn;
}

// Make the engine's move
void GUI::makeEngineMove() {
    Move bestMove = searchEngine.findBestMove(board);
    board.makeMove(bestMove.from, bestMove.to);
    isWhiteTurn = !isWhiteTurn;
}

// Check if the game is over
bool GUI::isGameOver() {
    return board.isCheckmate() || board.isStalemate();
}

// Display the end game message
void GUI::showEndGameMessage() {
    if (board.isCheckmate()) {
        std::string winner = isWhiteTurn ? "Black" : "White";
        std::cout << "Checkmate! " << winner << " wins!" << std::endl;
    } else if (board.isStalemate()) {
        std::cout << "Stalemate! It's a draw!" << std::endl;
    }
}

// Reset the game to the initial state
void GUI::resetGame() {
    board.resetBoard();
    isWhiteTurn = true;
    selectedPiece = -1;
    validMoves.clear();
}
