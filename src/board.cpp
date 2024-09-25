#include <iostream>
#include "board.h"
#include "movegen.h"
#include "utils.h"

// Helper function to convert a square index to row and column
// std::pair<int, int> indexToRowCol(int index)
// {
//     return {index / BOARD_SIZE, index % BOARD_SIZE};
// }

// Constructor: Initialize the board
// Board::Board()
// {
//     setupInitialPosition();
// }
Board::Board()
    : enPassantTargetSquare(-1),
      whiteKingMoved(false), whiteRookKingSideMoved(false), whiteRookQueenSideMoved(false),
      blackKingMoved(false), blackRookKingSideMoved(false), blackRookQueenSideMoved(false)
{
    setupInitialPosition();
    isWhiteTurn = true; // White starts first
}

// Function to set up the initial position of the chessboard
void Board::setupInitialPosition()
{
    // Set up white pieces
    board[0] = {ROOK_W, KNIGHT_W, BISHOP_W, QUEEN_W, KING_W, BISHOP_W, KNIGHT_W, ROOK_W};
    board[1] = {PAWN_W, PAWN_W, PAWN_W, PAWN_W, PAWN_W, PAWN_W, PAWN_W, PAWN_W};

    // Set up black pieces
    board[6] = {PAWN_B, PAWN_B, PAWN_B, PAWN_B, PAWN_B, PAWN_B, PAWN_B, PAWN_B};
    board[7] = {ROOK_B, KNIGHT_B, BISHOP_B, QUEEN_B, KING_B, BISHOP_B, KNIGHT_B, ROOK_B};

    // Set up empty squares
    for (int i = 2; i < 6; ++i)
    {
        board[i].fill(EMPTY);
    }
}

// Function to display the board in the console
void Board::displayBoard() const
{
    for (int row = 0; row < BOARD_SIZE; ++row)
    {
        for (int col = 0; col < BOARD_SIZE; ++col)
        {
            std::cout << board[row][col] << " ";
        }
        std::cout << std::endl;
    }
}

// Function to get the piece at a specific row and column
Piece Board::getPieceAt(int row, int col) const
{
    if (row < 0 || row >= BOARD_SIZE || col < 0 || col >= BOARD_SIZE)
    {
        // Return EMPTY or handle error for out-of-bounds access
        return EMPTY;
    }
    return board[row][col];
}

bool Board::isEmptySquare(int row, int col) const
{
    return getPieceAt(row, col) == EMPTY;
}

bool Board::isSquareUnderAttack(int row, int col, bool isWhiteTurn) const
{
    MoveGenerator moveGen;
    // Iterate over all squares to check for possible attacking moves by opponent pieces
    for (int r = 0; r < BOARD_SIZE; ++r)
    {
        for (int c = 0; c < BOARD_SIZE; ++c)
        {
            Piece piece = getPieceAt(r, c);
            if ((isWhiteTurn && piece > 0) || (!isWhiteTurn && piece < 0))
            {
                // Generate all possible moves for this piece
                std::vector<std::pair<int, int>> possibleMoves;
                if (piece == PAWN_W || piece == PAWN_B)
                {
                    possibleMoves = moveGen.generatePawnMoves(*this, r * BOARD_SIZE + c, isWhiteTurn);
                }
                else if (piece == KNIGHT_W || piece == KNIGHT_B)
                {
                    possibleMoves = moveGen.generateKnightMoves(*this, r * BOARD_SIZE + c);
                }
                else if (piece == BISHOP_W || piece == BISHOP_B)
                {
                    possibleMoves = moveGen.generateBishopMoves(*this, r * BOARD_SIZE + c);
                }
                else if (piece == ROOK_W || piece == ROOK_B)
                {
                    possibleMoves = moveGen.generateRookMoves(*this, r * BOARD_SIZE + c);
                }
                else if (piece == QUEEN_W || piece == QUEEN_B)
                {
                    possibleMoves = moveGen.generateQueenMoves(*this, r * BOARD_SIZE + c);
                }
                else if (piece == KING_W || piece == KING_B)
                {
                    possibleMoves = moveGen.generateKingMoves(*this, r * BOARD_SIZE + c);
                }

                // Check if any of the possible moves can attack the given square
                for (const auto &move : possibleMoves)
                {
                    if (move.second == row * BOARD_SIZE + col)
                    {
                        return true;
                    }
                }
            }
        }
    }

    return false;
}

