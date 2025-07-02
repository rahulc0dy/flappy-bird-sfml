#include "Background.hpp"
#include <cmath>

const float Background::BACKGROUND_SPEED = 50.0f;
const float Background::GROUND_SPEED = 100.0f;

Background::Background(sf::RenderWindow &window, AssetManager &assetManager)
    : m_window(window),
      m_assetManager(assetManager),
      m_background(m_assetManager.getTexture("background")),
      m_ground(m_assetManager.getTexture("ground")),
      m_backgroundOffset(0.0f),
      m_groundOffset(0.0f) {
    m_groundY = m_window.getSize().y * 0.9f;

    sf::Vector2u bgTexSize = m_background.getTexture().getSize();
    float bgScale = m_groundY / static_cast<float>(bgTexSize.y);
    m_background.setScale({bgScale, bgScale});
    m_background.setPosition({0, 0});

    sf::Vector2u groundTexSize = m_ground.getTexture().getSize();
    float groundScaleX = m_window.getSize().x / static_cast<float>(groundTexSize.x);
    float groundScaleY = (m_window.getSize().y - m_groundY) / static_cast<float>(groundTexSize.y);
    m_ground.setScale({groundScaleX, groundScaleY});
    m_ground.setPosition({0, m_groundY});
}

void Background::update(float deltaTime) {
    m_backgroundOffset += BACKGROUND_SPEED * deltaTime;
    float bgWidth = m_background.getGlobalBounds().size.x;
    if (m_backgroundOffset >= bgWidth) {
        m_backgroundOffset = std::fmod(m_backgroundOffset, bgWidth);
    }

    m_groundOffset += GROUND_SPEED * deltaTime;
    float groundWidth = m_ground.getGlobalBounds().size.x;
    if (m_groundOffset >= groundWidth) {
        m_groundOffset = std::fmod(m_groundOffset, groundWidth);
    }
}

void Background::render() {
    // Draw background tiles
    float bgWidth = m_background.getGlobalBounds().size.x;
    int numBgTiles = static_cast<int>(std::ceil(m_window.getSize().x / bgWidth)) + 1;
    for (int i = 0; i < numBgTiles; ++i) {
        sf::Sprite bg = m_background;
        bg.setPosition({-m_backgroundOffset + i * bgWidth, 0});
        m_window.draw(bg);
    }

    // Draw ground tiles
    float groundWidth = m_ground.getGlobalBounds().size.x;
    int numGroundTiles = static_cast<int>(std::ceil(m_window.getSize().x / groundWidth)) + 1;
    for (int i = 0; i < numGroundTiles; ++i) {
        sf::Sprite ground = m_ground;
        ground.setPosition({-m_groundOffset + i * groundWidth, m_groundY});
        m_window.draw(ground);
    }
}

void Background::reset() {
    m_backgroundOffset = 0.0f;
    m_groundOffset = 0.0f;
}

float Background::getGroundY() const {
    return m_groundY;
}
