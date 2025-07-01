#include "PlayState.hpp"
#include "GameOverState.hpp"
#include "GameStateManager.hpp"
#include <SFML/Window/Event.hpp>
#include "Player.hpp"

PlayState::PlayState(sf::RenderWindow& window, AssetManager &assetManager)
    : GameState(window),
      m_assetManager(assetManager),
      m_jumpSound(assetManager.getSoundBuffer("jump")),
      m_scoreSound(assetManager.getSoundBuffer("score")),
      m_hitSound(assetManager.getSoundBuffer("hit")),
      m_gameStarted(false),
      m_startText(m_assetManager.getFont("pixel")) {
    m_player = std::make_unique<Player>(m_window, m_assetManager);
    m_pipeManager = std::make_unique<PipeManager>(m_window, m_assetManager);
    m_background = std::make_unique<Background>(m_window, m_assetManager);
    m_scoreManager = std::make_unique<ScoreManager>(m_window, m_assetManager);

    // Setup start text with dynamic sizing
    sf::Vector2u windowSize = m_window.getSize();
    float windowWidth = static_cast<float>(windowSize.x);
    float windowHeight = static_cast<float>(windowSize.y);
    
    m_startText.setFont(m_assetManager.getFont("pixel"));
    
    // Calculate font size based on window size
    unsigned int fontSize = static_cast<unsigned int>(windowHeight * 0.04f); // 4% of window height
    m_startText.setCharacterSize(fontSize);
    
    m_startText.setString("Press SPACE to start");
    m_startText.setFillColor(sf::Color::White);
    m_startText.setOutlineColor(sf::Color::Black);
    
    float outlineThickness = windowHeight * 0.003f; // 0.3% of window height
    m_startText.setOutlineThickness(outlineThickness);

    // Center the text
    auto bounds = m_startText.getLocalBounds();
    float x = (windowWidth - bounds.size.x) / 2.0f;
    float y = windowHeight * 0.5f; // Center vertically
    m_startText.setPosition({x, y});
}

void PlayState::handleInput(const sf::Event &event, GameStateManager &stateManager) {
    if (event.is<sf::Event::KeyPressed>()) {
        const auto &keyEvent = event.getIf<sf::Event::KeyPressed>();
        if (keyEvent->code == sf::Keyboard::Key::Space) {
            if (!m_gameStarted) {
                m_gameStarted = true;
            }
            m_player->jump();
            m_jumpSound.stop();
            m_jumpSound.play();
        }
    }
}

void PlayState::update(float deltaTime, GameStateManager &stateManager) {
    if (!m_gameStarted) {
        return;
    }

    m_background->update(deltaTime);
    m_player->update(deltaTime);
    m_pipeManager->update(deltaTime);

    // Check for scoring
    int newScore = m_pipeManager->checkScoring(m_player->getPosition().x);
    if (newScore > 0) {
        m_scoreManager->addScore(newScore);
        m_scoreSound.play();
    }

    checkCollisions(stateManager);
}

void PlayState::render() {
    m_background->render();
    m_pipeManager->render();
    m_player->render();
    m_scoreManager->render();

    if (!m_gameStarted) {
        m_window.draw(m_startText);
    }
}

void PlayState::onEnter() {
    resetGame();
}

void PlayState::checkCollisions(GameStateManager &stateManager) {
    // Check ground collision
    if (m_player->isOnGround()) {
        m_hitSound.play();
        stateManager.changeState(std::make_unique<GameOverState>(
            m_window,
            m_assetManager,
            m_scoreManager->getCurrentScore(),
            m_scoreManager->getBestScore()
        ));
        return;
    }

    // Check pipe collision
    if (m_pipeManager->checkCollision(m_player->getBounds())) {
        m_hitSound.play();
        stateManager.changeState(std::make_unique<GameOverState>(
            m_window,
            m_assetManager,
            m_scoreManager->getCurrentScore(),
            m_scoreManager->getBestScore()
        ));
        return;
    }
}

void PlayState::resetGame() {
    m_gameStarted = false;
    m_player->reset();
    m_pipeManager->reset();
    m_background->reset();
    m_scoreManager->reset();
}