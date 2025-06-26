#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

int main() {
    // Create the main window
    sf::RenderWindow window(sf::VideoMode({800, 600}), "SFML window",
                            sf::Style::Close | sf::Style::Titlebar | sf::Style::Resize);

    // Load a sprite to display
    const sf::Texture texture("assets/sprites/Player/StyleBird1/Bird1-1.png");
    const int frameWidth = 16;
    const int frameHeight = 16;
    const int frameCount = 4;
    sf::Sprite sprite(texture);
    sprite.setScale({2, 2});
    sprite.setPosition(sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2));

    const sf::Font font("assets/fonts/MegamaxJonathanToo.ttf");
    const sf::Text text(font, "Flappy", 50);

    sf::Music music("assets/sounds/background-music.mp3");

    music.play();

    int currentFrame = 0;
    sf::Clock frameClock;
    const float frameDuration = 0.1f; // Duration of each frame in seconds

    // Start the game loop
    while (window.isOpen()) {
        // Process events
        while (const std::optional event = window.pollEvent()) {
            // Close window: exit
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        // Update properties
        if (frameClock.getElapsedTime().asSeconds() > frameDuration) {
            currentFrame = (currentFrame + 1) % frameCount;
            sprite.setTextureRect(sf::IntRect(
                    {currentFrame * frameWidth, 0},
                    {frameWidth, frameHeight})
            );
            frameClock.restart();
        }

        // Draw
        window.clear();
        window.draw(sprite);
        window.draw(text);
        window.display();
    }

    return 0;
}
