/**
* COP3503 - Project 3
* @author Preston Hemmy
* @version 1.0
*/

#include <chrono>
#include <sstream>
#include <iomanip>

#include <iostream>
#include "Game.h"
#include "LeaderboardWindow.h"

Game::Game(unsigned int width, unsigned int height, unsigned int mine_count, const std::string& username) : width(width),
height(height), mine_count(mine_count), username(username), board(width / 32, height / 32 - 3, mine_count),
remaining_mines(mine_count) {
    window.create(sf::VideoMode(width, height), "Minesweeper", sf::Style::Close);
    loadTextures();
    setButtonPositions();
    font.loadFromFile("files/font.ttf");
//    timer_text.setFont(font);
}

void Game::run() {
    board.setMines();
    board.updateAdjacentMineCounts();
    clock.restart();

    while (window.isOpen()) {
        sf::Event event;
//        updateRemainingMinesCounter();
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
                    if (debug_button.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
                        handleDebugButtonClick();
                    }
                    if (face_button.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
                        resetGame();
                    }
                    if (pause_button.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
                        handlePauseButtonClick();
                    } else if (leaderboard_button.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
                        handleLeaderboardButtonClick();
                    }
                    unsigned int row = mousePosition.y / 32;
                    unsigned int col = mousePosition.x / 32;
                    if (row < board.getHeight() && col < board.getWidth()) {
                        Tile& tile = board.getTile(row, col);
                        if (!tile.isFlagged() && !tile.isRevealed() && !game_over) {
                            if (tile.hasMine()) {
                                for (unsigned int i = 0; i < board.getHeight(); i++) {
                                    for (unsigned int j = 0; j < board.getWidth(); j++) {
                                        Tile& t = board.getTile(i, j);
                                        if (t.hasMine()) {
                                            t.reveal();
                                        }
                                    }
                                }
                                game_over = true;
                            } else {
                                board.revealAdjacentTiles(row, col);
                            }
                        }
                    }
                } else if (event.mouseButton.button == sf::Mouse::Right && !game_over) {
                    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
                    unsigned int row = mousePosition.y / 32;
                    unsigned int col = mousePosition.x / 32;
                    if (row < board.getHeight() && col < board.getWidth()) {
                        Tile& tile = board.getTile(row, col);
                        if (!tile.isRevealed()) {
                            tile.toggleFlag();
//                            remaining_mines += tile.isFlagged() ? -1 : 1;
                        }
                    }
                }
            }
            if (game_over) {
                TextureManager::getInstance().loadTexture("files/images/face_lose.png");
                face_button.setTexture(TextureManager::getInstance().getTexture("files/images/face_lose.png"));
            }

            if (!game_over && !game_won && checkWinCondition()) {
                handleWin();
            }
        }

        window.clear(sf::Color::White);
        board.draw(window);
        window.draw(face_button);
        window.draw(debug_button);
        window.draw(pause_button);
        window.draw(leaderboard_button);
        window.draw(remaining_mines_counter);
        window.draw(timer_text);
        window.display();
    }
}

void Game::loadTextures() {
    TextureManager::getInstance().loadTexture("files/images/face_happy.png");
    face_button.setTexture(TextureManager::getInstance().getTexture("files/images/face_happy.png"));

    TextureManager::getInstance().loadTexture("files/images/debug.png");
    debug_button.setTexture(TextureManager::getInstance().getTexture("files/images/debug.png"));

    TextureManager::getInstance().loadTexture("files/images/pause.png");
    pause_button.setTexture(TextureManager::getInstance().getTexture("files/images/pause.png"));

    TextureManager::getInstance().loadTexture("files/images/leaderboard.png");
    leaderboard_button.setTexture(TextureManager::getInstance().getTexture("files/images/leaderboard.png"));

    TextureManager::getInstance().loadTexture("files/images/digits.png");
    remaining_mines_counter.setTexture(TextureManager::getInstance().getTexture("files/images/digits.png"));
}

