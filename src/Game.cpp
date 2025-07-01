#include "Game.hpp"
#include "MenuState.hpp"

Game::Game()
    : m_window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Flappy Bird",
               sf::Style::Close | sf::Style::Titlebar)
      , m_assetManager(std::make_unique<AssetManager>(m_window))
      , m_stateManager(std::make_unique<GameStateManager>(m_window, *m_assetManager)) {
    m_window.setFramerateLimit(120);

    // Load all assets
    m_assetManager->loadTexture("bird", "assets/sprites/Player/StyleBird1/Bird1-1.png");
    m_assetManager->loadTexture("background", "assets/sprites/Background/Background1.png");
    m_assetManager->loadTexture("pipe", "assets/sprites/Tiles/Style 1/PipeStyle1.png");
    m_assetManager->loadTexture("ground", "assets/sprites/Tiles/Style 1/TileStyle1.png");

    m_assetManager->loadFont("main", "assets/fonts/MegamaxJonathanToo.ttf");
    m_assetManager->loadFont("pixel", "assets/fonts/SuperPixel.ttf");

    m_assetManager->loadMusic("background", "assets/sounds/background-music.mp3");
    m_assetManager->loadSound("jump", "assets/sounds/jump-sound.wav");
    m_assetManager->loadSound("hit", "assets/sounds/fall-sound.wav");
    m_assetManager->loadSound("score", "assets/sounds/score-sound.wav");

    // Start with menu state
    m_stateManager->pushState(std::make_unique<MenuState>(m_window, *m_assetManager));
}

void Game::run() {
    while (m_window.isOpen() && !m_stateManager->isEmpty()) {
        float deltaTime = m_clock.restart().asSeconds();

        processEvents();
        update(deltaTime);
        render();
    }
}

void Game::processEvents() {
    while (const std::optional event = m_window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            m_window.close();
        }

        m_stateManager->handleInput(*event);
    }
}

void Game::update(float deltaTime) {
    m_stateManager->update(deltaTime);
}

void Game::render() {
    m_window.clear(sf::Color::Cyan);
    m_stateManager->render();
    m_window.display();
}