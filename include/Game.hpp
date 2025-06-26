#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <memory>
#include "GameStateManager.hpp"
#include "AssetManager.hpp"

class Game {
public:
    Game();
    ~Game() = default;

    void run();

private:
    void processEvents();
    void update(float deltaTime);
    void render();

    sf::RenderWindow m_window;
    std::unique_ptr<GameStateManager> m_stateManager;
    std::unique_ptr<AssetManager> m_assetManager;
    sf::Clock m_clock;
    
    static const int WINDOW_WIDTH = 800;
    static const int WINDOW_HEIGHT = 600;
};