void Game::setButtonPositions() {
    face_button.setPosition(width / 2 - 32, height - 84);
    debug_button.setPosition(width - 304, height - 84);
    pause_button.setPosition(width - 240, height - 84);
    leaderboard_button.setPosition(width - 176, height - 84);
    remaining_mines_counter.setPosition(33, height - 84);
    //    timer_text.setPosition(width - 140, height - 100 + 16);
}

void Game::handleDebugButtonClick() {
    if (!game_over) {
        debug_mode = !debug_mode;
        for (unsigned int i = 0; i < board.getHeight(); ++i) {
            for (unsigned int j = 0; j < board.getWidth(); ++j) {
                Tile& tile = board.getTile(i, j);
                if (tile.hasMine()) {
                    if (debug_mode) {
                        tile.reveal();
                    } else {
                        tile.setTexture("files/images/tile_hidden.png");
                        tile.setRevealed(false);
                        tile.clearOverlaySprites();
                    }
                }
            }
        }
    }
}

void Game::resetGame() {
    game_over = false;
    debug_mode = false;
    board.reset();
    board.setMines();
    board.updateAdjacentMineCounts();
    remaining_mines = mine_count;
    TextureManager::getInstance().loadTexture("files/images/face_happy.png");
    face_button.setTexture(TextureManager::getInstance().getTexture("files/images/face_happy.png"));
}

void Game::handlePauseButtonClick() {
    if (!game_over) {
        paused = !paused;
        if (paused) {
            TextureManager::getInstance().loadTexture("files/images/play.png");
            pause_button.setTexture(TextureManager::getInstance().getTexture("files/images/play.png"));
            for (unsigned int i = 0; i < board.getHeight(); ++i) {
                for (unsigned int j = 0; j < board.getWidth(); ++j) {
                    Tile& tile = board.getTile(i, j);
                    tile.setTexture("files/images/tile_revealed.png");
                    tile.clearOverlaySprites();
                }
            }
        } else {
            TextureManager::getInstance().loadTexture("files/images/pause.png");
            pause_button.setTexture(TextureManager::getInstance().getTexture("files/images/pause.png"));
            board.restoreTileStates();
        }
    }
}

void Game::handleLeaderboardButtonClick() {
    paused = true;
    TextureManager::getInstance().loadTexture("files/images/play.png");
    pause_button.setTexture(TextureManager::getInstance().getTexture("files/images/play.png"));
    for (unsigned int i = 0; i < board.getHeight(); ++i) {
        for (unsigned int j = 0; j < board.getWidth(); ++j) {
            Tile& tile = board.getTile(i, j);
            tile.setTexture("files/images/tile_revealed.png");
        }
    }

    LeaderboardWindow leaderboardWindow(width / 2, (height - 50) / 2);
    leaderboardWindow.run();
}

void Game::handleWin() {
    game_won = true;
    for (unsigned int i = 0; i < board.getHeight(); i++) {
        for (unsigned int j = 0; j < board.getWidth(); j++) {
            Tile& tile = board.getTile(i, j);
            if (!tile.isRevealed() && !tile.hasMine()) {
                tile.reveal();
            }
            if (tile.hasMine()) {
                tile.toggleFlag();
            }
        }
    }

    TextureManager::getInstance().loadTexture("files/images/face_win.png");
    face_button.setTexture(TextureManager::getInstance().getTexture("files/images/face_win.png"));

    sf::Time elapsed = clock.getElapsedTime();
    int minutes = elapsed.asSeconds() / 60;
    int seconds = static_cast<int>(elapsed.asSeconds()) % 60;
    std::string time = std::to_string(minutes) + ":" + (seconds < 10 ? "0" : "") + std::to_string(seconds);

    LeaderboardWindow leaderboardWindow(400, 400);
    leaderboardWindow.run(true, username, time);
}

bool Game::checkWinCondition() {
    unsigned int revealed_tiles = 0;
    for (unsigned int i = 0; i < board.getHeight(); i++) {
        for (unsigned int j = 0; j < board.getWidth(); j++) {
            Tile& tile = board.getTile(i, j);
            if (tile.isRevealed() && !tile.hasMine()) {
                revealed_tiles++;
            }
        }
    }

    return revealed_tiles == board.getWidth() * board.getHeight() - mine_count;
}
