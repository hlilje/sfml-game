#include "stdafx.hpp"
#include "win_screen.hpp"


void WinScreen::Show(sf::RenderWindow & window) {
    sf::Texture texture;
    if (!texture.loadFromFile("img/winScreen.png")) {
        std::cout << "Error loading win screen image" << std::endl;
        return;
    }

    sf::Sprite sprite(texture);

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
