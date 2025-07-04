#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "AssetManager.hpp"

class Player {
public:
    Player(sf::RenderWindow& window, AssetManager& assetManager);
    ~Player() = default;

    void update(float deltaTime);
    void render();
    void jump();
    void reset();

    sf::FloatRect getBounds() const;
    sf::Vector2f getPosition() const { return m_sprite.getPosition(); }
    bool isOnGround() const;

private:
    void updateAnimation(float deltaTime);
    void updatePhysics(float deltaTime);

    sf::RenderWindow& m_window;
    AssetManager& m_assetManager;
    sf::Sprite m_sprite;
    sf::Vector2f m_velocity;
    
    // Animation
    int m_currentFrame;
    float m_animationTimer;
    static const int FRAME_COUNT = 4;
    static const float ANIMATION_SPEED;
    static const int FRAME_WIDTH = 16;
    static const int FRAME_HEIGHT = 16;
    
    // Physics
    static const float GRAVITY;
    static const float JUMP_FORCE;
    static const float MAX_FALL_SPEED;
    
    // Dynamic position values
    float m_startX;
    float m_startY;
    float m_groundY;
};