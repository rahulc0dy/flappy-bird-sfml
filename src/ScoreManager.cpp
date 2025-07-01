#include "ScoreManager.hpp"
#include <fstream>
#include <iostream>

ScoreManager::ScoreManager(sf::RenderWindow& window, AssetManager &assetManager)
    : m_window(window),
      m_assetManager(assetManager),
      m_scoreText(m_assetManager.getFont("pixel")),
      m_currentScore(0),
      m_bestScore(0) {
    
    // Get window dimensions for dynamic sizing
    sf::Vector2u windowSize = m_window.getSize();
    float windowWidth = static_cast<float>(windowSize.x);
    float windowHeight = static_cast<float>(windowSize.y);
    
    m_scoreText.setFont(m_assetManager.getFont("pixel"));
    
    // Calculate font size based on window size
    unsigned int fontSize = static_cast<unsigned int>(windowHeight * 0.053f); // 5.3% of window height
    m_scoreText.setCharacterSize(fontSize);
    
    m_scoreText.setFillColor(sf::Color::White);
    m_scoreText.setOutlineColor(sf::Color::Black);
    
    // Calculate outline thickness based on window size
    float outlineThickness = windowHeight * 0.003f; // 0.3% of window height
    m_scoreText.setOutlineThickness(outlineThickness);

    loadBestScore();
    updateScoreText();
}

void ScoreManager::render() {
    m_window.draw(m_scoreText);
}

void ScoreManager::addScore(int points) {
    m_currentScore += points;
    if (m_currentScore > m_bestScore) {
        m_bestScore = m_currentScore;
        saveBestScore();
    }
    updateScoreText();
}

void ScoreManager::reset() {
    m_currentScore = 0;
    updateScoreText();
}

void ScoreManager::updateScoreText() {
    m_scoreText.setString(std::to_string(m_currentScore));
    
    // Center the score text horizontally at the top of the window
    sf::Vector2u windowSize = m_window.getSize();
    float windowWidth = static_cast<float>(windowSize.x);
    float windowHeight = static_cast<float>(windowSize.y);
    
    auto bounds = m_scoreText.getLocalBounds();
    float x = (windowWidth - bounds.size.x) / 2.0f;
    float y = windowHeight * 0.083f; // 8.3% from top
    
    m_scoreText.setPosition({x, y});
}

void ScoreManager::saveBestScore() {
    std::ofstream file("best_score.txt");
    if (file.is_open()) {
        file << m_bestScore;
        file.close();
    }
}

void ScoreManager::loadBestScore() {
    std::ifstream file("best_score.txt");
    if (file.is_open()) {
        file >> m_bestScore;
        file.close();
    }
}