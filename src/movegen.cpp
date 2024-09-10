#include <iostream>
#include "movegen.h"

// Helper function to convert a square index to row and column
std::pair<int, int> indexToRowCol(int index)
{
    return {index / BOARD_SIZE, index % BOARD_SIZE};
}

std::vector<std::pair<int, int>> MoveGenerator::generateMoves(const Board &board, bool isWhiteTurn)
{
    std::vector<std::pair<int, int>> moves;

    for (int square = 0; square < 64; ++square)
    {
        auto [row, col] = indexToRowCol(square);
        int piece = board.getPieceAt(row, col);

        if ((isWhiteTurn && piece > 0) || (!isWhiteTurn && piece < 0))
        {
            switch (std::abs(piece))
            {
            case 1:
                moves.insert(moves.end(), generatePawnMoves(board, square, isWhiteTurn).begin(), generatePawnMoves(board, square, isWhiteTurn).end());
                break;
            case 2:
                moves.insert(moves.end(), generateKnightMoves(board, square).begin(), generateKnightMoves(board, square).end());
                break;
            case 3:
                moves.insert(moves.end(), generateBishopMoves(board, square).begin(), generateBishopMoves(board, square).end());
                break;
            case 4:
                moves.insert(moves.end(), generateRookMoves(board, square).begin(), generateRookMoves(board, square).end());
                break;
            case 5:
                moves.insert(moves.end(), generateQueenMoves(board, square).begin(), generateQueenMoves(board, square).end());
                break;
            case 6:
                moves.insert(moves.end(), generateKingMoves(board, square).begin(), generateKingMoves(board, square).end());
                break;
            }
        }
    }

    return moves;
}

// std::vector<std::pair<int, int>> MoveGenerator::generatePawnMoves(const Board &board, int startSquare, bool isWhite)
// {
//     std::vector<std::pair<int, int>> moves;
//     auto [startRow, startCol] = indexToRowCol(startSquare);
//     int direction = isWhite ? -1 : 1; // Pawns move up for white, down for black

//     // Single square move
//     int singleStepSquare = (startRow + direction) * BOARD_SIZE + startCol;
//     if (isValidSquare(singleStepSquare) && board.getPieceAt(startRow + direction, startCol) == 0)
//     {
//         moves.emplace_back(startSquare, singleStepSquare);

//         // Double square move from initial position
//         if ((isWhite && startRow == 6) || (!isWhite && startRow == 1))
//         {
//             int doubleStepSquare = (startRow + 2 * direction) * BOARD_SIZE + startCol;
//             if (isValidSquare(doubleStepSquare) && board.getPieceAt(startRow + 2 * direction, startCol) == 0)
//             {
//                 moves.emplace_back(startSquare, doubleStepSquare);
//             }
//         }
//     }

//     // Captures
//     for (int colOffset : {-1, 1})
//     {
//         int captureRow = startRow + direction;
//         int captureCol = startCol + colOffset;
//         int captureSquare = captureRow * BOARD_SIZE + captureCol;

//         if (isValidSquare(captureSquare))
//         {
//             int targetPiece = board.getPieceAt(captureRow, captureCol);
//             if (targetPiece != 0 && ((isWhite && targetPiece < 0) || (!isWhite && targetPiece > 0)))
//             {
//                 moves.emplace_back(startSquare, captureSquare);
//             }
//         }
//     }

//     return moves;
// }