// RULES IMPLEMENTATION

// Castling rights

// bool Board::canCastleKingSide(bool isWhiteTurn) const
// {
//     if (isWhiteTurn)
//     {
//         if (whiteKingMoved || whiteRookKingSideMoved)
//             return false;

//         // Check if the squares between the king and the rook are empty and not under attack
//         if (isEmptySquare(0, 5) && isEmptySquare(0, 6))
//         {
//             // Additional logic to check if squares are not under attack
//             return true;
//         }
//     }
//     else
//     {
//         if (blackKingMoved || blackRookKingSideMoved)
//             return false;

//         if (isEmptySquare(7, 5) && isEmptySquare(7, 6))
//         {
//             // Additional logic to check if squares are not under attack
//             return true;
//         }
//     }
//     return false;
// }

bool Board::canCastleKingSide(bool isWhiteTurn) const
{
    if (isWhiteTurn)
    {
        if (whiteKingMoved || whiteRookKingSideMoved)
            return false;

        // Check if the squares between the king and the rook are empty
        if (isEmptySquare(0, 5) && isEmptySquare(0, 6))
        {
            // Placeholder: check if squares are not under attack
            if (!isSquareUnderAttack(0, 4, false) && !isSquareUnderAttack(0, 5, false) && !isSquareUnderAttack(0, 6, false))
            {
                return true;
            }
        }
    }
    else
    {
        if (blackKingMoved || blackRookKingSideMoved)
            return false;

        // Check if the squares between the king and the rook are empty
        if (isEmptySquare(7, 5) && isEmptySquare(7, 6))
        {
            // Placeholder: check if squares are not under attack
            if (!isSquareUnderAttack(7, 4, true) && !isSquareUnderAttack(7, 5, true) && !isSquareUnderAttack(7, 6, true))
            {
                return true;
            }
        }
    }
    return false;
}

// bool Board::canCastleQueenSide(bool isWhiteTurn) const
// {
//     if (isWhiteTurn)
//     {
//         if (whiteKingMoved || whiteRookQueenSideMoved)
//             return false;

//         if (isEmptySquare(0, 1) && isEmptySquare(0, 2) && isEmptySquare(0, 3))
//         {
//             // Additional logic to check if squares are not under attack
//             return true;
//         }
//     }
//     else
//     {
//         if (blackKingMoved || blackRookQueenSideMoved)
//             return false;

//         if (isEmptySquare(7, 1) && isEmptySquare(7, 2) && isEmptySquare(7, 3))
//         {
//             // Additional logic to check if squares are not under attack
//             return true;
//         }
//     }
//     return false;
// }

bool Board::canCastleQueenSide(bool isWhiteTurn) const
{
    if (isWhiteTurn)
    {
        if (whiteKingMoved || whiteRookQueenSideMoved)
            return false;

        // Check if the squares between the king and the rook are empty
        if (isEmptySquare(0, 1) && isEmptySquare(0, 2) && isEmptySquare(0, 3))
        {
            // Placeholder: check if squares are not under attack
            if (!isSquareUnderAttack(0, 4, false) && !isSquareUnderAttack(0, 3, false) && !isSquareUnderAttack(0, 2, false))
            {
                return true;
            }
        }
    }
    else
    {
        if (blackKingMoved || blackRookQueenSideMoved)
            return false;

        // Check if the squares between the king and the rook are empty
        if (isEmptySquare(7, 1) && isEmptySquare(7, 2) && isEmptySquare(7, 3))
        {
            // Placeholder: check if squares are not under attack
            if (!isSquareUnderAttack(7, 4, true) && !isSquareUnderAttack(7, 3, true) && !isSquareUnderAttack(7, 2, true))
            {
                return true;
            }
        }
    }
    return false;
}

// EN PASSANT
//  Board::Board()
//      : enPassantTargetSquare(-1) // Initialize with -1 to indicate no en passant target square
//  {
//      setupInitialPosition();
//  }

