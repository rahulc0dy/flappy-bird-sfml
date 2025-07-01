#include "Pipe.hpp"

const float Pipe::PIPE_SPEED = 200.0f;

Pipe::Pipe(sf::RenderWindow &window, AssetManager &assetManager, float x, float gapY, float gapSize)
    : m_window(window),
      m_assetManager(assetManager),
      m_topPipe(m_assetManager.getTexture("pipe")),
      m_bottomPipe(m_assetManager.getTexture("pipe")),
      m_x(x),
      m_gapY(gapY),
      m_gapSize(gapSize) {
    // Get window dimensions for dynamic scaling
    sf::Vector2u windowSize = m_window.getSize();
    float windowHeight = static_cast<float>(windowSize.y);

    // Calculate pipe dimensions based on window size
    m_pipeWidth = windowSize.x * 0.065f; // 6.5% of window width
    m_pipeHeight = windowHeight * 0.533f; // 53.3% of window height

    m_topPipe.setTextureRect(sf::IntRect(
            {64, 0},
            {32, 80})
    );
    m_bottomPipe.setTextureRect(sf::IntRect(
            {64, 0},
            {32, 80})
    );

    // Calculate scale based on desired pipe dimensions
    sf::Vector2u textureSize = m_topPipe.getTexture().getSize();
    float scaleX = m_pipeWidth / 32.0f; // 32 is the texture width
    float scaleY = m_pipeHeight / 80.0f; // 80 is the texture height

    // Scale pipes
    m_topPipe.setScale({scaleX, scaleY});
    m_bottomPipe.setScale({scaleX, scaleY});

    // Position top pipe (flipped)
    m_topPipe.setOrigin({0, m_pipeHeight});
    m_topPipe.setScale({scaleX, -scaleY});
    m_topPipe.setPosition({m_x, m_gapY - m_gapSize / 2});

    // Position bottom pipe
    m_bottomPipe.setPosition({m_x, m_gapY + m_gapSize / 2});
}

void Pipe::update(float deltaTime) {
    m_x -= PIPE_SPEED * deltaTime;

    m_topPipe.setPosition({m_x, m_gapY - m_gapSize / 2});
    m_bottomPipe.setPosition({m_x, m_gapY + m_gapSize / 2});
}

void Pipe::render() {
    m_window.draw(m_topPipe);
    m_window.draw(m_bottomPipe);
}

sf::FloatRect Pipe::getTopBounds() const {
    return m_topPipe.getGlobalBounds();
}

sf::FloatRect Pipe::getBottomBounds() const {
    return m_bottomPipe.getGlobalBounds();
}

bool Pipe::isOffScreen() const {
    return m_x + m_pipeWidth < 0;
}

bool Pipe::hasPassedPlayer(float playerX) const {
    return m_x + m_pipeWidth < playerX;
}
