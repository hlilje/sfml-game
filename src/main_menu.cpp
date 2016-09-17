#include "stdafx.hpp"
#include "main_menu.hpp"
#include "service_locator.hpp"


MainMenu::MenuResult MainMenu::Show(sf::RenderWindow & window) {
    sf::Texture texture;
    if (!texture.loadFromFile("img/mainMenu.png"))
        std::cout << "Error loading main menu image\n";
    sf::Sprite sprite(texture);

    // Play menu item coordinates
    MenuItem play_button;
    play_button.rect.top= 145;
    play_button.rect.height = 380;
    play_button.rect.left = 0;
    play_button.rect.width = 1023;
    play_button.action = Play;
    play_button.alt_key = sf::Keyboard::S;

    // Exit menu item coordinates
    MenuItem exit_button;
    exit_button.rect.left = 0;
    exit_button.rect.height = 1023;
    exit_button.rect.top = 383;
    exit_button.rect.width = 560;
    exit_button.action = Exit;
    exit_button.alt_key = sf::Keyboard::Escape;

    _menu_items.push_back(play_button);
    _menu_items.push_back(exit_button);

    window.clear();
    window.draw(sprite);
    window.display();

    return GetMenuResponse(window);
}

MainMenu::MenuResult MainMenu::HandleClick(const int x, const int y) {
    for (std::list<MenuItem>::iterator it = _menu_items.begin();
         it != _menu_items.end(); it++) {
        sf::Rect<int> menuItemRect = (*it).rect;
        if((menuItemRect.height > y
            && menuItemRect.top < y
            && menuItemRect.left < x
            && menuItemRect.width > x)
            || sf::Keyboard::isKeyPressed((*it).alt_key)) {
            return (*it).action;
        }
    }

    return Nothing;
}

MainMenu::MenuResult MainMenu::GetMenuResponse(sf::RenderWindow & window) {
    sf::Event menuEvent;

    while (true) {
        while (window.pollEvent(menuEvent)) {
            if (menuEvent.type == sf::Event::MouseButtonPressed ||
                menuEvent.type == sf::Event::KeyPressed) {
                if (ServiceLocator::GetAudio()->IsSongPlaying())
                    ServiceLocator::GetAudio()->StopAllSounds();

                return HandleClick(menuEvent.mouseButton.x, menuEvent.mouseButton.y);
            }

            if (menuEvent.type == sf::Event::Closed) {
                return Exit;
            }
        }
    }
}
