#pragma once
#include <SFML/Graphics.hpp>
#include "AssetManager.hpp"

class ScoreManager {
public:
    ScoreManager(sf::RenderWindow& window, AssetManager& assetManager);
    ~ScoreManager() = default;

    void render();
    void addScore(int points = 1);
    void reset();
    
    int getCurrentScore() const { return m_currentScore; }
    int getBestScore() const { return m_bestScore; }

private:
    void updateScoreText();
    void saveBestScore();
    void loadBestScore();

    sf::RenderWindow& m_window;
    AssetManager& m_assetManager;
    sf::Text m_scoreText;
    
    int m_currentScore;
    int m_bestScore;
};