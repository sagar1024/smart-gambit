#include "move.h"
#include "movegen.h"
#include "search.h"
#include "evaluation.h"

#include <iostream>

//Constructor
Search::Search(int maxDepth) : maxDepth(maxDepth) {}

//Function to calculate the best move
Move Search::searchBestMove(Board &board, int depth, bool isWhiteTurn)
{
    int bestScore = isWhiteTurn ? -10000 : 10000; //Initial best score
    Move bestMove(-1, -1); //Initialize the best move as an invalid move

    //Generate possible moves (std::pair<int, int>)
    std::vector<std::pair<int, int>> possibleMovePairs = moveGen.generateMoves(board, isWhiteTurn);

    //Convert std::pair<int, int> to Move
    std::vector<Move> possibleMoves;
    for (const auto &movePair : possibleMovePairs)
    {
        possibleMoves.push_back(Move(movePair.first, movePair.second));
    }

    for (const Move &move : possibleMoves)
    {
        Board newBoard = board; //Make a copy of the board
        newBoard.makeMove(move.from, move.to); //Apply the move on the new board

        //Perform the minimax algorithm with alpha-beta pruning
        int score = minimax(newBoard, depth - 1, -10000, 10000, !isWhiteTurn);

        //If it's White's turn, maximize the score, otherwise minimize it
        if ((isWhiteTurn && score > bestScore) || (!isWhiteTurn && score < bestScore))
        {
            bestScore = score;
            bestMove = move; //Update the best move
        }
    }

    return bestMove;
}

//Minimax search with alpha-beta pruning
int Search::minimax(Board &board, int depth, int alpha, int beta, bool isWhiteTurn)
{
    if (depth == 0)
    {
        return evaluateBoard(board, isWhiteTurn);
    }

    MoveGenerator moveGen;
    std::vector<std::pair<int, int>> possibleMoves = moveGen.generateMoves(board, isWhiteTurn);

    if (isWhiteTurn)
    {
        int maxEval = -10000;
        for (const auto &move : possibleMoves)
        {
            Board newBoard = board;
            newBoard.makeMove(move.first, move.second);
            int eval = minimax(newBoard, depth - 1, alpha, beta, false);
            maxEval = std::max(maxEval, eval);
            alpha = std::max(alpha, eval);
            if (beta <= alpha)
            {
                break;
            }
        }
        return maxEval;
    }
    else
    {
        int minEval = 10000;
        for (const auto &move : possibleMoves)
        {
            Board newBoard = board;
            newBoard.makeMove(move.first, move.second);
            int eval = minimax(newBoard, depth - 1, alpha, beta, true);
            minEval = std::min(minEval, eval);
            beta = std::min(beta, eval);
            if (beta <= alpha)
            {
                break;
            }
        }

        return minEval;
    }
}

//Basic evaluation function for board scoring
int Search::evaluateBoard(const Board &board, bool isWhiteTurn)
{
    //Simplified evaluation: could be based on material, piece positions, etc.
    int score = 0;

    for (int r = 0; r < BOARD_SIZE; ++r)
    {
        for (int c = 0; c < BOARD_SIZE; ++c)
        {
            Piece piece = board.getPieceAt(r, c);
            score += piece; //Modify this to reflect proper piece values and positions
        }
    }

    return score;
}

//Function to order moves (e.g., to prioritize captures or checks)
std::vector<std::pair<int, int>> Search::orderMoves(const std::vector<std::pair<int, int>> &moves, const Board &board, bool isWhiteTurn)
{
    // Currently, no specific move ordering is implemented
    // In future, you can add logic to prioritize certain moves, like captures or checks

    return moves; // Return the moves without any modification
}
