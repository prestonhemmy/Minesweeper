/**
* COP3503 - Project 3
* @author Preston Hemmy
* @version 1.0
*/

#include <algorithm>
#include <random>
#include "Board.h"

Board::Board(unsigned int width, unsigned int height, unsigned int mine_count) : width(width), height(height),
mine_count(mine_count), tiles(height, std::vector<Tile>(width)) {
    for (unsigned int i = 0; i < height; i++) {
        for (unsigned int j = 0; j < width; j++) {
            tiles[i][j].setPosition(j * 32.f, i * 32.f);
        }
    }
}

void Board::draw(sf::RenderWindow& window) {
    for (unsigned int i = 0; i < height; i++) {
        for (unsigned int j = 0; j < width; j++) {
            tiles[i][j].draw(window);
        }
    }
}

void Board::setMines() {
    std::vector<std::pair<unsigned int, unsigned int>> positions;
    for (unsigned int i = 0; i < height; i++) {
        for (unsigned int j = 0; j < width; j++) {
            positions.emplace_back(i, j);
        }
    }

    std::random_device rand;
    std::mt19937 rng(rand());
    std::shuffle(positions.begin(), positions.end(), rng);

    for (unsigned int i = 0; i < mine_count && i < positions.size(); i++) {
        unsigned int row = positions[i].first;
        unsigned int col = positions[i].second;
        tiles[row][col].setMine(true);
    }
}

void Board::updateAdjacentMineCounts() {
    for (unsigned int i = 0; i < height; i++) {
        for (unsigned int j = 0; j < width; j++) {
            if (!tiles[i][j].hasMine()) {
                unsigned int count = 0;

                for (int y = -1; y <= 1; y++) {
                    for (int x = -1; x <= 1; x++) {
                        int row = i + y;
                        int col = j + x;

                        if (row >= 0 && row < height && col >= 0 && col < width && tiles[row][col].hasMine()) {
                            count++;
                        }
                    }
                }

                tiles[i][j].setAdjacentMines(count);
            }
        }
    }
}

void Board::revealAdjacentTiles(unsigned int row, unsigned int col) {
    if (row >= height || col >= width || tiles[row][col].isRevealed() || tiles[row][col].hasMine()) {
        return;
    }

    tiles[row][col].reveal();

    if (tiles[row][col].getAdjacentMines() == 0) {
        for (int y = -1; y <= 1; y++) {
            for (int x = -1; x <= 1; x++) {
                if (x != 0 || y != 0) {
                    unsigned int newRow = row + y;
                    unsigned int newCol = col + x;
                    if (newRow < height && newCol < width && !tiles[newRow][newCol].isRevealed()) {
                        revealAdjacentTiles(newRow, newCol);
                    }
                }
            }
        }
    }
}

void Board::reset() {
    for (unsigned int i = 0; i < height; i++) {
        for (unsigned int j = 0; j < width; j++) {
            tiles[i][j].setTexture("files/images/tile_hidden.png");
            tiles[i][j].setRevealed(false);
            tiles[i][j].setMine(false);
            tiles[i][j].clearOverlaySprites();
        }
    }
}

Tile &Board::getTile(unsigned int row, unsigned int col) {
    return tiles[row][col];
}

unsigned int Board::getHeight() const {
    return height;
}

unsigned int Board::getWidth() const {
    return width;
}

void Board::restoreTileStates() {
    for (unsigned int i = 0; i < height; i++) {
        for (unsigned int j = 0; j < width; j++) {
            if (tiles[i][j].isRevealed()) {
                tiles[i][j].setTexture("files/images/tile_revealed.png");
                if (tiles[i][j].hasMine() || tiles[i][j].getAdjacentMines() > 0) {
                    tiles[i][j].reveal();
                }
            } else {
                tiles[i][j].setTexture("files/images/tile_hidden.png");
            }
        }
    }
}