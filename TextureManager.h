/**
* COP3503 - Project 3
* @author Preston Hemmy
* @version 1.0
*/

#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <unordered_map>

class TextureManager {
    std::unordered_map<std::string, sf::Texture> textures;
    TextureManager() = default;

public:
    TextureManager(const TextureManager&) = delete;

    TextureManager& operator=(const TextureManager&) = delete;

    static TextureManager& getInstance();

    void loadTexture(const std::string& filename);

    const sf::Texture& getTexture(const std::string& filename);
};