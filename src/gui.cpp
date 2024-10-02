#include "gui.h"
#include <iostream>

// Set the tile size for the chessboard squares (64x64 pixel tiles)
const float GUI::tileSize = 64.f;

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

void GUI::drawBoard()
{
    // Chessboard starts at the top-left corner
    // float squareSize = boardTexture.getSize().x / 8.0f; // Assuming the texture is 8x8 squares
    float squareSize = boardTexture.getSize().x / 8.0f;
    float boardSize = squareSize * 8.0f; // Total size of the chessboard (8 squares)

    // Get the window size
    sf::Vector2u windowSize = window.getSize();

    // Calculate the top-left corner position to center the board
    float boardX = (windowSize.x - boardSize) / 2.0f;
    float boardY = (windowSize.y - boardSize) / 2.0f;

    // Now, when drawing the board, use the calculated position (boardX, boardY)
    // Example:
    sf::Sprite boardSprite(boardTexture);
    boardSprite.setPosition(boardX, boardY);
    window.draw(boardSprite);

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
                square.setFillColor(sf::Color(140, 69, 19)); // Dark brown
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
    //window.draw(logoSprite);

    // Draw the pieces on the chessboard after the board squares
    drawPieces();
}

std::string getPieceTextureName(int piece)
{
    switch (piece)
    {
    case PAWN_W:
        return "whitePawn";
    case KNIGHT_W:
        return "whiteKnight";
    case BISHOP_W:
        return "whiteBishop";
    case ROOK_W:
        return "whiteRook";
    case QUEEN_W:
        return "whiteQueen";
    case KING_W:
        return "whiteKing";
    case PAWN_B:
        return "blackPawn";
    case KNIGHT_B:
        return "blackKnight";
    case BISHOP_B:
        return "blackBishop";
    case ROOK_B:
        return "blackRook";
    case QUEEN_B:
        return "blackQueen";
    case KING_B:
        return "blackKing";
    default:
        return "";
    }
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
            else if (piece == BISHOP_W)
                pieceSprite.setTexture(pieceTextures["whiteBishop"]);
            else if (piece == ROOK_W)
                pieceSprite.setTexture(pieceTextures["whiteRook"]);
            else if (piece == QUEEN_W)
                pieceSprite.setTexture(pieceTextures["whiteQueen"]);
            else if (piece == KING_W)
                pieceSprite.setTexture(pieceTextures["whiteKing"]);
            else if (piece == PAWN_B)
                pieceSprite.setTexture(pieceTextures["blackPawn"]);
            else if (piece == KNIGHT_B)
                pieceSprite.setTexture(pieceTextures["blackKnight"]);
            else if (piece == BISHOP_B)
                pieceSprite.setTexture(pieceTextures["blackBishop"]);
            else if (piece == ROOK_B)
                pieceSprite.setTexture(pieceTextures["blackRook"]);
            else if (piece == QUEEN_B)
                pieceSprite.setTexture(pieceTextures["blackQueen"]);
            else if (piece == KING_B)
                pieceSprite.setTexture(pieceTextures["blackKing"]);

            // Scale down the piece sprite to fit your tile size
            // pieceSprite.setScale(0.05f, 0.05f);
            // pieceSprite.setScale(tileSize / pieceTextures.getSize().x, tileSize / pieceTextures.getSize().y);
            // pieceSprite.setScale(
            //     tileSize / pieceTextures[piece].getSize().x,
            //     tileSize / pieceTextures[piece].getSize().y);

            std::string textureKey = getPieceTextureName(piece);
            if (!textureKey.empty())
            {
                // pieceSprite.setTexture(pieceTextures[textureKey]);

                pieceSprite.setScale(
                    tileSize / pieceTextures[textureKey].getSize().x,
                    tileSize / pieceTextures[textureKey].getSize().y);

                // pieceSprite.setPosition(col * tileSize, row * tileSize);
                // window.draw(pieceSprite);
            }

            // Set the position of the piece on the board
            pieceSprite.setPosition(col * tileSize, (row + 1) * tileSize); // Adjust based on grid size
            window.draw(pieceSprite);                                      // Draw each piece
        }
    }
}

