#pragma once
#include "GameState.hpp"
#include <SFML/Graphics.hpp>

#include "AssetManager.hpp"

class MenuState : public GameState {
public:
    MenuState(sf::RenderWindow& window, AssetManager &assetManager);

    ~MenuState() = default;

    void handleInput(const sf::Event &event, GameStateManager &stateManager) override;

    void update(float deltaTime, GameStateManager &stateManager) override;

    void render() override;

    void onEnter() override;

private:
    AssetManager &m_assetManager;
    sf::Sprite m_background;
    sf::Text m_titleText;
    sf::Text m_playText;
    sf::Text m_instructionText;
    sf::Music *m_backgroundMusic{};

    float m_playTextBlink;
    bool m_showPlayText;
};