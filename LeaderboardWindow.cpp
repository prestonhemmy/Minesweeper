/**
* COP3503 - Project 3
* @author Preston Hemmy
* @version 1.0
*/

#include <fstream>
#include <sstream>
#include <iomanip>
#include <vector>
#include "LeaderboardWindow.h"

LeaderboardWindow::LeaderboardWindow(unsigned int width, unsigned int height) : width(width), height(height) {
    window.create(sf::VideoMode(width, height), "Leaderboard", sf::Style::Close);
    loadFont();
    loadLeaderboardData();
}

void LeaderboardWindow::run(bool player_won, const std::string& username, const std::string& time) {
    if (player_won) {
        updateLeaderboard(username, time);
//        saveLeaderboardData();
    }
    loadLeaderboardData();

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            window.clear(sf::Color::Blue);

            window.draw(leaderboard_title);
            window.draw(leaderboard_entries);

            window.display();
        }
    }
}

void LeaderboardWindow::loadFont() {
    font.loadFromFile("files/font.ttf");
}

void LeaderboardWindow::loadLeaderboardData() {
    std::ifstream file("files/leaderboard.txt");
    std::string line;
    std::vector<std::pair<std::string, std::string>> entries;

    while (std::getline(file, line)) {
        std::string name;
        std::string time;
        std::istringstream iss(line);
        std::getline(iss, time, ',');
        std::getline(iss, name);
        entries.emplace_back(time, name);
    }

    std::sort(entries.begin(), entries.end());

    std::stringstream ss;

    int rank = 1;
    for (const auto& entry : entries) {
        ss << std::setw(4) << rank << ".  " << std::setw(10) << entry.first << "  " << entry.second << "\n\n";
        rank++;
    }

    setText(leaderboard_title, 20, sf::Color::White, true);
    leaderboard_title.setString("LEADERBOARD");
    leaderboard_title.setPosition(width / 2.f - leaderboard_title.getLocalBounds().width / 2.f, 20);

    setText(leaderboard_entries, 18, sf::Color::White, false);
    leaderboard_entries.setString(ss.str());
    leaderboard_entries.setPosition(20, 60);
}

void LeaderboardWindow::updateLeaderboard(std::string username, std::string time) {
    std::vector<std::pair<std::string, std::string>> entries;
    entries.emplace_back(time, username);

    std::ifstream file("leaderboard.txt");
    std::string line;
    while (std::getline(file, line)) {
        std::string name;
        std::string t;
        std::istringstream iss(line);
        std::getline(iss, t, ',');
        std::getline(iss, name);
        entries.emplace_back(t, name);
    }

    std::sort(entries.begin(), entries.end());

    std::ofstream outputFile("leaderboard.txt");
    for (size_t i = 0; i < entries.size() && i < 5; ++i) {
        outputFile << entries[i].first << "," << entries[i].second << "\n";
    }
}

void LeaderboardWindow::saveLeaderboardData() {
    std::ofstream file("leaderboard.txt");
    std::string leaderboardText = leaderboard_entries.getString();
    std::istringstream iss(leaderboardText);
    std::string line;
    while (std::getline(iss, line)) {
        if (line.empty()) {
            continue;
        }

        auto pos = line.find('\t');
        if (pos != std::string::npos) {
            line = line.substr(pos + 1);
            pos = line.find('\t');
            if (pos != std::string::npos) {
                std::string time = line.substr(0, pos);
                std::string name = line.substr(pos + 1);
                if (name.back() == '*') {
                    name.pop_back();
                    name.pop_back();
                }

                file << time << "," << name << std::endl;
            }
        }
    }
}

void LeaderboardWindow::setText(sf::Text &text, unsigned int char_size, sf::Color color, bool underline) {
    text.setFont(font);
    text.setCharacterSize(char_size);
    text.setFillColor(color);
    text.setStyle(sf::Text::Bold);
    if (underline) {
        text.setStyle(text.getStyle() | sf::Text::Underlined);
    }
}