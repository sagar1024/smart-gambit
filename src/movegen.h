#ifndef MOVEGEN_H
#define MOVEGEN_H

#include <vector>
#include <utility>
#include "board.h"

class MoveGenerator
{
public:
    // Function to generate all possible moves for the given side
    std::vector<std::pair<int, int>> generateMoves(const Board &board, bool isWhiteTurn);

    std::vector<std::pair<int, int>> getValidMoves(const Board &board)
    {
        return generateMoves(board, board.isWhiteTurn);  // Use the board's turn to get moves
    }

    // New functions to check for check and checkmate
    bool isInCheck(const Board &board, int kingSquare);
    bool isCheckmate(const Board &board, int kingSquare);
    bool isStalemate(const Board &board);

    // Function to generate castling moves
    std::vector<std::pair<int, int>> generateCastlingMoves(const Board &board, bool isWhiteTurn);

    // Helper functions to generate moves for specific piece types
    std::vector<std::pair<int, int>> generatePawnMoves(const Board &board, int startSquare, bool isWhite);
    std::vector<std::pair<int, int>> generateKnightMoves(const Board &board, int startSquare);
    std::vector<std::pair<int, int>> generateBishopMoves(const Board &board, int startSquare);
    std::vector<std::pair<int, int>> generateRookMoves(const Board &board, int startSquare);
    std::vector<std::pair<int, int>> generateQueenMoves(const Board &board, int startSquare);
    std::vector<std::pair<int, int>> generateKingMoves(const Board &board, int startSquare);

private:
    // Function to validate if a move is within board bounds
    bool isValidSquare(int square);
};

#endif // MOVEGEN_H