std::vector<std::pair<int, int>> MoveGenerator::generatePawnMoves(const Board &board, int startSquare, bool isWhite)
{
    std::vector<std::pair<int, int>> moves;
    auto [startRow, startCol] = indexToRowCol(startSquare);
    int direction = isWhite ? -1 : 1; // Pawns move up for white, down for black

    // Single square move
    int singleStepSquare = (startRow + direction) * BOARD_SIZE + startCol;
    if (isValidSquare(singleStepSquare) && board.getPieceAt(startRow + direction, startCol) == 0)
    {
        // Check for promotion
        if ((isWhite && startRow + direction == 0) || (!isWhite && startRow + direction == 7))
        {
            // Handle promotion (for simplicity, promoting to a queen)
            moves.emplace_back(startSquare, singleStepSquare);
        }
        else
        {
            moves.emplace_back(startSquare, singleStepSquare);
        }

        // Double square move from initial position
        if ((isWhite && startRow == 6) || (!isWhite && startRow == 1))
        {
            int doubleStepSquare = (startRow + 2 * direction) * BOARD_SIZE + startCol;
            if (isValidSquare(doubleStepSquare) && board.getPieceAt(startRow + 2 * direction, startCol) == 0)
            {
                moves.emplace_back(startSquare, doubleStepSquare);
            }
        }
    }

    // Captures
    for (int colOffset : {-1, 1})
    {
        int captureRow = startRow + direction;
        int captureCol = startCol + colOffset;
        int captureSquare = captureRow * BOARD_SIZE + captureCol;

        if (isValidSquare(captureSquare))
        {
            int targetPiece = board.getPieceAt(captureRow, captureCol);
            if (targetPiece != 0 && ((isWhite && targetPiece < 0) || (!isWhite && targetPiece > 0)))
            {
                // Check for promotion
                if ((isWhite && captureRow == 0) || (!isWhite && captureRow == 7))
                {
                    // Handle promotion (for simplicity, promoting to a queen)
                    moves.emplace_back(startSquare, captureSquare);
                }
                else
                {
                    moves.emplace_back(startSquare, captureSquare);
                }
            }
        }
    }

    // En passant capture
    int enPassantTarget = board.getEnPassantTargetSquare();
    if (enPassantTarget != -1)
    {
        for (int colOffset : {-1, 1})
        {
            int enPassantCol = startCol + colOffset;
            if (enPassantCol >= 0 && enPassantCol < BOARD_SIZE)
            {
                int enPassantSquare = (startRow + direction) * BOARD_SIZE + enPassantCol;
                if (enPassantSquare == enPassantTarget)
                {
                    moves.emplace_back(startSquare, enPassantSquare);
                }
            }
        }
    }

    return moves;
}

// std::vector<std::pair<int, int>> MoveGenerator::generateKnightMoves(const Board &board, int startSquare)
// {
//     std::vector<std::pair<int, int>> moves;
//     static const int knightOffsets[] = {-17, -15, -10, -6, 6, 10, 15, 17};

//     for (int offset : knightOffsets)
//     {
//         int targetSquare = startSquare + offset;

//         if (isValidSquare(targetSquare))
//         {
//             int targetPiece = board.getPieceAt(targetSquare/BOARD_SIZE,targetSquare%BOARD_SIZE);
//             if (targetPiece == 0 || (targetPiece > 0 && board.getPieceAt(startSquare/BOARD_SIZE,startSquare%BOARD_SIZE) < 0) || (targetPiece < 0 && board.getPieceAt(startSquare/BOARD_SIZE,startSquare%BOARD_SIZE) > 0))
//             {
//                 moves.emplace_back(startSquare, targetSquare);
//             }
//         }
//     }

//     return moves;
// }

std::vector<std::pair<int, int>> MoveGenerator::generateKnightMoves(const Board &board, int startSquare)
{
    std::vector<std::pair<int, int>> moves;
    static const int knightOffsets[] = {-17, -15, -10, -6, 6, 10, 15, 17};

    auto [startRow, startCol] = indexToRowCol(startSquare);

    for (int offset : knightOffsets)
    {
        int targetSquare = startSquare + offset;
        auto [targetRow, targetCol] = indexToRowCol(targetSquare);

        if (isValidSquare(targetSquare))
        {
            int targetPiece = board.getPieceAt(targetRow, targetCol);
            int startPiece = board.getPieceAt(startRow, startCol);

            // Check if the target square is empty or contains an opponent's piece
            if (targetPiece == 0 || (targetPiece > 0 && startPiece < 0) || (targetPiece < 0 && startPiece > 0))
            {
                moves.emplace_back(startSquare, targetSquare);
            }
        }
    }

    return moves;
}

// std::vector<std::pair<int, int>> MoveGenerator::generateBishopMoves(const Board &board, int startSquare)
// {
//     std::vector<std::pair<int, int>> moves;
//     static const int bishopOffsets[] = {-9, -7, 7, 9};

