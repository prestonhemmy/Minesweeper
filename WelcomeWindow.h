/**
* COP3503 - Project 3
* @author Preston Hemmy
* @version 1.0
*/

#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "Game.h"

class WelcomeWindow {
    unsigned int width;
    unsigned int height;
    unsigned int mine_count;
    sf::RenderWindow window;
    sf::Font font;
    sf::Text title, prompt, username, cursor;
    Game* game;

public:
    WelcomeWindow();

    ~WelcomeWindow();

    Game* run();

private:
    void loadConfig();

    void createWindow();

    void loadFont();

    void setText(sf::Text& text, float x, float y);

    void setTitleAndPrompt();

    void setUsername();
};