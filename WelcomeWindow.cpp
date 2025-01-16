/**
* COP3503 - Lab 5
* @author Preston Hemmy
* @version 1.0
*/

#include "WelcomeWindow.h"
#include "Game.h"
#include <iostream>
#include <fstream>

WelcomeWindow::WelcomeWindow() {
    loadConfig();
    createWindow();
    loadFont();
    setTitleAndPrompt();
    setUsername();
}

WelcomeWindow::~WelcomeWindow() {
    // Todo. (need?)
}

Game* WelcomeWindow::run() {
    while(window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::TextEntered) {
                if (((event.text.unicode >= 'A' && event.text.unicode <= 'Z') || (event.text.unicode >= 'a' && event.text.unicode <= 'z')) && username.getString().getSize() < 10) {
                    char entered = static_cast<char>(event.text.unicode);

                    if (username.getString().isEmpty()) {
                        entered = std::toupper(entered);
                    } else {
                        entered = std::tolower(entered);
                    }

                    username.setString(username.getString() + entered);
                } else if (event.text.unicode == '\b') {
                    username.setString(username.getString().substring(0, username.getString().getSize() - 1));
                }

                setText(username, width / 2, height / 2 - 45);

                sf::FloatRect usernameRect = username.getLocalBounds();
                cursor.setPosition(username.getPosition().x + usernameRect.width / 2.0f + 5, username.getPosition().y);
            } else if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Return && !username.getString().isEmpty()) {
                    game = new Game(width, height, mine_count, username.getString());
                    window.close();
                    return game;
                }
            }
        }

        window.clear(sf::Color::Blue);

        window.draw(title);
        window.draw(prompt);
        window.draw(username);
        window.draw(cursor);

        window.display();
    }

    return nullptr;
}

void WelcomeWindow::loadConfig() {
    std::ifstream file("files/config.cfg");
    if (file.is_open()) {
        std::string line;
        unsigned int lineNumber = 1;

        while (getline(file, line)) {
            if (lineNumber == 1) {
                width = stoul(line) * 32;
            } else if (lineNumber == 2) {
                height = stoul(line) * 32 + 100;
            } else if (lineNumber == 3) {
                mine_count = stoul(line);       // Added to read mine count
            }

            lineNumber++;
        }

        file.close();
    } else {
        std::cerr << "Could not open config.cfg file." << std::endl;
    }
}

void WelcomeWindow::createWindow() {
    window.create(sf::VideoMode(width, height), "Minesweeper", sf::Style::Close);
}

void WelcomeWindow::loadFont() {
    if (!font.loadFromFile("files/font.ttf")) {
        std::cerr << "Could not open font.ttf file." << std::endl;
    }
}

void WelcomeWindow::setText(sf::Text &text, float x, float y) {
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    text.setPosition(sf::Vector2f (x, y));
}

void WelcomeWindow::setTitleAndPrompt() {
    title.setFont(font);
    title.setCharacterSize(24);
    title.setFillColor(sf::Color::White);
    title.setStyle(sf::Text::Bold | sf::Text::Underlined);
    title.setString("MINESWEEPER!");
    setText(title, width / 2, height / 2 - 150);

    prompt.setFont(font);
    prompt.setCharacterSize(20);
    prompt.setFillColor(sf::Color::White);
    prompt.setStyle(sf::Text::Bold);
    prompt.setString("Enter your name:");
    setText(prompt, width / 2, height/ 2 - 75);
}

void WelcomeWindow::setUsername() {
    username.setFont(font);
    username.setCharacterSize(18);
    username.setFillColor(sf::Color::Yellow);
    username.setStyle(sf::Text::Bold);
    username.setString("");
    setText(username, width / 2, height / 2 - 45);

    cursor.setFont(font);
    cursor.setCharacterSize(18);
    cursor.setFillColor(sf::Color::Yellow);
    cursor.setStyle(sf::Text::Bold);
    cursor.setString("|");
    setText(cursor, width / 2 + 5, height / 2 - 45);
}
