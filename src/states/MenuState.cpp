#include "MenuState.hpp"
#include "PlayState.hpp"
#include "GameStateManager.hpp"
#include <SFML/Window/Event.hpp>

MenuState::MenuState(sf::RenderWindow& window, AssetManager &assetManager)
    : GameState(window),
      m_assetManager(assetManager),
      m_backgroundMusic(&assetManager.getMusic("background")),
      m_background(m_assetManager.getTexture("background")),
      m_titleText(m_assetManager.getFont("main")),
      m_playText(m_assetManager.getFont("pixel")),
      m_instructionText(m_assetManager.getFont("pixel")),
      m_playTextBlink(0.0f),
      m_showPlayText(true) {
    
    // Get window dimensions for dynamic sizing and positioning
    sf::Vector2u windowSize = m_window.getSize();
    float windowWidth = static_cast<float>(windowSize.x);
    float windowHeight = static_cast<float>(windowSize.y);
    
    // Setup background
    m_background.setTexture(m_assetManager.getTexture("background"));
    
    // Scale background to fit window
    sf::Vector2u bgTextureSize = m_background.getTexture()->getSize();
    float bgScaleX = windowWidth / static_cast<float>(bgTextureSize.x);
    float bgScaleY = windowHeight / static_cast<float>(bgTextureSize.y);
    m_background.setScale({bgScaleX, bgScaleY});
    
    // Setup title text
    m_titleText.setFont(m_assetManager.getFont("main"));
    m_titleText.setString("Flappy Bird");
    
    unsigned int titleFontSize = static_cast<unsigned int>(windowHeight * 0.107f); // 10.7% of window height
    m_titleText.setCharacterSize(titleFontSize);
    m_titleText.setFillColor(sf::Color::White);
    m_titleText.setOutlineColor(sf::Color::Black);
    m_titleText.setOutlineThickness(windowHeight * 0.005f); // 0.5% of window height

    auto titleBounds = m_titleText.getLocalBounds();
    m_titleText.setPosition({(windowWidth - titleBounds.size.x) / 2, windowHeight * 0.25f});

    // Setup play text
    m_playText.setFont(m_assetManager.getFont("pixel"));
    m_playText.setString("Press SPACE to Play");
    
    unsigned int playFontSize = static_cast<unsigned int>(windowHeight * 0.04f); // 4% of window height
    m_playText.setCharacterSize(playFontSize);
    m_playText.setFillColor(sf::Color::Yellow);

    auto playBounds = m_playText.getLocalBounds();
    m_playText.setPosition({(windowWidth - playBounds.size.x) / 2, windowHeight * 0.583f});

    // Setup instruction text
    m_instructionText.setFont(m_assetManager.getFont("pixel"));
    m_instructionText.setString("Press SPACE to jump");
    
    unsigned int instrFontSize = static_cast<unsigned int>(windowHeight * 0.03f); // 3% of window height
    m_instructionText.setCharacterSize(instrFontSize);
    m_instructionText.setFillColor(sf::Color::White);

    auto instrBounds = m_instructionText.getLocalBounds();
    m_instructionText.setPosition({(windowWidth - instrBounds.size.x) / 2, windowHeight * 0.75f});

    m_backgroundMusic = &m_assetManager.getMusic("background");
}

void MenuState::handleInput(const sf::Event &event, GameStateManager &stateManager) {
    if (event.is<sf::Event::KeyPressed>()) {
        const auto &keyEvent = event.getIf<sf::Event::KeyPressed>();
        if (keyEvent->code == sf::Keyboard::Key::Space) {
            stateManager.changeState(std::make_unique<PlayState>(m_window, m_assetManager));
        }
    }
}

void MenuState::update(float deltaTime, GameStateManager &stateManager) {
    m_playTextBlink += deltaTime;
    if (m_playTextBlink >= 0.5f) {
        m_showPlayText = !m_showPlayText;
        m_playTextBlink = 0.0f;
    }
}

void MenuState::render() {
    m_window.draw(m_background);
    m_window.draw(m_titleText);
    if (m_showPlayText) {
        m_window.draw(m_playText);
    }
    m_window.draw(m_instructionText);
}

void MenuState::onEnter() {
    m_backgroundMusic->setLooping(true);
    m_backgroundMusic->setVolume(50);
    m_backgroundMusic->play();
}