//     for (int offset : bishopOffsets)
//     {
//         for (int n = 1; n < 8; ++n)
//         {
//             int targetSquare = startSquare + n * offset;
//             if (isValidSquare(targetSquare))
//             {
//                 int targetPiece = board.getPieceAt(targetSquare / BOARD_SIZE, targetSquare % BOARD_SIZE);
//                 if (targetPiece == 0)
//                 {
//                     moves.emplace_back(startSquare, targetSquare);
//                 }
//                 else
//                 {
//                     if ((targetPiece > 0 && board.getPieceAt(startSquare / BOARD_SIZE, startSquare % BOARD_SIZE) < 0) || (targetPiece < 0 && board.getPieceAt(startSquare / BOARD_SIZE, startSquare % BOARD_SIZE) > 0))
//                     {
//                         moves.emplace_back(startSquare, targetSquare);
//                     }
//                     break; // Blocked by another piece
//                 }
//             }
//         }
//     }

//     return moves;
// }

std::vector<std::pair<int, int>> MoveGenerator::generateBishopMoves(const Board &board, int startSquare)
{
    std::vector<std::pair<int, int>> moves;
    static const int bishopOffsets[] = {-9, -7, 7, 9};

    auto [startRow, startCol] = indexToRowCol(startSquare);
    int startPiece = board.getPieceAt(startRow, startCol);

    for (int offset : bishopOffsets)
    {
        for (int n = 1; n < 8; ++n)
        {
            int targetSquare = startSquare + n * offset;
            auto [targetRow, targetCol] = indexToRowCol(targetSquare);

            if (isValidSquare(targetSquare))
            {
                int targetPiece = board.getPieceAt(targetRow, targetCol);

                if (targetPiece == 0)
                {
                    // Empty square, valid move
                    moves.emplace_back(startSquare, targetSquare);
                }
                else
                {
                    // Target square contains a piece
                    if ((targetPiece > 0 && startPiece < 0) || (targetPiece < 0 && startPiece > 0))
                    {
                        // Opponent's piece, valid capture
                        moves.emplace_back(startSquare, targetSquare);
                    }
                    break; // Blocked by another piece, stop exploring this direction
                }
            }
            else
            {
                break; // Out of bounds, stop exploring this direction
            }
        }
    }

    return moves;
}

// std::vector<std::pair<int, int>> MoveGenerator::generateRookMoves(const Board &board, int startSquare)
// {
//     std::vector<std::pair<int, int>> moves;
//     static const int rookOffsets[] = {-8, -1, 1, 8};

//     for (int offset : rookOffsets)
//     {
//         for (int n = 1; n < 8; ++n)
//         {
//             int targetSquare = startSquare + n * offset;
//             if (isValidSquare(targetSquare))
//             {
//                 int targetPiece = board.getPieceAt(targetSquare / BOARD_SIZE, targetSquare % BOARD_SIZE);
//                 if (targetPiece == 0)
//                 {
//                     moves.emplace_back(startSquare, targetSquare);
//                 }
//                 else
//                 {
//                     if ((targetPiece > 0 && board.getPieceAt(startSquare / BOARD_SIZE, startSquare % BOARD_SIZE) < 0) || (targetPiece < 0 && board.getPieceAt(startSquare / BOARD_SIZE, startSquare % BOARD_SIZE) > 0))
//                     {
//                         moves.emplace_back(startSquare, targetSquare);
//                     }
//                     break; // Blocked by another piece
//                 }
//             }
//         }
//     }

//     return moves;
// }

std::vector<std::pair<int, int>> MoveGenerator::generateRookMoves(const Board &board, int startSquare)
{
    std::vector<std::pair<int, int>> moves;
    static const int rookOffsets[] = {-8, -1, 1, 8};

    auto [startRow, startCol] = indexToRowCol(startSquare);
    int startPiece = board.getPieceAt(startRow, startCol);

    for (int offset : rookOffsets)
    {
        for (int n = 1; n < 8; ++n)
        {
            int targetSquare = startSquare + n * offset;
            auto [targetRow, targetCol] = indexToRowCol(targetSquare);

            if (isValidSquare(targetSquare))
            {
                int targetPiece = board.getPieceAt(targetRow, targetCol);

                if (targetPiece == 0)
                {
                    // Empty square, valid move
                    moves.emplace_back(startSquare, targetSquare);
                }
                else
                {
                    // Target square contains a piece
                    if ((targetPiece > 0 && startPiece < 0) || (targetPiece < 0 && startPiece > 0))
                    {
                        // Opponent's piece, valid capture
                        moves.emplace_back(startSquare, targetSquare);
                    }
                    break; // Blocked by another piece, stop exploring this direction
                }
            }
            else
            {
                break; // Out of bounds, stop exploring this direction
            }
        }
    }

    return moves;
}

