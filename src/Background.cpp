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
    sf::Vector2u windowSize = m_window.getSize();
    auto windowWidth = static_cast<float>(windowSize.x);
    auto windowHeight = static_cast<float>(windowSize.y);

    // Calculate ground Y position (90% down from top)
    m_groundY = windowHeight * 0.9f;

    // Setup background sprite: scale so its height matches m_groundY.
    sf::Vector2u bgTexSize = m_background.getTexture().getSize();
    float bgScale = m_groundY / static_cast<float>(bgTexSize.y);
    m_background.setScale({bgScale, bgScale});
    m_background.setPosition({0, 0});

    sf::Vector2u groundTexSize = m_ground.getTexture().getSize();
    float groundScaleX = windowWidth / static_cast<float>(groundTexSize.x);
    float groundScaleY = (windowHeight - m_groundY) / static_cast<float>(groundTexSize.y);
    m_ground.setScale({groundScaleX, groundScaleY});
    m_ground.setPosition({0, m_groundY});
}

void Background::update(float deltaTime) {
    // Update background offset
    m_backgroundOffset += BACKGROUND_SPEED * deltaTime;
    float bgWidth = m_background.getGlobalBounds().size.x;
    if (m_backgroundOffset >= bgWidth) {
        m_backgroundOffset = std::fmod(m_backgroundOffset, bgWidth);
    }

    // Update ground offset
    m_groundOffset += GROUND_SPEED * deltaTime;
    float groundWidth = m_ground.getGlobalBounds().size.x;
    if (m_groundOffset >= groundWidth) {
        m_groundOffset = std::fmod(m_groundOffset, groundWidth);
    }
}

void Background::render() {
    // Draw background: two copies for seamless scrolling
    sf::Sprite bg1 = m_background;
    bg1.setPosition({-m_backgroundOffset, 0});
    m_window.draw(bg1);

    sf::Sprite bg2 = m_background;
    float bgWidth = m_background.getGlobalBounds().size.x;
    // Fixed: Position the second tile immediately after the first
    bg2.setPosition({-m_backgroundOffset + bgWidth, 0});
    m_window.draw(bg2);

    // Draw ground: two copies for seamless scrolling
    sf::Sprite ground1 = m_ground;
    ground1.setPosition({-m_groundOffset, m_groundY});
    m_window.draw(ground1);

    sf::Sprite ground2 = m_ground;
    float groundWidth = m_ground.getGlobalBounds().size.x;
    // Fixed: Position the second ground tile immediately after the first
    ground2.setPosition({-m_groundOffset + groundWidth, m_groundY});
    m_window.draw(ground2);
}

void Background::reset() {
    m_backgroundOffset = 0.0f;
    m_groundOffset = 0.0f;
}

float Background::getGroundY() const {
    return m_groundY;
}
