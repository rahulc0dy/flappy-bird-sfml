#include "MenuState.hpp"
#include "PlayState.hpp"
#include "GameStateManager.hpp"
#include <SFML/Window/Event.hpp>

MenuState::MenuState(AssetManager& assetManager) 
    : m_assetManager(assetManager)
    , m_playTextBlink(0.0f)
    , m_showPlayText(true) {
    
    // Setup background
    m_background.setTexture(m_assetManager.getTexture("background"));
    m_background.setScale(2.0f, 2.0f);
    
    // Setup title text
    m_titleText.setFont(m_assetManager.getFont("main"));
    m_titleText.setString("Flappy Bird");
    m_titleText.setCharacterSize(64);
    m_titleText.setFillColor(sf::Color::White);
    m_titleText.setOutlineColor(sf::Color::Black);
    m_titleText.setOutlineThickness(3);
    
    auto titleBounds = m_titleText.getLocalBounds();
    m_titleText.setPosition(400 - titleBounds.width / 2, 150);
    
    // Setup play text
    m_playText.setFont(m_assetManager.getFont("pixel"));
    m_playText.setString("Press SPACE to Play");
    m_playText.setCharacterSize(24);
    m_playText.setFillColor(sf::Color::Yellow);
    
    auto playBounds = m_playText.getLocalBounds();
    m_playText.setPosition(400 - playBounds.width / 2, 350);
    
    // Setup instruction text
    m_instructionText.setFont(m_assetManager.getFont("pixel"));
    m_instructionText.setString("Press SPACE to jump");
    m_instructionText.setCharacterSize(18);
    m_instructionText.setFillColor(sf::Color::White);
    
    auto instrBounds = m_instructionText.getLocalBounds();
    m_instructionText.setPosition(400 - instrBounds.width / 2, 450);
    
    m_backgroundMusic = &m_assetManager.getMusic("background");
}

void MenuState::handleInput(const sf::Event& event, GameStateManager& stateManager) {
    if (event.is<sf::Event::KeyPressed>()) {
        const auto& keyEvent = event.get<sf::Event::KeyPressed>();
        if (keyEvent.code == sf::Keyboard::Key::Space) {
            stateManager.changeState(std::make_unique<PlayState>(m_assetManager));
        }
    }
}

void MenuState::update(float deltaTime, GameStateManager& stateManager) {
    m_playTextBlink += deltaTime;
    if (m_playTextBlink >= 0.5f) {
        m_showPlayText = !m_showPlayText;
        m_playTextBlink = 0.0f;
    }
}

void MenuState::render(sf::RenderWindow& window) {
    window.draw(m_background);
    window.draw(m_titleText);
    if (m_showPlayText) {
        window.draw(m_playText);
    }
    window.draw(m_instructionText);
}

void MenuState::onEnter() {
    m_backgroundMusic->setLoop(true);
    m_backgroundMusic->setVolume(50);
    m_backgroundMusic->play();
}