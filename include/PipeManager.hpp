#pragma once
#include <vector>
#include <memory>
#include "Pipe.hpp"
#include "AssetManager.hpp"

class PipeManager {
public:
    PipeManager(sf::RenderWindow& window, AssetManager& assetManager);
    ~PipeManager() = default;

    void update(float deltaTime);
    void render();
    void reset();

    bool checkCollision(const sf::FloatRect& playerBounds) const;
    int checkScoring(float playerX);

private:
    void spawnPipe();

    sf::RenderWindow& m_window;
    AssetManager& m_assetManager;
    std::vector<std::unique_ptr<Pipe>> m_pipes;
    
    float m_spawnTimer;
    int m_lastScoredPipe;
    
    // Dynamic values based on window size
    float m_minGapY;
    float m_maxGapY;
    
    static const float SPAWN_INTERVAL;
    static const float GAP_SIZE;
};