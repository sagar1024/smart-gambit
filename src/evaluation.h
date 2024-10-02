#ifndef EVALUATION_H
#define EVALUATION_H

#include "board.h"

class Evaluation
{
public:
    //Function to evaluate the board and return an evaluation score
    int evaluate(const Board &board);

private:
    int evaluateMaterial(const Board &board);
    int evaluatePosition(const Board &board);

    //Positional bonus tables for each piece
    static const int pawnTable[64];
    static const int blackPawnTable[64];
    static const int knightTable[64];
    static const int bishopTable[64];
    static const int rookTable[64];
    static const int queenTable[64];
    static const int kingTable[64];
};

#endif //EVALUATION_H