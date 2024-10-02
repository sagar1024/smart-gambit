#include <iostream>

#include "board.h"
#include "evaluation.h"

const int Evaluation::pawnTable[64] = {
    0, 0, 0, 0, 0, 0, 0, 0,
    5, 10, 10, -20, -20, 10, 10, 5,
    5, -5, -10, 0, 0, -10, -5, 5,
    0, 0, 0, 20, 20, 0, 0, 0,
    5, 5, 10, 25, 25, 10, 5, 5,
    10, 10, 20, 30, 30, 20, 10, 10,
    50, 50, 50, 50, 50, 50, 50, 50,
    0, 0, 0, 0, 0, 0, 0, 0
};

const int Evaluation::blackPawnTable[64] = {
    0, 0, 0, 0, 0, 0, 0, 0,
    50, 50, 50, 50, 50, 50, 50, 50,
    10, 10, 20, 30, 30, 20, 10, 10,
    5, 5, 10, 25, 25, 10, 5, 5,
    0, 0, 0, 20, 20, 0, 0, 0,
    5, -5, -10, 0, 0, -10, -5, 5,
    5, 10, 10, -20, -20, 10, 10, 5,
    0, 0, 0, 0, 0, 0, 0, 0
};

const int Evaluation::knightTable[64] = {
    -50, -40, -30, -30, -30, -30, -40, -50,
    -40, -20, 0, 0, 0, 0, -20, -40,
    -30, 0, 10, 15, 15, 10, 0, -30,
    -30, 5, 15, 20, 20, 15, 5, -30,
    -30, 0, 15, 20, 20, 15, 0, -30,
    -30, 5, 10, 15, 15, 10, 5, -30,
    -40, -20, 0, 5, 5, 0, -20, -40,
    -50, -40, -30, -30, -30, -30, -40, -50
};

const int Evaluation::bishopTable[64] = {
    -20, -10, -10, -10, -10, -10, -10, -20,
    -10, 0, 0, 0, 0, 0, 0, -10,
    -10, 0, 5, 10, 10, 5, 0, -10,
    -10, 5, 5, 10, 10, 5, 5, -10,
    -10, 0, 10, 10, 10, 10, 0, -10,
    -10, 10, 10, 10, 10, 10, 10, -10,
    -10, 5, 0, 0, 0, 0, 5, -10,
    -20, -10, -10, -10, -10, -10, -10, -20
};

const int Evaluation::rookTable[64] = {
    0, 0, 0, 0, 0, 0, 0, 0,
    5, 10, 10, 10, 10, 10, 10, 5,
    -5, 0, 0, 0, 0, 0, 0, -5,
    -5, 0, 0, 0, 0, 0, 0, -5,
    -5, 0, 0, 0, 0, 0, 0, -5,
    -5, 0, 0, 0, 0, 0, 0, -5,
    -5, 0, 0, 0, 0, 0, 0, -5,
    0, 0, 0, 5, 5, 0, 0, 0
};

const int Evaluation::queenTable[64] = {
    -20, -10, -10, -5, -5, -10, -10, -20,
    -10, 0, 0, 0, 0, 0, 0, -10,
    -10, 0, 5, 5, 5, 5, 0, -10,
    -5, 0, 5, 5, 5, 5, 0, -5,
    0, 0, 5, 5, 5, 5, 0, -5,
    -10, 5, 5, 5, 5, 5, 0, -10,
    -10, 0, 5, 0, 0, 0, 0, -10,
    -20, -10, -10, -5, -5, -10, -10, -20
};

const int Evaluation::kingTable[64] = {
    -30, -40, -40, -50, -50, -40, -40, -30,
    -30, -40, -40, -50, -50, -40, -40, -30,
    -30, -40, -40, -50, -50, -40, -40, -30,
    -30, -40, -40, -50, -50, -40, -40, -30,
    -20, -30, -30, -40, -40, -30, -30, -20,
    -10, -20, -20, -20, -20, -20, -20, -10,
    20, 20, 0, 0, 0, 0, 20, 20,
    20, 30, 10, 0, 0, 10, 30, 20
};

//MAIN Evaluation function
int Evaluation::evaluate(const Board &board)
{
    int materialScore = evaluateMaterial(board);
    int positionScore = evaluatePosition(board);

    return materialScore + positionScore;
}

int Evaluation::evaluateMaterial(const Board &board)
{
    int score = 0;

    for (int square = 0; square < 64; ++square)
    {
        int piece = board.getPieceAt(square / BOARD_SIZE, square % BOARD_SIZE);
        switch (std::abs(piece))
        {
        case 1: //Pawn
            score += (piece > 0) ? 100 : -100;
            break;
        case 2: //Knight
            score += (piece > 0) ? 320 : -320;
            break;
        case 3: //Bishop
            score += (piece > 0) ? 330 : -330;
            break;
        case 4: //Rook
            score += (piece > 0) ? 500 : -500;
            break;
        case 5: //Queen
            score += (piece > 0) ? 900 : -900;
            break;
        case 6: //King doesn't contribute to material score but has positional value
            break;
        }
    }

    return score;
}

int Evaluation::evaluatePosition(const Board &board)
{
    int score = 0;

    for (int square = 0; square < 64; ++square)
    {
        int piece = board.getPieceAt(square / BOARD_SIZE, square % BOARD_SIZE);
        switch (std::abs(piece))
        {
        case 1: //Pawn
            score += (piece > 0) ? pawnTable[square] : -pawnTable[63 - square];
            break;
        case 2: //Knight
            score += (piece > 0) ? knightTable[square] : -knightTable[63 - square];
            break;
        case 3: //Bishop
            score += (piece > 0) ? bishopTable[square] : -bishopTable[63 - square];
            break;
        case 4: //Rook
            score += (piece > 0) ? rookTable[square] : -rookTable[63 - square];
            break;
        case 5: //Queen
            score += (piece > 0) ? queenTable[square] : -queenTable[63 - square];
            break;
        case 6: //King
            score += (piece > 0) ? kingTable[square] : -kingTable[63 - square];
            break;
        }
    }

    return score;
}
