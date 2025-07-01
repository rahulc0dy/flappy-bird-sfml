#pragma once
#include "GameState.hpp"
#include "Player.hpp"
#include "PipeManager.hpp"
#include "Background.hpp"
#include "ScoreManager.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class PlayState : public GameState {
public:
    PlayState(sf::RenderWindow& window, AssetManager& assetManager);
    ~PlayState() = default;

    void handleInput(const sf::Event& event, GameStateManager& stateManager) override;
    void update(float deltaTime, GameStateManager& stateManager) override;
    void render() override;
    void onEnter() override;

private:
    void checkCollisions(GameStateManager& stateManager);
    void resetGame();

    AssetManager& m_assetManager;
    std::unique_ptr<Player> m_player;
    std::unique_ptr<PipeManager> m_pipeManager;
    std::unique_ptr<Background> m_background;
    std::unique_ptr<ScoreManager> m_scoreManager;
    
    sf::Sound m_jumpSound;
    sf::Sound m_scoreSound;
    sf::Sound m_hitSound;
    
    bool m_gameStarted;
    sf::Text m_startText;
};