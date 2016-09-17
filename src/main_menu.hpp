#pragma once


class MainMenu {
public:
    enum MenuResult {
        Exit,
        Nothing,
        Play
    };  

    struct MenuItem {
        sf::Rect<int> rect;
        MenuResult action;
        sf::Keyboard::Key alt_key;
    };

private:
    std::list<MenuItem> _menu_items;

    MenuResult GetMenuResponse(sf::RenderWindow & window);
    MenuResult HandleClick(const int x, const int y);

public:
    MenuResult Show(sf::RenderWindow & window);
};