void Board::setEnPassantTargetSquare(int square)
{
    enPassantTargetSquare = square;
}

int Board::getEnPassantTargetSquare() const
{
    return enPassantTargetSquare;
}

// void Board::makeMove(int fromSquare, int toSquare)
// {
//     // Implement logic to move a piece from one square to another
//     auto [fromRow, fromCol] = indexToRowCol(fromSquare);
//     auto [toRow, toCol] = indexToRowCol(toSquare);

//     board[toRow][toCol] = board[fromRow][fromCol];
//     board[fromRow][fromCol] = EMPTY;

//     //Tracking the kings position
//     updateKingPosition(fromSquare, toSquare);
// }

// The error occurs because structured bindings (auto [var1, var2] = ...) require C++17 or higher
// Replacing the structured bindings
//  void Board::makeMove(int fromSquare, int toSquare)
//  {
//      std::pair<int, int> fromPos = indexToRowCol(fromSquare);
//      int fromRow = fromPos.first;
//      int fromCol = fromPos.second;

//     std::pair<int, int> toPos = indexToRowCol(toSquare);
//     int toRow = toPos.first;
//     int toCol = toPos.second;

//     // Perform the move on the board
//     board[toRow][toCol] = board[fromRow][fromCol];
//     board[fromRow][fromCol] = Piece::EMPTY; // Clear the source square after the move

//     //Tracking the kings position
//     updateKingPosition(fromSquare, toSquare);
// }

void Board::makeMove(int fromSquare, int toSquare)
{
    Piece capturedPiece = board[toSquare / BOARD_SIZE][toSquare % BOARD_SIZE]; // Get the captured piece
    moveHistory.push(Move(fromSquare, toSquare));                              // Record the move
    capturedPieces.push(capturedPiece);                                        // Record the captured piece (even if it's EMPTY)

    board[toSquare / BOARD_SIZE][toSquare % BOARD_SIZE] = board[fromSquare / BOARD_SIZE][fromSquare % BOARD_SIZE]; // Move the piece
    board[fromSquare / BOARD_SIZE][fromSquare % BOARD_SIZE] = EMPTY;                                               // Clear the original square

    updateKingPosition(fromSquare, toSquare); // Update king's position if necessary

    switchTurn(); // Switch the turn
}

// Function to get valid moves
std::vector<int> Board::getValidMoves(int square)
{
    std::vector<int> validMoves;

    // Function that returns all possible moves for the piece at 'square'
    std::vector<int> possibleMoves = pieceMoves(square);

    for (int move : possibleMoves)
    {
        // Here isMoveValid is a function that checks the legality of a move
        if (isMoveValid(square, move))
        {
            validMoves.push_back(move);
        }
    }

    return validMoves;
}

// Implementation of pieceMoves()

// std::vector<int> Board::pieceMoves(int square)
// {
//     std::vector<int> moves;
//     int piece = boardState[square];
//     int row = square / 8;
//     int col = square % 8;

//     // Lambda function to add move if it's valid
//     auto addMoveIfValid = [&](int toSquare)
//     {
//         if (isMoveValid(square, toSquare))
//         {
//             moves.push_back(toSquare);
//         }
//     };

//     switch (piece)
//     {
//     case PAWN_W:
//         // Single square move forward
//         if (row > 0)
//         {
//             addMoveIfValid(square - 8);
//             // Double square move from the starting position
//             if (row == 6 && boardState[square - 8] == EMPTY)
//             {
//                 addMoveIfValid(square - 16);
//             }
//         }
//         // Capture moves
//         if (col > 0 && boardState[square - 9] < 0)
//         { // Capture to the left
//             addMoveIfValid(square - 9);
//         }
//         if (col < 7 && boardState[square - 7] < 0)
//         { // Capture to the right
//             addMoveIfValid(square - 7);
//         }
//         break;

