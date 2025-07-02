#pragma once
#include <SFML/Graphics.hpp>
#include "AssetManager.hpp"

class Background {
public:
    Background(sf::RenderWindow &window, AssetManager &assetManager);

    ~Background() = default;

    void update(float deltaTime);

    void render();

    void reset();

    float getGroundY() const;

private:
    sf::RenderWindow &m_window;
    AssetManager &m_assetManager;
    sf::Sprite m_background;
    sf::Sprite m_ground;

    float m_backgroundOffset;
    float m_groundOffset;
    float m_groundY; // Dynamic ground Y position

    static const float BACKGROUND_SPEED;
    static const float GROUND_SPEED;
};
