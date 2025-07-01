#include "GameOverState.hpp"
#include "PlayState.hpp"
#include "MenuState.hpp"
#include "GameStateManager.hpp"
#include <SFML/Window/Event.hpp>

GameOverState::GameOverState(sf::RenderWindow& window, AssetManager &assetManager, int score, int bestScore)
    : GameState(window),
      m_assetManager(assetManager),
      m_background(m_assetManager.getTexture("background")),
      m_gameOverText(m_assetManager.getFont("main")),
      m_scoreText(m_assetManager.getFont("main")),
      m_bestScoreText(m_assetManager.getFont("main")),
      m_restartText(m_assetManager.getFont("main")),
      m_menuText(m_assetManager.getFont("main")),
      m_score(score),
      m_bestScore(bestScore),
      m_restartTextBlink(0.0f),
      m_showRestartText(true) {
    // Setup background
    m_background.setTexture(m_assetManager.getTexture("background"));
    m_background.setScale({2.0f, 2.0f});
    m_background.setColor(sf::Color(100, 100, 100, 200));

    // Setup game over text
    m_gameOverText.setFont(m_assetManager.getFont("main"));
    m_gameOverText.setString("Game Over");
    m_gameOverText.setCharacterSize(48);
    m_gameOverText.setFillColor(sf::Color::Red);
    m_gameOverText.setOutlineColor(sf::Color::Black);
    m_gameOverText.setOutlineThickness(3);

    auto gameOverBounds = m_gameOverText.getLocalBounds();
    m_gameOverText.setPosition({400 - gameOverBounds.size.x / 2, 150});

    // Setup score text
    m_scoreText.setFont(m_assetManager.getFont("pixel"));
    m_scoreText.setString("Score: " + std::to_string(m_score));
    m_scoreText.setCharacterSize(24);
    m_scoreText.setFillColor(sf::Color::White);

    auto scoreBounds = m_scoreText.getLocalBounds();
    m_scoreText.setPosition({400 - scoreBounds.size.x / 2, 250});

    // Setup best score text
    m_bestScoreText.setFont(m_assetManager.getFont("pixel"));
    m_bestScoreText.setString("Best: " + std::to_string(m_bestScore));
    m_bestScoreText.setCharacterSize(24);
    m_bestScoreText.setFillColor(sf::Color::Yellow);

    auto bestBounds = m_bestScoreText.getLocalBounds();
    m_bestScoreText.setPosition({400 - bestBounds.size.x / 2, 290});

    // Setup restart text
    m_restartText.setFont(m_assetManager.getFont("pixel"));
    m_restartText.setString("Press SPACE to play again");
    m_restartText.setCharacterSize(20);
    m_restartText.setFillColor(sf::Color::Green);

    auto restartBounds = m_restartText.getLocalBounds();
    m_restartText.setPosition({400 - restartBounds.size.x / 2, 380});

    // Setup menu text
    m_menuText.setFont(m_assetManager.getFont("pixel"));
    m_menuText.setString("Press ESC for menu");
    m_menuText.setCharacterSize(18);
    m_menuText.setFillColor(sf::Color::White);

    auto menuBounds = m_menuText.getLocalBounds();
    m_menuText.setPosition({400 - menuBounds.size.x / 2, 450});
}

void GameOverState::handleInput(const sf::Event &event, GameStateManager &stateManager) {
    if (event.is<sf::Event::KeyPressed>()) {
        const auto &keyEvent = event.getIf<sf::Event::KeyPressed>();
        if (keyEvent->code == sf::Keyboard::Key::Space) {
            stateManager.changeState(std::make_unique<PlayState>(m_window, m_assetManager));
        } else if (keyEvent->code == sf::Keyboard::Key::Escape) {
            stateManager.changeState(std::make_unique<MenuState>(m_window, m_assetManager));
        }
    }
}

void GameOverState::update(float deltaTime, GameStateManager &stateManager) {
    m_restartTextBlink += deltaTime;
    if (m_restartTextBlink >= 0.5f) {
        m_showRestartText = !m_showRestartText;
        m_restartTextBlink = 0.0f;
    }
}

void GameOverState::render() {
    m_window.draw(m_background);
    m_window.draw(m_gameOverText);
    m_window.draw(m_scoreText);
    m_window.draw(m_bestScoreText);
    if (m_showRestartText) {
        m_window.draw(m_restartText);
    }
    m_window.draw(m_menuText);
}

void GameOverState::onEnter() {
    // Stop background music or play game over sound
}