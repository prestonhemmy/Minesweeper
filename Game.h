/**
* COP3503 - Project 3
* @author Preston Hemmy
* @version 1.0
*/

#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "Board.h"
#include "TextureManager.h"

class Game {
    unsigned int width, height, mine_count;
    std::string username;
    sf::RenderWindow window;
    Board board;
    sf::Sprite face_button, debug_button, pause_button, leaderboard_button;
    sf::Sprite remaining_mines_counter;
    sf::Text timer_text;
    sf::Font font;
    bool game_over = false, debug_mode, paused = false, game_won = false;
    int remaining_mines;
    sf::Clock clock;

public:
    Game(unsigned int width, unsigned int height, unsigned int mine_count, const std::string& username);

    void run();

private:

    void loadTextures();

    void setButtonPositions();

    void handleDebugButtonClick();

    void resetGame();

    void handlePauseButtonClick();

    void handleLeaderboardButtonClick();

    void handleWin();

    bool checkWinCondition();
};