//     case PAWN_B:
//         // Single square move forward
//         if (row < 7)
//         {
//             addMoveIfValid(square + 8);
//             // Double square move from the starting position
//             if (row == 1 && boardState[square + 8] == EMPTY)
//             {
//                 addMoveIfValid(square + 16);
//             }
//         }
//         // Capture moves
//         if (col > 0 && boardState[square + 7] > 0)
//         { // Capture to the left
//             addMoveIfValid(square + 7);
//         }
//         if (col < 7 && boardState[square + 9] > 0)
//         { // Capture to the right
//             addMoveIfValid(square + 9);
//         }
//         break;

//     case KNIGHT_W:
//     case KNIGHT_B:
//         // Knight moves in an 'L' shape
//         for (int r = -2; r <= 2; ++r)
//         {
//             for (int c = -2; c <= 2; ++c)
//             {
//                 if (std::abs(r * c) == 2)
//                 {
//                     int toRow = row + r;
//                     int toCol = col + c;
//                     if (toRow >= 0 && toRow < 8 && toCol >= 0 && toCol < 8)
//                     {
//                         addMoveIfValid(toRow * 8 + toCol);
//                     }
//                 }
//             }
//         }
//         break;

//     case BISHOP_W:
//     case BISHOP_B:
//         // Bishop moves diagonally
//         for (int dr = -1; dr <= 1; dr += 2)
//         {
//             for (int dc = -1; dc <= 1; dc += 2)
//             {
//                 for (int i = 1; i < 8; ++i)
//                 {
//                     int toRow = row + dr * i;
//                     int toCol = col + dc * i;
//                     if (toRow >= 0 && toRow < 8 && toCol >= 0 && toCol < 8)
//                     {
//                         addMoveIfValid(toRow * 8 + toCol);
//                         if (boardState[toRow * 8 + toCol] != EMPTY)
//                             break;
//                     }
//                 }
//             }
//         }
//         break;

//     case ROOK_W:
//     case ROOK_B:
//         // Rook moves horizontally and vertically
//         for (int dr = -1; dr <= 1; dr += 2)
//         {
//             for (int i = 1; i < 8; ++i)
//             {
//                 int toRow = row + dr * i;
//                 if (toRow >= 0 && toRow < 8)
//                 {
//                     addMoveIfValid(toRow * 8 + col);
//                     if (boardState[toRow * 8 + col] != EMPTY)
//                         break;
//                 }
//             }
//         }
//         for (int dc = -1; dc <= 1; dc += 2)
//         {
//             for (int i = 1; i < 8; ++i)
//             {
//                 int toCol = col + dc * i;
//                 if (toCol >= 0 && toCol < 8)
//                 {
//                     addMoveIfValid(row * 8 + toCol);
//                     if (boardState[row * 8 + toCol] != EMPTY)
//                         break;
//                 }
//             }
//         }
//         break;

//     case QUEEN_W:
//     case QUEEN_B:
//         // Queen combines Rook and Bishop moves
//         for (int dr = -1; dr <= 1; ++dr)
//         {
//             for (int dc = -1; dc <= 1; ++dc)
//             {
//                 if (dr != 0 || dc != 0)
//                 {
//                     for (int i = 1; i < 8; ++i)
//                     {
//                         int toRow = row + dr * i;
//                         int toCol = col + dc * i;
//                         if (toRow >= 0 && toRow < 8 && toCol >= 0 && toCol < 8)
//                         {
//                             addMoveIfValid(toRow * 8 + toCol);
//                             if (boardState[toRow * 8 + toCol] != EMPTY)
//                                 break;
//                         }
//                     }
//                 }
//             }
//         }
//         break;

//     case KING_W:
//     case KING_B:
//         // King moves one square in any direction
//         for (int dr = -1; dr <= 1; ++dr)
//         {
//             for (int dc = -1; dc <= 1; ++dc)
//             {
//                 if (dr != 0 || dc != 0)
//                 {
//                     int toRow = row + dr;
//                     int toCol = col + dc;
//                     if (toRow >= 0 && toRow < 8 && toCol >= 0 && toCol < 8)
//                     {
//                         addMoveIfValid(toRow * 8 + toCol);
//                     }
//                 }
//             }
//         }
//         // Castling can be handled separately
//         break;

//     default:
//         break;
//     }

//     return moves;
// }

