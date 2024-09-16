#ifndef SEARCH_H
#define SEARCH_H

#include <vector>
#include <utility>
#include "board.h"
#include "move.h"
#include "movegen.h"

class Search
{
public:
    // Constructor with maximum depth parameter
    Search(int maxDepth = 3);

    // Function to find the best move
    //std::pair<int, int> searchBestMove(Board &board, int depth, bool isWhiteTurn);
    Move searchBestMove(Board &board, int depth, bool isWhiteTurn);

    MoveGenerator moveGen;

private:
    // Function to perform the minimax search with alpha-beta pruning
    int minimax(Board &board, int depth, int alpha, int beta, bool isMaximizingPlayer);

    // Maximum depth for the search
    int maxDepth;

    // Helper function to evaluate board, assuming this is implemented elsewhere
    int evaluateBoard(const Board &board, bool isWhiteTurn);

    // Function to order moves (e.g., to prioritize captures or checks)
    std::vector<std::pair<int, int>> orderMoves(const std::vector<std::pair<int, int>> &moves, const Board &board, bool isWhiteTurn);
};

#endif // SEARCH_H
