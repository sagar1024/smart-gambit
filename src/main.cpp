// #include <SFML/Graphics.hpp>
// #include "board.h"
// #include "movegen.h"
// #include "search.h"
// #include "evaluation.h"
// #include "gui.h"

// #include <iostream>
// #include <bits/stdc++.h>

// int main()
// {
//     // Initialize the game
//     Board board;
//     MoveGenerator moveGen;
//     Search searchEngine(5); // Set search depth, adjust as necessary
//     GUI gui;

//     // Create the main window
//     sf::RenderWindow window(sf::VideoMode(800, 800), "SmartGambit Chess Engine");

//     bool isWhiteTurn = true;
//     bool gameEnded = false;

//     while (window.isOpen())
//     {
//         sf::Event event;
//         while (window.pollEvent(event))
//         {
//             if (event.type == sf::Event::Closed)
//                 window.close();

//             // Handle GUI events (clicks, moves, etc.)
//             if (!gameEnded)
//             {
//                 gui.handleEvent(event, board, isWhiteTurn);

//                 if (gui.isMoveMade())
//                 {
//                     // Check if the move is valid
//                     if (moveGen.isMoveLegal(board, gui.getLastMove(), isWhiteTurn))
//                     {
//                         board.makeMove(gui.getLastMove().first, gui.getLastMove().second);
//                         isWhiteTurn = !isWhiteTurn;

//                         // Check for game end conditions (checkmate, stalemate)
//                         if (moveGen.isCheckmate(board, isWhiteTurn))
//                         {
//                             gameEnded = true;
//                             gui.displayEndGameMessage(isWhiteTurn ? "Black wins!" : "White wins!");
//                         }
//                         else if (moveGen.isStalemate(board, isWhiteTurn))
//                         {
//                             gameEnded = true;
//                             gui.displayEndGameMessage("Stalemate!");
//                         }
//                     }
//                 }

//                 // If it's the engine's turn, search for the best move
//                 if (!isWhiteTurn && !gameEnded)
//                 {
//                     std::pair<int, int> bestMove = searchEngine.searchBestMove(board, 5, isWhiteTurn);
//                     board.makeMove(bestMove.first, bestMove.second);
//                     isWhiteTurn = !isWhiteTurn;

//                     // Check for game end conditions
//                     if (moveGen.isCheckmate(board, isWhiteTurn))
//                     {
//                         gameEnded = true;
//                         gui.displayEndGameMessage(isWhiteTurn ? "Black wins!" : "White wins!");
//                     }
//                     else if (moveGen.isStalemate(board, isWhiteTurn))
//                     {
//                         gameEnded = true;
//                         gui.displayEndGameMessage("Stalemate!");
//                     }
//                 }
//             }

//             // If the game has ended, ask the player if they want to play again
//             if (gameEnded)
//             {
//                 if (gui.askForReplay())
//                 {
//                     board.reset();
//                     isWhiteTurn = true;
//                     gameEnded = false;
//                 }
//                 else
//                 {
//                     window.close();
//                 }
//             }
//         }

//         // Clear the window
//         window.clear();

//         // Draw the current state of the board and pieces
//         gui.render(window, board);

//         // Display the window
//         window.display();
//     }

//     return 0;
// }

#include <iostream>
#include <bits/stdc++.h>

#include "gui.h"

void showMainMenu()
{
    std::cout << "====================" << std::endl;
    std::cout << "  Chess Engine Menu " << std::endl;
    std::cout << "====================" << std::endl;
    std::cout << "1. Play a game" << std::endl;
    std::cout << "2. Analyze a position" << std::endl;
    std::cout << "3. Exit" << std::endl;
    std::cout << "Enter your choice: ";
}

int main()
{
    GUI gui; // Create GUI instance to manage the game

    bool exit = false;
    while (!exit)
    {
        showMainMenu();

        int choice;
        std::cin >> choice;

        switch (choice)
        {
        case 1:
            gui.playMode(); // Start play mode
            break;
        case 2:
            gui.analyzeMode(); // Start analysis mode
            break;
        case 3:
            exit = true; // Exit the program
            std::cout << "Exiting the chess engine. Goodbye!" << std::endl;
            break;
        default:
            std::cout << "Invalid choice. Please try again." << std::endl;
        }
    }

    return 0;
}