std::vector<int> Board::pieceMoves(int square)
{
    std::vector<int> moves;
    Piece piece = board[square / 8][square % 8];
    int row = square / 8;
    int col = square % 8;

    // Lambda function to add move if it's valid
    auto addMoveIfValid = [&](int toSquare)
    {
        if (isMoveValid(square, toSquare))
        {
            moves.push_back(toSquare);
        }
    };

    switch (piece)
    {
    case PAWN_W:
        // Single square move forward
        if (row > 0)
        {
            addMoveIfValid(square - 8);
            // Double square move from the starting position
            if (row == 6 && board[row - 1][col] == EMPTY)
            {
                addMoveIfValid(square - 16);
            }
        }
        // Capture moves
        if (col > 0 && board[row - 1][col - 1] >= PAWN_B)
        { // Capture to the left
            addMoveIfValid(square - 9);
        }
        if (col < 7 && board[row - 1][col + 1] >= PAWN_B)
        { // Capture to the right
            addMoveIfValid(square - 7);
        }
        break;

    case PAWN_B:
        // Single square move forward
        if (row < 7)
        {
            addMoveIfValid(square + 8);
            // Double square move from the starting position
            if (row == 1 && board[row + 1][col] == EMPTY)
            {
                addMoveIfValid(square + 16);
            }
        }
        // Capture moves
        if (col > 0 && board[row + 1][col - 1] <= KING_W && board[row + 1][col - 1] != EMPTY)
        { // Capture to the left
            addMoveIfValid(square + 7);
        }
        if (col < 7 && board[row + 1][col + 1] <= KING_W && board[row + 1][col + 1] != EMPTY)
        { // Capture to the right
            addMoveIfValid(square + 9);
        }
        break;

    case KNIGHT_W:
    case KNIGHT_B:
        // Knight moves in an 'L' shape
        for (int r = -2; r <= 2; ++r)
        {
            for (int c = -2; c <= 2; ++c)
            {
                if (std::abs(r * c) == 2)
                {
                    int toRow = row + r;
                    int toCol = col + c;
                    if (toRow >= 0 && toRow < 8 && toCol >= 0 && toCol < 8)
                    {
                        addMoveIfValid(toRow * 8 + toCol);
                    }
                }
            }
        }
        break;

    case BISHOP_W:
    case BISHOP_B:
        // Bishop moves diagonally
        for (int dr = -1; dr <= 1; dr += 2)
        {
            for (int dc = -1; dc <= 1; dc += 2)
            {
                for (int i = 1; i < 8; ++i)
                {
                    int toRow = row + dr * i;
                    int toCol = col + dc * i;
                    if (toRow >= 0 && toRow < 8 && toCol >= 0 && toCol < 8)
                    {
                        addMoveIfValid(toRow * 8 + toCol);
                        if (board[toRow][toCol] != EMPTY)
                            break;
                    }
                }
            }
        }
        break;

    case ROOK_W:
    case ROOK_B:
        // Rook moves horizontally and vertically
        for (int dr = -1; dr <= 1; dr += 2)
        {
            for (int i = 1; i < 8; ++i)
            {
                int toRow = row + dr * i;
                if (toRow >= 0 && toRow < 8)
                {
                    addMoveIfValid(toRow * 8 + col);
                    if (board[toRow][col] != EMPTY)
                        break;
                }
            }
        }
        for (int dc = -1; dc <= 1; dc += 2)
        {
            for (int i = 1; i < 8; ++i)
            {
                int toCol = col + dc * i;
                if (toCol >= 0 && toCol < 8)
                {
                    addMoveIfValid(row * 8 + toCol);
                    if (board[row][toCol] != EMPTY)
                        break;
                }
            }
        }
        break;

    case QUEEN_W:
    case QUEEN_B:
        // Queen combines Rook and Bishop moves
        for (int dr = -1; dr <= 1; ++dr)
        {
            for (int dc = -1; dc <= 1; ++dc)
            {
                if (dr != 0 || dc != 0)
                {
                    for (int i = 1; i < 8; ++i)
                    {
                        int toRow = row + dr * i;
                        int toCol = col + dc * i;
                        if (toRow >= 0 && toRow < 8 && toCol >= 0 && toCol < 8)
                        {
                            addMoveIfValid(toRow * 8 + toCol);
                            if (board[toRow][toCol] != EMPTY)
                                break;
                        }
                    }
                }
            }
        }
        break;

    case KING_W:
    case KING_B:
        // King moves one square in any direction
        for (int dr = -1; dr <= 1; ++dr)
        {
            for (int dc = -1; dc <= 1; ++dc)
            {
                if (dr != 0 || dc != 0)
                {
                    int toRow = row + dr;
                    int toCol = col + dc;
                    if (toRow >= 0 && toRow < 8 && toCol >= 0 && toCol < 8)
                    {
                        addMoveIfValid(toRow * 8 + toCol);
                    }
                }
            }
        }
        // Castling can be handled separately
        break;

    default:
        break;
    }

    return moves;
}