// std::vector<std::pair<int, int>> MoveGenerator::generateQueenMoves(const Board &board, int startSquare)
// {
//     std::vector<std::pair<int, int>> moves;
//     std::vector<std::pair<int, int>> bishopMoves = generateBishopMoves(board, startSquare);
//     std::vector<std::pair<int, int>> rookMoves = generateRookMoves(board, startSquare);

//     moves.insert(moves.end(), bishopMoves.begin(), bishopMoves.end());
//     moves.insert(moves.end(), rookMoves.begin(), rookMoves.end());

//     return moves;
// }

std::vector<std::pair<int, int>> MoveGenerator::generateQueenMoves(const Board &board, int startSquare)
{
    std::vector<std::pair<int, int>> moves;

    // Helper lambda to add moves with capture functionality
    auto addMoves = [this, &board, startSquare, &moves](const std::vector<std::pair<int, int>> &generatedMoves)
    {
        auto [startRow, startCol] = indexToRowCol(startSquare);
        int startPiece = board.getPieceAt(startRow, startCol);

        for (const auto &[fromSquare, toSquare] : generatedMoves)
        {
            auto [targetRow, targetCol] = indexToRowCol(toSquare);
            int targetPiece = board.getPieceAt(targetRow, targetCol);

            if (targetPiece == 0)
            {
                // Empty square, valid move
                moves.emplace_back(fromSquare, toSquare);
            }
            else
            {
                // Target square contains a piece
                if ((targetPiece > 0 && startPiece < 0) || (targetPiece < 0 && startPiece > 0))
                {
                    // Opponent's piece, valid capture
                    moves.emplace_back(fromSquare, toSquare);
                }
                // Stop exploring this direction if a piece is encountered
                break;
            }
        }
    };

    // Generate bishop moves and add with capture functionality
    std::vector<std::pair<int, int>> bishopMoves = generateBishopMoves(board, startSquare);
    addMoves(bishopMoves);

    // Generate rook moves and add with capture functionality
    std::vector<std::pair<int, int>> rookMoves = generateRookMoves(board, startSquare);
    addMoves(rookMoves);

    return moves;
}

// std::vector<std::pair<int, int>> MoveGenerator::generateKingMoves(const Board &board, int startSquare)
// {
//     std::vector<std::pair<int, int>> moves;
//     static const int kingOffsets[] = {-9, -8, -7, -1, 1, 7, 8, 9};

//     for (int offset : kingOffsets)
//     {
//         int targetSquare = startSquare + offset;
//         if (isValidSquare(targetSquare))
//         {
//             int targetPiece = board.getPieceAt(targetSquare / BOARD_SIZE, targetSquare % BOARD_SIZE);
//             if (targetPiece == 0 || (targetPiece > 0 && board.getPieceAt(startSquare / BOARD_SIZE, startSquare % BOARD_SIZE) < 0) || (targetPiece < 0 && board.getPieceAt(startSquare / BOARD_SIZE, startSquare % BOARD_SIZE) > 0))
//             {
//                 moves.emplace_back(startSquare, targetSquare);
//             }
//         }
//     }

//     return moves;
// }

std::vector<std::pair<int, int>> MoveGenerator::generateKingMoves(const Board &board, int startSquare)
{
    std::vector<std::pair<int, int>> moves;
    static const int kingOffsets[] = {-9, -8, -7, -1, 1, 7, 8, 9};

    auto [startRow, startCol] = indexToRowCol(startSquare);
    int startPiece = board.getPieceAt(startRow, startCol);

    for (int offset : kingOffsets)
    {
        int targetSquare = startSquare + offset;

        if (isValidSquare(targetSquare))
        {
            auto [targetRow, targetCol] = indexToRowCol(targetSquare);
            int targetPiece = board.getPieceAt(targetRow, targetCol);

            if (targetPiece == 0 || (targetPiece > 0 && startPiece < 0) || (targetPiece < 0 && startPiece > 0))
            {
                // Empty square or opponent's piece
                moves.emplace_back(startSquare, targetSquare);
            }
        }
    }

    return moves;
}

// Function to check if a square is within board
bool MoveGenerator::isValidSquare(int square)
{
    return square >= 0 && square < 64;
}

// RULE IMPLEMENTATION
// CASTLING

