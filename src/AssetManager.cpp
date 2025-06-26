#include "AssetManager.hpp"
#include <iostream>

void AssetManager::loadTexture(const std::string &name, const std::string &filename) {
    auto texture = std::make_unique<sf::Texture>();
    if (!texture->loadFromFile(filename)) {
        std::cerr << "Error loading texture: " << filename << std::endl;
        return;
    }
    m_textures[name] = std::move(texture);
}

void AssetManager::loadFont(const std::string &name, const std::string &filename) {
    auto font = std::make_unique<sf::Font>();
    if (!font->openFromFile(filename)) {
        std::cerr << "Error loading font: " << filename << std::endl;
        return;
    }
    m_fonts[name] = std::move(font);
}

void AssetManager::loadSound(const std::string &name, const std::string &filename) {
    auto soundBuffer = std::make_unique<sf::SoundBuffer>();
    if (!soundBuffer->loadFromFile(filename)) {
        std::cerr << "Error loading sound: " << filename << std::endl;
        return;
    }
    m_soundBuffers[name] = std::move(soundBuffer);
}

void AssetManager::loadMusic(const std::string &name, const std::string &filename) {
    auto music = std::make_unique<sf::Music>();
    if (!music->openFromFile(filename)) {
        std::cerr << "Error loading music: " << filename << std::endl;
        return;
    }
    m_music[name] = std::move(music);
}

const sf::Texture &AssetManager::getTexture(const std::string &name) const {
    return *m_textures.at(name);
}

const sf::Font &AssetManager::getFont(const std::string &name) const {
    return *m_fonts.at(name);
}

const sf::SoundBuffer &AssetManager::getSoundBuffer(const std::string &name) const {
    return *m_soundBuffers.at(name);
}

sf::Music &AssetManager::getMusic(const std::string &name) {
    return *m_music.at(name);
}
