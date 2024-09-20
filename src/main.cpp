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

// Alternate soln -

// #include <iostream>
// #include "gui.h"

// void showMainMenu()
// {
//     std::cout << "=====================" << std::endl;
//     std::cout << "     SmartGambit     " << std::endl;
//     std::cout << "=====================" << std::endl;
//     std::cout << "1. Play a game" << std::endl;
//     std::cout << "2. Analyze a position" << std::endl;
//     std::cout << "3. Exit" << std::endl;
//     std::cout << "Enter your choice: ";
// }

// int main()
// {
//     GUI gui; // Create GUI instance to manage the game

//     bool exit = false;
//     while (!exit)
//     {
//         showMainMenu();

//         int choice;
//         std::cin >> choice;

//         switch (choice)
//         {
//         case 1:
//             gui.playMode(); // Start play mode
//             break;
//         case 2:
//             gui.analyzeMode(); // Start analysis mode
//             break;
//         case 3:
//             exit = true; // Exit the program
//             std::cout << "Exiting the chess engine. Goodbye!" << std::endl;
//             break;
//         default:
//             std::cout << "Invalid choice. Please try again." << std::endl;
//         }
//     }

//     return 0;
// }

// Alternate code -

// #include <iostream>
// #include "gui.h"

// int main()
// {
//     //Creating an instance of the GUI
//     GUI gui;

//     //Running the GUI main loop
//     gui.run();

//     return 0;
// }

// Alternate code -

#include <SFML/Graphics.hpp>
#include "gui.h"
#include <iostream>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 800), "SmartGambit Chess Engine");

    // Load the logo texture
    sf::Texture logoTexture;
    if (!logoTexture.loadFromFile("texture/logo.png"))
    {
        std::cerr << "Error loading logo image" << std::endl;
        return -1;
    }

    // Create sprite for the logo
    sf::Sprite logoSprite;
    logoSprite.setTexture(logoTexture);
    logoSprite.setPosition(150, 10); // Position it at the top

    // Load font
    sf::Font font;
    if (!font.loadFromFile("texture/font.ttf"))
    {
        std::cerr << "Error loading font" << std::endl;
        return -1;
    }

    // Create the GUI object
    GUI gui(window);

    while (window.isOpen())
    {
        // Display the main menu (Play, Analyze, Exit)
        window.clear();

        // Draw the logo at the top
        window.draw(logoSprite);

        // Create text for Play, Analyze, and Exit options
        sf::Text playText("1. Play", font, 40);
        sf::Text analyzeText("2. Analyze", font, 40);
        sf::Text exitText("3. Exit", font, 40);

        playText.setPosition(300, 250);
        analyzeText.setPosition(300, 350);
        exitText.setPosition(300, 450);

        window.draw(playText);
        window.draw(analyzeText);
        window.draw(exitText);

        window.display();

        // Handle user input
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                    if (playText.getGlobalBounds().contains(mousePos.x, mousePos.y))
                    {
                        // User selects Play
                        std::cout << "Play selected" << std::endl;

                        // Ask user whether they want to play as white or black
                        bool validChoice = false;
                        bool isWhite = true;
                        while (!validChoice)
                        {
                            window.clear();
                            window.draw(logoSprite);
                            sf::Text whiteText("Play as White", font, 30);
                            sf::Text blackText("Play as Black", font, 30);

                            whiteText.setPosition(300, 250);
                            blackText.setPosition(300, 350);

                            window.draw(whiteText);
                            window.draw(blackText);
                            window.display();

                            sf::Event choiceEvent;
                            while (window.pollEvent(choiceEvent))
                            {
                                if (choiceEvent.type == sf::Event::Closed)
                                {
                                    window.close();
                                    return 0;
                                }
                                if (choiceEvent.type == sf::Event::MouseButtonPressed)
                                {
                                    if (choiceEvent.mouseButton.button == sf::Mouse::Left)
                                    {
                                        if (whiteText.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
                                        {
                                            isWhite = true;
                                            validChoice = true;
                                        }
                                        else if (blackText.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
                                        {
                                            isWhite = false;
                                            validChoice = true;
                                        }
                                    }
                                }
                            }
                        }

                        // Call play mode with the chosen color
                        gui.playMode(isWhite);
                    }
                    else if (analyzeText.getGlobalBounds().contains(mousePos.x, mousePos.y))
                    {
                        // User selects Analyze
                        std::cout << "Analyze selected" << std::endl;

                        // Ask user whether they want to import PGN or start with the initial board setup
                        bool validChoice = false;
                        bool importPGN = false;
                        while (!validChoice)
                        {
                            window.clear();
                            window.draw(logoSprite);
                            sf::Text pgnText("Import PGN", font, 30);
                            sf::Text initialText("Initial Board Setup", font, 30);

                            pgnText.setPosition(300, 250);
                            initialText.setPosition(300, 350);

                            window.draw(pgnText);
                            window.draw(initialText);
                            window.display();

                            sf::Event choiceEvent;
                            while (window.pollEvent(choiceEvent))
                            {
                                if (choiceEvent.type == sf::Event::Closed)
                                {
                                    window.close();
                                    return 0;
                                }
                                if (choiceEvent.type == sf::Event::MouseButtonPressed)
                                {
                                    if (choiceEvent.mouseButton.button == sf::Mouse::Left)
                                    {
                                        if (pgnText.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
                                        {
                                            importPGN = true;
                                            validChoice = true;
                                        }
                                        else if (initialText.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
                                        {
                                            importPGN = false;
                                            validChoice = true;
                                        }
                                    }
                                }
                            }
                        }

                        // Call analyze mode with the chosen option
                        gui.analyzeMode();
                    }
                    else if (exitText.getGlobalBounds().contains(mousePos.x, mousePos.y))
                    {
                        // User selects Exit
                        window.close();
                    }
                }
            }
        }
    }

    return 0;
}