// Implementation of isMoveValid()

// bool Board::isMoveValid(int fromSquare, int toSquare)
// {
//     int piece = boardState[fromSquare];
//     int target = boardState[toSquare];

//     // If the destination square contains a piece of the same color, the move is invalid
//     if ((piece > 0 && target > 0) || (piece < 0 && target < 0))
//     {
//         return false;
//     }

//     // Determine row and column of source and destination
//     int fromRow = fromSquare / 8;
//     int fromCol = fromSquare % 8;
//     int toRow = toSquare / 8;
//     int toCol = toSquare % 8;

//     switch (abs(piece))
//     {
//     case PAWN_W: // or PAWN_B since abs() is used
//         // Pawns move straight ahead or diagonally to capture
//         if (fromCol == toCol)
//         {
//             // Straight move: check if destination is empty
//             if ((piece > 0 && toRow == fromRow - 1) || // White pawn moves up
//                 (piece < 0 && toRow == fromRow + 1))
//             { // Black pawn moves down
//                 return target == EMPTY;
//             }
//             // Double move from starting position
//             if ((piece > 0 && fromRow == 6 && toRow == 4) ||
//                 (piece < 0 && fromRow == 1 && toRow == 3))
//             {
//                 int middleSquare = (fromSquare + toSquare) / 2;
//                 return target == EMPTY && boardState[middleSquare] == EMPTY;
//             }
//         }
//         else if (std::abs(fromCol - toCol) == 1)
//         {
//             // Diagonal move: must capture a piece
//             if ((piece > 0 && toRow == fromRow - 1) || // White pawn captures diagonally
//                 (piece < 0 && toRow == fromRow + 1))
//             { // Black pawn captures diagonally
//                 return target != EMPTY;
//             }
//         }
//         break;

//     case KNIGHT_W: // or BLACK_KNIGHT
//         // Knights move in an 'L' shape (2 squares in one direction, 1 in the other)
//         if ((std::abs(fromRow - toRow) == 2 && std::abs(fromCol - toCol) == 1) ||
//             (std::abs(fromRow - toRow) == 1 && std::abs(fromCol - toCol) == 2))
//         {
//             return true;
//         }
//         break;

//     case BISHOP_W: // or BLACK_BISHOP
//         // Bishops move diagonally
//         if (std::abs(fromRow - toRow) == std::abs(fromCol - toCol))
//         {
//             // Check all squares between fromSquare and toSquare
//             int stepRow = (toRow > fromRow) ? 1 : -1;
//             int stepCol = (toCol > fromCol) ? 1 : -1;
//             for (int i = 1; i < std::abs(fromRow - toRow); ++i)
//             {
//                 if (boardState[(fromRow + i * stepRow) * 8 + (fromCol + i * stepCol)] != EMPTY)
//                 {
//                     return false;
//                 }
//             }
//             return true;
//         }
//         break;

//     case ROOK_W: // or BLACK_ROOK
//         // Rooks move horizontally or vertically
//         if (fromRow == toRow || fromCol == toCol)
//         {
//             // Horizontal or vertical move
//             int step = (fromRow == toRow) ? (toCol > fromCol ? 1 : -1) : (toRow > fromRow ? 8 : -8);
//             for (int i = fromSquare + step; i != toSquare; i += step)
//             {
//                 if (boardState[i] != EMPTY)
//                 {
//                     return false;
//                 }
//             }
//             return true;
//         }
//         break;

