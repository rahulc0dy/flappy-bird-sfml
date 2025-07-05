#include "Player.hpp"
#include <algorithm>

const float Player::ANIMATION_SPEED = 0.1f;
const float Player::GRAVITY = 980.0f;
const float Player::JUMP_FORCE = -350.0f;
const float Player::MAX_FALL_SPEED = 500.0f;

Player::Player(sf::RenderWindow &window, AssetManager &assetManager)
    : m_window(window),
      m_assetManager(assetManager),
      m_sprite(m_assetManager.getTexture("bird")),
      m_velocity(0.0f, 0.0f),
      m_currentFrame(0),
      m_animationTimer(0.0f) {
    sf::Vector2u windowSize = m_window.getSize();
    float windowWidth = static_cast<float>(windowSize.x);
    float windowHeight = static_cast<float>(windowSize.y);

    // Calculate dynamic positions based on window size
    m_startX = windowWidth * 0.125f; // 12.5% from left
    m_startY = windowHeight * 0.5f; // Center vertically
    m_groundY = windowHeight * 0.9f; // 90% down from top

    m_sprite.setTexture(m_assetManager.getTexture("bird"));
    m_sprite.setTextureRect(sf::IntRect({0, 0}, {FRAME_WIDTH, FRAME_HEIGHT}));

    // Calculate scale based on window size
    float scale = std::min(windowWidth / 400.0f, windowHeight / 300.0f);
    m_sprite.setScale({scale, scale});
    m_sprite.setOrigin({FRAME_WIDTH / 2.0f, FRAME_HEIGHT / 2.0f});

    reset();
}

void Player::update(float deltaTime) {
    updateAnimation(deltaTime);
    updatePhysics(deltaTime);
}

void Player::render() {
    m_window.draw(m_sprite);
}

void Player::jump() {
    m_velocity.y = JUMP_FORCE;
}

void Player::reset() {
    m_sprite.setPosition({m_startX, m_startY});
    m_velocity = sf::Vector2f(0.0f, 0.0f);
    m_currentFrame = 0;
    m_animationTimer = 0.0f;
}

sf::FloatRect Player::getBounds() const {
    return m_sprite.getGlobalBounds();
}

bool Player::isOnGround() const {
    return m_sprite.getPosition().y >= m_groundY;
}

void Player::updateAnimation(float deltaTime) {
    m_animationTimer += deltaTime;
    if (m_animationTimer >= ANIMATION_SPEED) {
        m_currentFrame = (m_currentFrame + 1) % FRAME_COUNT;
        m_sprite.setTextureRect(sf::IntRect(
            {m_currentFrame * FRAME_WIDTH, 0},
            {FRAME_WIDTH, FRAME_HEIGHT}
        ));
        m_animationTimer = 0.0f;
    }
}

void Player::updatePhysics(float deltaTime) {
    // Apply gravity
    m_velocity.y += GRAVITY * deltaTime;
    m_velocity.y = std::min(m_velocity.y, MAX_FALL_SPEED);

    // Update position
    sf::Vector2f position = m_sprite.getPosition();
    position.y += m_velocity.y * deltaTime;

    // Clamp to ground
    if (position.y >= m_groundY) {
        position.y = m_groundY;
        m_velocity.y = 0.0f;
    }

    // Clamp to ceiling
    if (position.y <= 0) {
        position.y = 0;
        m_velocity.y = 0.0f;
    }

    m_sprite.setPosition(position);

    // Rotate sprite based on velocity
    float rotation = std::clamp(m_velocity.y * 0.1f, -30.0f, 90.0f);
    m_sprite.setRotation(sf::degrees(rotation));
}
