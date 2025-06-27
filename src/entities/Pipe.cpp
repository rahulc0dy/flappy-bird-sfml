#include "Pipe.hpp"

const float Pipe::PIPE_SPEED = 200.0f;
const float Pipe::PIPE_WIDTH = 52.0f;
const float Pipe::PIPE_HEIGHT = 320.0f;

Pipe::Pipe(AssetManager &assetManager, float x, float gapY, float gapSize)
    : m_assetManager(assetManager),
      m_topPipe(m_assetManager.getTexture("pipe")),
      m_bottomPipe(m_assetManager.getTexture("pipe")),
      m_x(x),
      m_gapY(gapY),
      m_gapSize(gapSize) {
    m_topPipe.setTextureRect(sf::IntRect(
            {64, 0},
            {32, 80})
    );
    m_bottomPipe.setTextureRect(sf::IntRect(
            {64, 0},
            {32, 80})
    );

    // Scale pipes
    m_topPipe.setScale({2.0f, 2.0f});
    m_bottomPipe.setScale({2.0f, 2.0f});

    // Position top pipe (flipped)
    m_topPipe.setOrigin({0, PIPE_HEIGHT});
    m_topPipe.setScale({2.0f, -2.0f});
    m_topPipe.setPosition({m_x, m_gapY - m_gapSize / 2});

    // Position bottom pipe
    m_bottomPipe.setPosition({m_x, m_gapY + m_gapSize / 2});
}

void Pipe::update(float deltaTime) {
    m_x -= PIPE_SPEED * deltaTime;

    m_topPipe.setPosition({m_x, m_gapY - m_gapSize / 2});
    m_bottomPipe.setPosition({m_x, m_gapY + m_gapSize / 2});
}

void Pipe::render(sf::RenderWindow &window) {
    window.draw(m_topPipe);
    window.draw(m_bottomPipe);
}

sf::FloatRect Pipe::getTopBounds() const {
    return m_topPipe.getGlobalBounds();
}

sf::FloatRect Pipe::getBottomBounds() const {
    return m_bottomPipe.getGlobalBounds();
}

bool Pipe::isOffScreen() const {
    return m_x + PIPE_WIDTH * 2 < 0;
}

bool Pipe::hasPassedPlayer(float playerX) const {
    return m_x + PIPE_WIDTH < playerX;
}