//     case QUEEN_W: // or BLACK_QUEEN
//         // Queens move like both a rook and a bishop
//         if (std::abs(fromRow - toRow) == std::abs(fromCol - toCol))
//         {
//             // Diagonal move (Bishop-like)
//             int stepRow = (toRow > fromRow) ? 1 : -1;
//             int stepCol = (toCol > fromCol) ? 1 : -1;
//             for (int i = 1; i < std::abs(fromRow - toRow); ++i)
//             {
//                 if (boardState[(fromRow + i * stepRow) * 8 + (fromCol + i * stepCol)] != EMPTY)
//                 {
//                     return false;
//                 }
//             }
//             return true;
//         }
//         else if (fromRow == toRow || fromCol == toCol)
//         {
//             // Horizontal or vertical move (Rook-like)
//             int step = (fromRow == toRow) ? (toCol > fromCol ? 1 : -1) : (toRow > fromRow ? 8 : -8);
//             for (int i = fromSquare + step; i != toSquare; i += step)
//             {
//                 if (boardState[i] != EMPTY)
//                 {
//                     return false;
//                 }
//             }
//             return true;
//         }
//         break;

//     case KING_W: // or BLACK_KING
//         // Kings move one square in any direction
//         if (std::abs(fromRow - toRow) <= 1 && std::abs(fromCol - toCol) <= 1)
//         {
//             return true;
//         }
//         // Castling logic can be added here if needed
//         break;

//     default:
//         return false;
//     }

//     return false;
// }

bool Board::isMoveValid(int fromSquare, int toSquare)
{
    int fromRow = fromSquare / 8;
    int fromCol = fromSquare % 8;
    int toRow = toSquare / 8;
    int toCol = toSquare % 8;

    Piece piece = board[fromRow][fromCol];
    Piece target = board[toRow][toCol];

    // Check if the target square is occupied by the player's own piece
    if ((piece <= KING_W && target <= KING_W && target != EMPTY) || (piece >= PAWN_B && target >= PAWN_B))
    {
        return false;
    }

    // Add more validation rules here (e.g., specific movement rules for each piece)
    // Here, we will keep it simple and return true for any valid move
    return true;
}

void Board::resetBoard()
{
    setupInitialPosition(); // Reset the board to the initial position
    whiteKingMoved = false;
    whiteRookKingSideMoved = false;
    whiteRookQueenSideMoved = false;
    blackKingMoved = false;
    blackRookKingSideMoved = false;
    blackRookQueenSideMoved = false;
    enPassantTargetSquare = -1;
}

void Board::undoMove()
{
    if (!moveHistory.empty())
    {
        // Get the last move
        Move lastMove = moveHistory.top();
        moveHistory.pop();

        // Revert the move on the board
        board[lastMove.from / BOARD_SIZE][lastMove.from % BOARD_SIZE] = board[lastMove.to / BOARD_SIZE][lastMove.to % BOARD_SIZE];
        board[lastMove.to / BOARD_SIZE][lastMove.to % BOARD_SIZE] = capturedPieces.top(); // Restore captured piece (if any)
        capturedPieces.pop();

        // Update the king's position if necessary
        updateKingPosition(lastMove.to, lastMove.from);

        // Switch turn back to the previous player
        switchTurn();
    }
}

void Board::reset()
{
    setupInitialPosition();               // Reset the board to its initial setup
    moveHistory = std::stack<Move>();     // Clear the move history
    capturedPieces = std::stack<Piece>(); // Clear the captured pieces stack
    isWhiteTurn = true;                   // Reset the turn to white
}

// Helper function to check if a piece is white
bool isWhitePiece(Piece piece)
{
    return piece >= PAWN_W && piece <= KING_W; // Assuming white pieces are defined in this range
}

// Helper function to check if a piece is black
bool isBlackPiece(Piece piece)
{
    return piece >= PAWN_B && piece <= KING_B; // Assuming black pieces are defined in this range
}

