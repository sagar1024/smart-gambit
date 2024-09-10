#include <iostream>
#include "board.h"
#include "movegen.h"

// Helper function to convert a square index to row and column
std::pair<int, int> indexToRowCol(int index)
{
    return {index / BOARD_SIZE, index % BOARD_SIZE};
}

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

// En passant
Board::Board()
    : enPassantTargetSquare(-1) // Initialize with -1 to indicate no en passant target square
{
    setupInitialPosition();
}

void Board::setEnPassantTargetSquare(int square)
{
    enPassantTargetSquare = square;
}

int Board::getEnPassantTargetSquare() const
{
    return enPassantTargetSquare;
}

// RULE IMPLEMENTATION
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

void Board::makeMove(int fromSquare, int toSquare)
{
    // Implement logic to move a piece from one square to another
    auto [fromRow, fromCol] = indexToRowCol(fromSquare);
    auto [toRow, toCol] = indexToRowCol(toSquare);

    board[toRow][toCol] = board[fromRow][fromCol];
    board[fromRow][fromCol] = EMPTY;
}
