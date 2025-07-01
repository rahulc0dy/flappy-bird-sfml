#include "Background.hpp"

#include "Game.hpp"
#include "Logger.hpp"

const float Background::BACKGROUND_SPEED = 50.0f;
const float Background::GROUND_SPEED = 100.0f;

Background::Background(sf::RenderWindow& window, AssetManager &assetManager)
    : m_window(window),
      m_assetManager(assetManager),
      m_background1(m_assetManager.getTexture("background")),
      m_background2(m_assetManager.getTexture("background")),
      m_ground1(m_assetManager.getTexture("ground")),
      m_ground2(m_assetManager.getTexture("ground")),
      m_backgroundOffset(0.0f),
      m_groundOffset(0.0f) {
    
    // Get window dimensions
    sf::Vector2u windowSize = m_window.getSize();
    float windowWidth = static_cast<float>(windowSize.x);
    float windowHeight = static_cast<float>(windowSize.y);
    
    // Calculate ground Y position based on window height (90% down from top)
    m_groundY = windowHeight * 0.9f;
    
    // Setup background sprites
    m_background1.setTexture(m_assetManager.getTexture("background"));
    m_background2.setTexture(m_assetManager.getTexture("background"));

    // Calculate scale to fit window height
    sf::Vector2u bgTextureSize = m_background1.getTexture()->getSize();
    float bgScaleY = windowHeight / static_cast<float>(bgTextureSize.y);
    float bgScaleX = bgScaleY; // Maintain aspect ratio
    
    m_background1.setScale({bgScaleX, bgScaleY});
    m_background2.setScale({bgScaleX, bgScaleY});

    m_background1.setPosition({0, 0});
    m_background2.setPosition({m_background1.getGlobalBounds().size.x, 0});

    // Setup ground sprites
    m_ground1.setTexture(m_assetManager.getTexture("ground"));
    m_ground2.setTexture(m_assetManager.getTexture("ground"));

    // Calculate scale for ground to fit window width
    sf::Vector2u groundTextureSize = m_ground1.getTexture()->getSize();
    float groundScaleX = windowWidth / static_cast<float>(groundTextureSize.x);
    float groundScaleY = (windowHeight - m_groundY) / static_cast<float>(groundTextureSize.y);
    
    m_ground1.setScale({groundScaleX, groundScaleY});
    m_ground2.setScale({groundScaleX, groundScaleY});

    m_ground1.setPosition({0, m_groundY});
    m_ground2.setPosition({m_ground1.getGlobalBounds().size.x, m_groundY});
}

void Background::update(float deltaTime) {
    // Update background
    m_backgroundOffset += BACKGROUND_SPEED * deltaTime;
    float bgWidth = m_background1.getGlobalBounds().size.x;

    if (m_backgroundOffset >= bgWidth) {
        m_backgroundOffset = 0.0f;
    }

    m_background1.setPosition({-m_backgroundOffset, 0});
    m_background2.setPosition({bgWidth - m_backgroundOffset, 0});

    // Update ground
    m_groundOffset += GROUND_SPEED * deltaTime;
    float groundWidth = m_ground1.getGlobalBounds().size.x;

    if (m_groundOffset >= groundWidth) {
        m_groundOffset = 0.0f;
    }

    m_ground1.setPosition({-m_groundOffset, m_groundY});
    m_ground2.setPosition({groundWidth - m_groundOffset, m_groundY});
}

void Background::render() {
    m_window.draw(m_background1);
    m_window.draw(m_background2);
    m_window.draw(m_ground1);
    m_window.draw(m_ground2);
}

void Background::reset() {
    m_backgroundOffset = 0.0f;
    m_groundOffset = 0.0f;
}

float Background::getGroundY() const {
    return m_groundY;
}