#include "Background.hpp"

#include "Game.hpp"
#include "Logger.hpp"

const float Background::BACKGROUND_SPEED = 50.0f;
const float Background::GROUND_SPEED = 100.0f;
const float Background::GROUND_Y = 550.0f;

Background::Background(AssetManager &assetManager)
    : m_assetManager(assetManager),
      m_background1(m_assetManager.getTexture("background")),
      m_background2(m_assetManager.getTexture("background")),
      m_ground1(m_assetManager.getTexture("ground")),
      m_ground2(m_assetManager.getTexture("ground")),
      m_backgroundOffset(0.0f),
      m_groundOffset(0.0f) {
    // Setup background sprites
    m_background1.setTexture(m_assetManager.getTexture("background"));
    m_background2.setTexture(m_assetManager.getTexture("background"));

    m_background1.setScale({2.0f, 2.0f});
    m_background2.setScale({2.0f, 2.0f});

    m_background1.setPosition({0, 0});
    m_background2.setPosition({m_background1.getGlobalBounds().size.x, 0});

    // Setup ground sprites
    m_ground1.setTexture(m_assetManager.getTexture("ground"));
    m_ground2.setTexture(m_assetManager.getTexture("ground"));

    m_ground1.setScale({2.0f, 2.0f});
    m_ground2.setScale({2.0f, 2.0f});

    m_ground1.setPosition({0, GROUND_Y});
    m_ground2.setPosition({m_ground1.getGlobalBounds().size.x, GROUND_Y});
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

    m_ground1.setPosition({-m_groundOffset, GROUND_Y});
    m_ground2.setPosition({groundWidth - m_groundOffset, GROUND_Y});
}

void Background::render(sf::RenderWindow &window) {
    window.draw(m_background1);
    window.draw(m_background2);
    window.draw(m_ground1);
    window.draw(m_ground2);
}

void Background::reset() {
    m_backgroundOffset = 0.0f;
    m_groundOffset = 0.0f;
}
