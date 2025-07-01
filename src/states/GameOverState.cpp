#include "GameOverState.hpp"
#include "PlayState.hpp"
#include "MenuState.hpp"
#include "GameStateManager.hpp"
#include <SFML/Window/Event.hpp>

GameOverState::GameOverState(sf::RenderWindow &window, AssetManager &assetManager, int score, int bestScore)
    : GameState(window),
      m_assetManager(assetManager),
      m_background(m_assetManager.getTexture("background")),
      m_gameOverText(m_assetManager.getFont("main")),
      m_scoreText(m_assetManager.getFont("pixel")),
      m_bestScoreText(m_assetManager.getFont("pixel")),
      m_restartText(m_assetManager.getFont("pixel")),
      m_menuText(m_assetManager.getFont("pixel")),
      m_score(score),
      m_bestScore(bestScore),
      m_restartTextBlink(0.0f),
      m_showRestartText(true) {
    // Get window dimensions for dynamic sizing and positioning
    sf::Vector2u windowSize = m_window.getSize();
    float windowWidth = static_cast<float>(windowSize.x);
    float windowHeight = static_cast<float>(windowSize.y);

    // Setup background
    m_background.setTexture(m_assetManager.getTexture("background"));

    // Scale background to fit window
    sf::Vector2u bgTextureSize = m_background.getTexture().getSize();
    float bgScaleX = windowWidth / static_cast<float>(bgTextureSize.x);
    float bgScaleY = windowHeight / static_cast<float>(bgTextureSize.y);
    m_background.setScale({bgScaleX, bgScaleY});
    m_background.setColor(sf::Color(100, 100, 100, 200));

    // Setup game over text
    m_gameOverText.setFont(m_assetManager.getFont("main"));
    m_gameOverText.setString("Game Over");

    unsigned int gameOverFontSize = static_cast<unsigned int>(windowHeight * 0.08f); // 8% of window height
    m_gameOverText.setCharacterSize(gameOverFontSize);
    m_gameOverText.setFillColor(sf::Color::Red);
    m_gameOverText.setOutlineColor(sf::Color::Black);
    m_gameOverText.setOutlineThickness(windowHeight * 0.005f); // 0.5% of window height

    auto gameOverBounds = m_gameOverText.getLocalBounds();
    m_gameOverText.setPosition({(windowWidth - gameOverBounds.size.x) / 2, windowHeight * 0.25f});

    // Setup score text
    m_scoreText.setFont(m_assetManager.getFont("pixel"));
    m_scoreText.setString("Score: " + std::to_string(m_score));

    unsigned int scoreFontSize = static_cast<unsigned int>(windowHeight * 0.04f); // 4% of window height
    m_scoreText.setCharacterSize(scoreFontSize);
    m_scoreText.setFillColor(sf::Color::White);

    auto scoreBounds = m_scoreText.getLocalBounds();
    m_scoreText.setPosition({(windowWidth - scoreBounds.size.x) / 2, windowHeight * 0.417f});

    // Setup best score text
    m_bestScoreText.setFont(m_assetManager.getFont("pixel"));
    m_bestScoreText.setString("Best: " + std::to_string(m_bestScore));
    m_bestScoreText.setCharacterSize(scoreFontSize);
    m_bestScoreText.setFillColor(sf::Color::Yellow);

    auto bestBounds = m_bestScoreText.getLocalBounds();
    m_bestScoreText.setPosition({(windowWidth - bestBounds.size.x) / 2, windowHeight * 0.483f});

    // Setup restart text
    m_restartText.setFont(m_assetManager.getFont("pixel"));
    m_restartText.setString("Press SPACE to play again");

    unsigned int restartFontSize = static_cast<unsigned int>(windowHeight * 0.033f); // 3.3% of window height
    m_restartText.setCharacterSize(restartFontSize);
    m_restartText.setFillColor(sf::Color::Green);

    auto restartBounds = m_restartText.getLocalBounds();
    m_restartText.setPosition({(windowWidth - restartBounds.size.x) / 2, windowHeight * 0.633f});

    // Setup menu text
    m_menuText.setFont(m_assetManager.getFont("pixel"));
    m_menuText.setString("Press ESC for menu");

    unsigned int menuFontSize = static_cast<unsigned int>(windowHeight * 0.03f); // 3% of window height
    m_menuText.setCharacterSize(menuFontSize);
    m_menuText.setFillColor(sf::Color::White);

    auto menuBounds = m_menuText.getLocalBounds();
    m_menuText.setPosition({(windowWidth - menuBounds.size.x) / 2, windowHeight * 0.75f});
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
