/**
* COP3503 - Project 3
* @author Preston Hemmy
* @version 1.0
*/

#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

class LeaderboardWindow {
    unsigned int width;
    unsigned int height;
    sf::RenderWindow window;
    sf::Font font;
    sf::Text leaderboard_title, leaderboard_entries;

public:
    LeaderboardWindow(unsigned int width, unsigned int height);

    void run(bool player_won = false, const std::string& username = "", const std::string& time = "");

private:
    void loadFont();

    void loadLeaderboardData();

    void updateLeaderboard(std::string username, std::string time);

    void saveLeaderboardData();

    void setText(sf::Text& text, unsigned int char_size, sf::Color color, bool underline);
};