// In GUI class
sf::Vector2i selectedSquare(-1, -1); // To store the selected square

void GUI::handleInput() // Handle input for piece movement
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
            // Get mouse position in window coordinates
            sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

            // Convert to board coordinates (assume square size is 80x80, adjust as needed)
            int squareSize = 80;
            sf::Vector2i boardPosition(mousePosition.x / squareSize, mousePosition.y / squareSize);

            // Handle selection of piece
            if (selectedSquare == sf::Vector2i(-1, -1)) // No piece selected yet
            {
                // Check if there's a piece on the clicked square
                if (isPieceOnSquare(boardPosition)) // Check if a piece exists on the square
                {
                    selectedSquare = boardPosition; // Store the selected square
                }
            }
            else // A piece is already selected, now move it
            {
                // Extract row and column for selectedSquare and boardPosition
                int fromRow = selectedSquare.y;
                int fromCol = selectedSquare.x;
                int toRow = boardPosition.y;
                int toCol = boardPosition.x;

                // Attempt to move the piece from selectedSquare to boardPosition
                if (board.isMoveValid(fromRow * 8 + fromCol, toRow * 8 + toCol)) // isMoveValid now takes row and col for both squares
                {
                    board.makeMove(fromRow * 8 + fromCol, toRow * 8 + toCol); // makeMove now takes row and col for both squares
                }

                // After the move or invalid attempt, reset selectedSquare
                selectedSquare = sf::Vector2i(-1, -1);
            }
        }
    }
}

void GUI::highlightSquare(sf::Vector2i square)
{
    sf::RectangleShape highlight(sf::Vector2f(tileSize, tileSize));
    highlight.setPosition(square.x * tileSize, square.y * tileSize);
    highlight.setFillColor(sf::Color(255, 255, 0, 100)); // Yellow with some transparency
    window.draw(highlight);
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
    sf::Text playButton("Play", font, 20);
    sf::Text analyzeButton("Analyze", font, 20);
    sf::Text exitButton("Exit", font, 20);

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
        turnText.setPosition(100, 650); // Position below the board
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

bool GUI::isPieceOnSquare(const sf::Vector2i &square)
{
    // Convert the board position to the internal board representation.
    int boardIndex = square.y * 8 + square.x;

    // Assuming your `Board` class has a function like `getPieceAt` that returns the piece.
    Piece piece = board.getPieceAt(square.y, square.x);

    // Return true if the square contains any piece, false if it's empty.
    return piece != Piece::EMPTY;
}

void GUI::showGameOverScreen(bool isWhiteWinner)
{
    sf::Font font;
    font.loadFromFile("texture/font.ttf");

    sf::Text resultText(isWhiteWinner ? "White won!" : "Black won!", font, 50);
    resultText.setPosition(100, 300); // Adjust this to center it
    window.draw(resultText);

    // Button for Restart
    sf::Text restartButton("Restart", font, 30);
    restartButton.setPosition(100, 400); // Adjust the position
    window.draw(restartButton);

    // Button for Exit
    sf::Text exitButton("Exit", font, 30);
    exitButton.setPosition(100, 500); // Adjust the position
    window.draw(exitButton);

    // Display the window with text
    window.display();

    // Event handling for clicking the buttons
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            window.close();
        }
        else if (event.type == sf::Event::MouseButtonPressed)
        {
            if (event.mouseButton.button == sf::Mouse::Left)
            {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                // Check if restart button is clicked
                if (restartButton.getGlobalBounds().contains(mousePos.x, mousePos.y))
                {
                    // Call your restart function
                    restartGame();
                }

                // Check if exit button is clicked
                if (exitButton.getGlobalBounds().contains(mousePos.x, mousePos.y))
                {
                    window.close(); // Exit the game
                }
            }
        }
    }
}

void GUI::restartGame()
{
    // Reset the board to the initial state
    board.resetBoard(); // Assuming you have a chess engine object with a resetBoard function

    // Reset any GUI-specific elements
    isGameOver = false;

    // currentPlayer = WHITE;  // Or whatever indicates the current turn
    isWhiteTurn = true;

    // You may need to refresh the GUI
    window.clear();
    drawBoard();
    window.display();
}
