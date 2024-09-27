#include "board.h"
#include "evaluation.h"
#include "gui.h"
#include "move.h"
#include "movegen.h"
#include "search.h"

#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
    sf::RenderWindow window(sf::VideoMode(1000,800), "SmartGambit Chess Engine");

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
    logoSprite.setPosition(300, 10); // Position it at the top

    // Scale down the piece sprite to fit your tile size
    logoSprite.setScale(0.55f, 0.55f);

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
        sf::Text playText("1. Play", font, 30);
        sf::Text analyzeText("2. Analyze", font, 30);
        sf::Text exitText("3. Exit", font, 30);

        playText.setPosition(380, 400);
        analyzeText.setPosition(380, 450);
        exitText.setPosition(380, 500);

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

                            whiteText.setPosition(380, 400);
                            blackText.setPosition(380, 450);

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

                            pgnText.setPosition(380, 400);
                            initialText.setPosition(380, 450);

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
