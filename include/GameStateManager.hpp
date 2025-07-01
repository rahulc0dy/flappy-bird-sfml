#pragma once
#include <stack>
#include <memory>
#include "GameState.hpp"
#include "AssetManager.hpp"

class GameStateManager {
public:
    GameStateManager(sf::RenderWindow& window, AssetManager& assetManager);
    ~GameStateManager() = default;

    void pushState(std::unique_ptr<GameState> state);
    void popState();
    void changeState(std::unique_ptr<GameState> state);
    
    void handleInput(const sf::Event& event);
    void update(float deltaTime);
    void render();

    sf::RenderWindow& getWindow() { return m_window; }
    AssetManager& getAssetManager() { return m_assetManager; }
    bool isEmpty() const { return m_states.empty(); }

private:
    sf::RenderWindow& m_window;
    std::stack<std::unique_ptr<GameState>> m_states;
    AssetManager& m_assetManager;
};