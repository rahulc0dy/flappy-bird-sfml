#pragma once
#include "GameState.hpp"
#include <SFML/Graphics.hpp>

#include "AssetManager.hpp"

class GameOverState : public GameState {
public:
    GameOverState(sf::RenderWindow& window, AssetManager &assetManager, int score, int bestScore);

    ~GameOverState() = default;

    void handleInput(const sf::Event &event, GameStateManager &stateManager) override;

    void update(float deltaTime, GameStateManager &stateManager) override;

    void render() override;

    void onEnter() override;

private:
    AssetManager &m_assetManager;
    sf::Sprite m_background;
    sf::Text m_gameOverText;
    sf::Text m_scoreText;
    sf::Text m_bestScoreText;
    sf::Text m_restartText;
    sf::Text m_menuText;

    int m_score;
    int m_bestScore;
    float m_restartTextBlink;
    bool m_showRestartText;
};