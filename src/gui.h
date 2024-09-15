#ifndef GUI_H
#define GUI_H

#include "board.h"
#include "movegen.h"
#include "search.h"
#include "move.h"

#include <iostream>
#include <vector>

class GUI
{
private:
    Board board;
    MoveGenerator moveGen;
    Search search;
    std::vector<std::pair<int, int>> validMoves;
    int selectedPiece;
    bool isWhiteTurn;
    int kingSquare;

public:
    GUI();
    void selectMode();
    void playMode();
    void analyzeMode();
    void handleMouseClick(int x, int y);
    void makeEngineMove();
    bool isGameOver();
    void showEndGameMessage();
    void resetGame();
    void loadPGN();
};

#endif
