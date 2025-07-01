#pragma once
#include <SFML/Graphics.hpp>

class GameStateManager;

class GameState {
public:
    GameState(sf::RenderWindow& window) : m_window(window) {}
    virtual ~GameState() = default;

    virtual void handleInput(const sf::Event& event, GameStateManager& stateManager) = 0;
    virtual void update(float deltaTime, GameStateManager& stateManager) = 0;
    virtual void render() = 0;
    virtual void onEnter() {}
    virtual void onExit() {}

protected:
    sf::RenderWindow& m_window;
};