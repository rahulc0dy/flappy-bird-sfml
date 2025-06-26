#pragma once
#include <SFML/Graphics.hpp>
#include "AssetManager.hpp"

class Pipe {
public:
    Pipe(AssetManager& assetManager, float x, float gapY, float gapSize);
    ~Pipe() = default;

    void update(float deltaTime);
    void render(sf::RenderWindow& window);

    sf::FloatRect getTopBounds() const;
    sf::FloatRect getBottomBounds() const;
    float getX() const { return m_x; }
    bool isOffScreen() const;
    bool hasPassedPlayer(float playerX) const;

private:
    AssetManager& m_assetManager;
    sf::Sprite m_topPipe;
    sf::Sprite m_bottomPipe;
    
    float m_x;
    float m_gapY;
    float m_gapSize;
    
    static const float PIPE_SPEED;
    static const float PIPE_WIDTH;
    static const float PIPE_HEIGHT;
};