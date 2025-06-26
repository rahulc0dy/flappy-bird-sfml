#pragma once
#include <SFML/Graphics.hpp>
#include "AssetManager.hpp"

class Background {
public:
    Background(AssetManager& assetManager);
    ~Background() = default;

    void update(float deltaTime);
    void render(sf::RenderWindow& window);
    void reset();

private:
    AssetManager& m_assetManager;
    sf::Sprite m_background1;
    sf::Sprite m_background2;
    sf::Sprite m_ground1;
    sf::Sprite m_ground2;
    
    float m_backgroundOffset;
    float m_groundOffset;
    
    static const float BACKGROUND_SPEED;
    static const float GROUND_SPEED;
    static const float GROUND_Y;
};