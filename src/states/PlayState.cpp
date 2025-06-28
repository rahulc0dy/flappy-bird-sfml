#include "PlayState.hpp"
#include "GameOverState.hpp"
#include "GameStateManager.hpp"
#include <SFML/Window/Event.hpp>
#include "Player.hpp"

PlayState::PlayState(AssetManager &assetManager)
    : m_assetManager(assetManager),
      m_jumpSound(assetManager.getSoundBuffer("jump")),
      m_scoreSound(assetManager.getSoundBuffer("score")),
      m_hitSound(assetManager.getSoundBuffer("hit")),
      m_gameStarted(false),
      m_startText(m_assetManager.getFont("pixel")) {
    m_player = std::make_unique<Player>(m_assetManager);
    m_pipeManager = std::make_unique<PipeManager>(m_assetManager);
    m_background = std::make_unique<Background>(m_assetManager);
    m_scoreManager = std::make_unique<ScoreManager>(m_assetManager);

    // Setup start text
    m_startText.setFont(m_assetManager.getFont("pixel"));
    m_startText.setString("Press SPACE to start");
    m_startText.setCharacterSize(24);
    m_startText.setFillColor(sf::Color::White);
    m_startText.setOutlineColor(sf::Color::Black);
    m_startText.setOutlineThickness(2);

    auto bounds = m_startText.getLocalBounds();
    m_startText.setPosition({400 - bounds.size.x / 2, 300});
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

void PlayState::render(sf::RenderWindow &window) {
    m_background->render(window);
    m_pipeManager->render(window);
    m_player->render(window);
    m_scoreManager->render(window);

    if (!m_gameStarted) {
        window.draw(m_startText);
    }
}

void PlayState::onEnter() {
    resetGame();
}

void PlayState::checkCollisions(GameStateManager &stateManager) {
    // Check ground collision
    if (m_player->isOnGround()) {
        stateManager.changeState(std::make_unique<GameOverState>(
            m_assetManager,
            m_scoreManager->getCurrentScore(),
            m_scoreManager->getBestScore()
        ));
        return;
    }

    // Check pipe collision
    if (m_pipeManager->checkCollision(m_player->getBounds())) {
        stateManager.changeState(std::make_unique<GameOverState>(
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
