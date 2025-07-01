#include "ScoreManager.hpp"
#include <fstream>
#include <iostream>

ScoreManager::ScoreManager(sf::RenderWindow& window, AssetManager &assetManager)
    : m_window(window),
      m_assetManager(assetManager),
      m_scoreText(m_assetManager.getFont("pixel")),
      m_currentScore(0),
      m_bestScore(0) {
    m_scoreText.setFont(m_assetManager.getFont("pixel"));
    m_scoreText.setCharacterSize(32);
    m_scoreText.setFillColor(sf::Color::White);
    m_scoreText.setOutlineColor(sf::Color::Black);
    m_scoreText.setOutlineThickness(2);

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
    auto bounds = m_scoreText.getLocalBounds();
    m_scoreText.setPosition({400 - bounds.size.x / 2, 50});
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