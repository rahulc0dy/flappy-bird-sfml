#pragma once
#include <SFML/Graphics.hpp>

class GameStateManager;

class GameState {
public:
    GameState() = default;
    virtual ~GameState() = default;

    virtual void handleInput(const sf::Event& event, GameStateManager& stateManager) = 0;
    virtual void update(float deltaTime, GameStateManager& stateManager) = 0;
    virtual void render(sf::RenderWindow& window) = 0;
    virtual void onEnter() {}
    virtual void onExit() {}
};