#include "stdafx.hpp"
#include "splash_screen.hpp"


void SplashScreen::Show(sf::RenderWindow & window) {
    sf::Texture texture;
    if (!texture.loadFromFile("img/splashScreen.png")) {
        std::cout << "Error loading splash screen image" << std::endl;
        return;
    }

    const sf::Sprite sprite(texture);

    window.draw(sprite);
    window.display();

    sf::Event event;
    while (true) {
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::EventType::KeyPressed 
                || event.type == sf::Event::EventType::MouseButtonPressed
                || event.type == sf::Event::EventType::Closed ) {
                return;
            }
        }
    }
}
