#include "PipeManager.hpp"
#include <random>

const float PipeManager::SPAWN_INTERVAL = 2.0f;
const float PipeManager::GAP_SIZE = 120.0f;

PipeManager::PipeManager(sf::RenderWindow& window, AssetManager &assetManager)
    : m_window(window),
      m_assetManager(assetManager),
      m_spawnTimer(0.0f),
      m_lastScoredPipe(-1) {
    
    // Calculate dynamic values based on window size
    sf::Vector2u windowSize = m_window.getSize();
    float windowHeight = static_cast<float>(windowSize.y);
    
    // Set gap Y limits based on window height
    m_minGapY = windowHeight * 0.25f; // 25% from top
    m_maxGapY = windowHeight * 0.75f; // 75% from top
}

void PipeManager::update(float deltaTime) {
    // Update existing pipes
    for (auto &pipe: m_pipes) {
        pipe->update(deltaTime);
    }

    // Remove off-screen pipes
    m_pipes.erase(
        std::remove_if(m_pipes.begin(), m_pipes.end(),
                       [](const std::unique_ptr<Pipe> &pipe) {
                           return pipe->isOffScreen();
                       }),
        m_pipes.end()
    );

    // Spawn new pipes
    m_spawnTimer += deltaTime;
    if (m_spawnTimer >= SPAWN_INTERVAL) {
        spawnPipe();
        m_spawnTimer = 0.0f;
    }
}

void PipeManager::render() {
    for (const auto &pipe: m_pipes) {
        pipe->render();
    }
}

void PipeManager::reset() {
    m_pipes.clear();
    m_spawnTimer = 0.0f;
    m_lastScoredPipe = -1;
}

bool PipeManager::checkCollision(const sf::FloatRect &playerBounds) const {
    for (const auto &pipe: m_pipes) {
        if (playerBounds.findIntersection(pipe->getTopBounds()) ||
            playerBounds.findIntersection(pipe->getBottomBounds())) {
            return true;
        }
    }
    return false;
}

int PipeManager::checkScoring(float playerX) {
    int newScores = 0;

    for (size_t i = 0; i < m_pipes.size(); ++i) {
        if (static_cast<int>(i) > m_lastScoredPipe && m_pipes[i]->hasPassedPlayer(playerX)) {
            newScores++;
            m_lastScoredPipe = static_cast<int>(i);
        }
    }

    return newScores;
}

void PipeManager::spawnPipe() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(m_minGapY, m_maxGapY);

    float gapY = dis(gen);
    sf::Vector2u windowSize = m_window.getSize();
    float spawnX = static_cast<float>(windowSize.x) + 50.0f; // Spawn just off-screen
    
    m_pipes.push_back(std::make_unique<Pipe>(m_window, m_assetManager, spawnX, gapY, GAP_SIZE));
}