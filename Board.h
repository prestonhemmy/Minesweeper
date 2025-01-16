/**
* COP3503 - Project 3
* @author Preston Hemmy
* @version 1.0
*/

#pragma once
#include <vector>
#include "Tile.h"
#include "TextureManager.h"

class Board {
    unsigned int width;
    unsigned int height;
    unsigned int mine_count;
    std::vector<std::vector<Tile>> tiles;


public:
    Board(unsigned int width, unsigned int height, unsigned int mine_count);

    void draw(sf::RenderWindow& window);

    void setMines();

    void updateAdjacentMineCounts();

    void revealAdjacentTiles(unsigned int row, unsigned int col);

    void reset();

    void restoreTileStates();

    Tile& getTile(unsigned int row, unsigned int col);

    unsigned int getHeight() const;

    unsigned int getWidth() const;
};