#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <unordered_map>
#include <string>
#include <memory>

class AssetManager {
public:
    AssetManager(sf::RenderWindow& window);

    ~AssetManager() = default;

    void loadTexture(const std::string &name, const std::string &filename);

    void loadFont(const std::string &name, const std::string &filename);

    void loadSound(const std::string &name, const std::string &filename);

    void loadMusic(const std::string &name, const std::string &filename);

    const sf::Texture &getTexture(const std::string &name);

    const sf::Font &getFont(const std::string &name) const;

    const sf::SoundBuffer &getSoundBuffer(const std::string &name) const;

    sf::Music &getMusic(const std::string &name);

    sf::RenderWindow& getWindow() { return m_window; }

private:
    sf::RenderWindow& m_window;
    std::unordered_map<std::string, std::unique_ptr<sf::Texture> > m_textures;
    std::unordered_map<std::string, std::unique_ptr<sf::Font> > m_fonts;
    std::unordered_map<std::string, std::unique_ptr<sf::SoundBuffer> > m_soundBuffers;
    std::unordered_map<std::string, std::unique_ptr<sf::Music> > m_music;
};