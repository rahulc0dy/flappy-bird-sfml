#include "GameStateManager.hpp"

GameStateManager::GameStateManager(sf::RenderWindow& window, AssetManager& assetManager) 
    : m_window(window), m_assetManager(assetManager) {
}

void GameStateManager::pushState(std::unique_ptr<GameState> state) {
    if (!m_states.empty()) {
        m_states.top()->onExit();
    }
    m_states.push(std::move(state));
    m_states.top()->onEnter();
}

void GameStateManager::popState() {
    if (!m_states.empty()) {
        m_states.top()->onExit();
        m_states.pop();
        if (!m_states.empty()) {
            m_states.top()->onEnter();
        }
    }
}

void GameStateManager::changeState(std::unique_ptr<GameState> state) {
    if (!m_states.empty()) {
        m_states.top()->onExit();
        m_states.pop();
    }
    m_states.push(std::move(state));
    m_states.top()->onEnter();
}

void GameStateManager::handleInput(const sf::Event& event) {
    if (!m_states.empty()) {
        m_states.top()->handleInput(event, *this);
    }
}

void GameStateManager::update(float deltaTime) {
    if (!m_states.empty()) {
        m_states.top()->update(deltaTime, *this);
    }
}

void GameStateManager::render() {
    if (!m_states.empty()) {
        m_states.top()->render();
    }
}