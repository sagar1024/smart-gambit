#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <array>

// Enum to represent pieces and empty squares
enum Piece
{
    EMPTY = 0,
    PAWN_W,
    KNIGHT_W,
    BISHOP_W,
    ROOK_W,
    QUEEN_W,
    KING_W,
    PAWN_B,
    KNIGHT_B,
    BISHOP_B,
    ROOK_B,
    QUEEN_B,
    KING_B
};

// Constants for board size
const int BOARD_SIZE = 8;

class Board
{
public:
    Board();                                  // Constructor to initialize the board
    void displayBoard() const;                // Function to display the board
    Piece getPieceAt(int row, int col) const; // Function to get the piece at a specific row and column

    // Function to set the en passant target square
    void setEnPassantTargetSquare(int square);

    // Function to get the en passant target square
    int getEnPassantTargetSquare() const;

    // Functions for castling and checking if a square is empty
    bool canCastleKingSide(bool isWhiteTurn) const;
    bool canCastleQueenSide(bool isWhiteTurn) const;
    bool isEmptySquare(int row, int col) const;

    // Function to apply a move
    void makeMove(int fromSquare, int toSquare);

    // Function to check if a square is under attack by any opponent's piece
    bool isSquareUnderAttack(int row, int col, bool isWhiteTurn) const;

private:
    std::array<std::array<Piece, BOARD_SIZE>, BOARD_SIZE> board; // 8x8 board
    void setupInitialPosition();                                 // Function to set up the initial chess position

    // Variable to store the en passant target square
    int enPassantTargetSquare;

    bool whiteKingMoved;
    bool whiteRookKingSideMoved;
    bool whiteRookQueenSideMoved;

    bool blackKingMoved;
    bool blackRookKingSideMoved;
    bool blackRookQueenSideMoved;
};

#endif // BOARD_H