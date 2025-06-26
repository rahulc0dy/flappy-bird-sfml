#pragma once
#include <stack>
#include <memory>
#include "GameState.hpp"
#include "AssetManager.hpp"

class GameStateManager {
public:
    GameStateManager(AssetManager& assetManager);
    ~GameStateManager() = default;

    void pushState(std::unique_ptr<GameState> state);
    void popState();
    void changeState(std::unique_ptr<GameState> state);
    
    void handleInput(const sf::Event& event);
    void update(float deltaTime);
    void render(sf::RenderWindow& window);

    AssetManager& getAssetManager() { return m_assetManager; }
    bool isEmpty() const { return m_states.empty(); }

private:
    std::stack<std::unique_ptr<GameState>> m_states;
    AssetManager& m_assetManager;
};