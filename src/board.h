#ifndef BOARD_H
#define BOARD_H

#include "move.h"
#include <iostream>
#include <array>
#include <vector>

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

    bool isEmptySquare(int row, int col) const;

    // Function to apply a move
    void makeMove(int fromSquare, int toSquare);

    // Function to check if a square is under attack by any opponent's piece
    bool isSquareUnderAttack(int row, int col, bool isWhiteTurn) const;

    // Function to get valid moves
    std::vector<int> getValidMoves(int square);
    std::vector<int> pieceMoves(int square);
    bool isMoveValid(int fromSquare, int toSquare);

    // Functions for castling and checking if a square is empty
    bool canCastleKingSide(bool isWhiteTurn) const;
    bool canCastleQueenSide(bool isWhiteTurn) const;

    // Function to set the en passant target square
    void setEnPassantTargetSquare(int square);

    // Function to get the en passant target square
    int getEnPassantTargetSquare() const;

    // struct Move
    // {
    //     int from;
    //     int to;
    //     Move(int fromSquare, int toSquare) : from(fromSquare), to(toSquare) {}
    // };
    struct Move
    {
        int from;
        int to;
        Move(int fromSquare, int toSquare) : from(fromSquare), to(toSquare) {}
    };

    //Reset the board
    void resetBoard();

    int whiteKingSquare;
    int blackKingSquare;

    //Function to update king's position after a move
    //You need to call this method in makeMove to update the king's position
    void updateKingPosition(int fromSquare, int toSquare)
    {
        if (getPieceAt(fromSquare,toSquare) == KING_W)
        {
            whiteKingSquare = toSquare;
        }
        else if (getPieceAt(fromSquare,toSquare) == KING_B)
        {
            blackKingSquare = toSquare;
        }
    }

    bool isWhiteTurn;  // Track whose turn it is (true for White, false for Black)
    
    // Function to switch turns after every move
    void switchTurn()
    {
        isWhiteTurn = !isWhiteTurn;
    }

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
