/**
* COP3503 - Project 3
* @author Preston Hemmy
* @version 1.0
*/

#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "TextureManager.h"

class Tile {
    bool is_mine;
    bool revealed;
    bool flagged;
    unsigned int adjacent_mines;
    sf::Sprite sprite;
    std::vector<sf::Sprite> overlay_sprites;

public:
    Tile();

    void setPosition(float x, float y);

    void setTexture(const std::string& filename);

    void draw(sf::RenderWindow& window);

    void reveal();

    void toggleFlag();

    bool isRevealed() const;

    bool isFlagged() const;

    bool hasMine() const;

    void setRevealed(bool revealed);

    void setMine(bool is_mine);

    void setAdjacentMines(unsigned int count);

    unsigned int getAdjacentMines() const;

    void clearOverlaySprites();
};