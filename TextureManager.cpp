/**
* COP3503 - Project 3
* @author Preston Hemmy
* @version 1.0
*/

#include <iostream>
#include "TextureManager.h"

TextureManager &TextureManager::getInstance() {
    static TextureManager instance;
    return instance;
}

void TextureManager::loadTexture(const std::string &filename) {
    if (textures.find(filename) == textures.end()) {
        sf::Texture texture;
        if (texture.loadFromFile(filename)) {
            textures[filename] = texture;
        } else {
            std::cerr << "Could not load texture: " << filename << std::endl;
        }
    }
}

const sf::Texture &TextureManager::getTexture(const std::string &filename) {
    if (textures.find(filename) != textures.end()) {
        return textures[filename];
    } else {
        static sf::Texture empty_texture;
        return empty_texture;
    }
}