// std::vector<std::pair<int, int>> MoveGenerator::generateCastlingMoves(const Board &board, bool isWhiteTurn)
// {
//     std::vector<std::pair<int, int>> moves;

//     // Assuming the castling rights and checks are tracked in the Board class.
//     if (board.canCastleKingSide())
//     {
//         if (board.isEmptySquare(startSquare + 1) && board.isEmptySquare(startSquare + 2))
//         {
//             if (!isInCheck(board, startSquare) && !isInCheck(board, startSquare + 1) && !isInCheck(board, startSquare + 2))
//             {
//                 moves.emplace_back(startSquare, startSquare + 2); // King-side castling
//             }
//         }
//     }
//     if (board.canCastleQueenSide())
//     {
//         if (board.isEmptySquare(startSquare - 1) && board.isEmptySquare(startSquare - 2) && board.isEmptySquare(startSquare - 3))
//         {
//             if (!isInCheck(board, startSquare) && !isInCheck(board, startSquare - 1) && !isInCheck(board, startSquare - 2))
//             {
//                 moves.emplace_back(startSquare, startSquare - 2); // Queen-side castling
//             }
//         }
//     }

//     return moves;
// }

// Function to generate castling moves
std::vector<std::pair<int, int>> MoveGenerator::generateCastlingMoves(const Board &board, bool isWhiteTurn)
{
    std::vector<std::pair<int, int>> moves;

    if (isWhiteTurn)
    {
        if (board.canCastleKingSide(true)) // Pass true for white
        {
            if (board.isEmptySquare(0, 5) && board.isEmptySquare(0, 6))
            {
                if (!board.isSquareUnderAttack(0, 4, isWhiteTurn) && !board.isSquareUnderAttack(0, 5, isWhiteTurn) && !board.isSquareUnderAttack(0, 6, isWhiteTurn))
                {
                    moves.emplace_back(4, 6); // King-side castling for white
                }
            }
        }
        if (board.canCastleQueenSide(true)) // Pass true for white
        {
            if (board.isEmptySquare(0, 1) && board.isEmptySquare(0, 2) && board.isEmptySquare(0, 3))
            {
                if (!board.isSquareUnderAttack(0, 4, isWhiteTurn) && !board.isSquareUnderAttack(0, 3, isWhiteTurn) && !board.isSquareUnderAttack(0, 2, isWhiteTurn))
                {
                    moves.emplace_back(4, 2); // Queen-side castling for white
                }
            }
        }
    }
    else
    {
        if (board.canCastleKingSide(false)) // Pass false for black
        {
            if (board.isEmptySquare(7, 5) && board.isEmptySquare(7, 6))
            {
                if (!board.isSquareUnderAttack(7, 4, isWhiteTurn) && !board.isSquareUnderAttack(7, 5, isWhiteTurn) && !board.isSquareUnderAttack(7, 6, isWhiteTurn))
                {
                    moves.emplace_back(60, 62); // King-side castling for black
                }
            }
        }
        if (board.canCastleQueenSide(false)) // Pass false for black
        {
            if (board.isEmptySquare(7, 1) && board.isEmptySquare(7, 2) && board.isEmptySquare(7, 3))
            {
                if (!board.isSquareUnderAttack(7, 4, isWhiteTurn) && !board.isSquareUnderAttack(7, 3, isWhiteTurn) && !board.isSquareUnderAttack(7, 2, isWhiteTurn))
                {
                    moves.emplace_back(60, 58); // Queen-side castling for black
                }
            }
        }
    }

    return moves;
}

// CHECK AND CHECKMATE
bool MoveGenerator::isInCheck(const Board &board, int kingSquare)
{
    std::vector<std::pair<int, int>> opponentMoves = generateMoves(board, -board.getPieceAt(kingSquare / BOARD_SIZE, kingSquare % BOARD_SIZE));

    for (const auto &move : opponentMoves)
    {
        if (move.second == kingSquare)
        {
            return true;
        }
    }
    return false;
}

bool MoveGenerator::isCheckmate(const Board &board, int kingSquare)
{
    if (!isInCheck(board, kingSquare))
    {
        return false;
    }

    std::vector<std::pair<int, int>> kingMoves = generateKingMoves(board, kingSquare);
    for (const auto &move : kingMoves)
    {
        Board newBoard = board;
        newBoard.makeMove(move.first, move.second);
        if (!isInCheck(newBoard, move.second))
        {
            return false;
        }
    }

    return true;
}
