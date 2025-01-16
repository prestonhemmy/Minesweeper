/**
* COP3503 - Project 3
* @author Preston Hemmy
* @version 1.0
*/

#include "Tile.h"

Tile::Tile() : is_mine(false), revealed(false), flagged(false), adjacent_mines(0) {
    setTexture("files/images/tile_hidden.png");
}

void Tile::setPosition(float x, float y) {
    sprite.setPosition(x, y);
}

void Tile::setTexture(const std::string& filename) {
    TextureManager::getInstance().loadTexture(filename);
    sprite.setTexture(TextureManager::getInstance().getTexture(filename));
}

void Tile::draw(sf::RenderWindow& window) {
    window.draw(sprite);
    for (const auto& overlay_sprite : overlay_sprites) {
        window.draw(overlay_sprite);
    }
}

void Tile::reveal() {
    if (!revealed && !flagged) {
        revealed = true;
        setTexture("files/images/tile_revealed.png");
        if (is_mine) {
            sf::Sprite mine_sprite;
            TextureManager::getInstance().loadTexture("files/images/mine.png");
            mine_sprite.setTexture(TextureManager::getInstance().getTexture("files/images/mine.png"));
            mine_sprite.setPosition(sprite.getPosition());
            overlay_sprites.push_back(mine_sprite);
        } else if (adjacent_mines > 0) {
            sf::Sprite number_sprite;
            TextureManager::getInstance().loadTexture("files/images/number_" + std::to_string(adjacent_mines) + ".png");
            number_sprite.setTexture(TextureManager::getInstance().getTexture("files/images/number_" + std::to_string(adjacent_mines) + ".png"));
            number_sprite.setPosition(sprite.getPosition());
            overlay_sprites.push_back(number_sprite);
        }
    }
}

void Tile::toggleFlag() {
    if (!revealed) {
        flagged = !flagged;
        if (flagged) {
            sf::Sprite flag_sprite;
            TextureManager::getInstance().loadTexture("files/images/flag.png");
            flag_sprite.setTexture(TextureManager::getInstance().getTexture("files/images/flag.png"));
            flag_sprite.setPosition(sprite.getPosition());
            overlay_sprites.push_back(flag_sprite);
        } else {
            overlay_sprites.pop_back();
        }
    }
}

bool Tile::isRevealed() const {
    return revealed;
}

bool Tile::isFlagged() const {
    return flagged;
}

bool Tile::hasMine() const {
    return is_mine;
}

void Tile::setRevealed(bool revealed) {
    this->revealed = revealed;
}

void Tile::setMine(bool is_mine) {
    this->is_mine = is_mine;
}

void Tile::setAdjacentMines(unsigned int count) {
    adjacent_mines = count;
}

unsigned int Tile::getAdjacentMines() const {
    return adjacent_mines;
}

void Tile::clearOverlaySprites() {
    overlay_sprites.clear();
}