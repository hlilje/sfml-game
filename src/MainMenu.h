// Main menu state.

#pragma once

// Ideally you would want a generic Menu class to inherit from
class MainMenu
{
public:
	// MenuResult and MenuItem is defined inside MainMenu since they will only
	// be used in this context, and defining them globally would make no sense.
	enum MenuResult { Nothing, Exit, Play };  

	// Represents an item in the menu with its own action.
	// Structs defaults to public, unlike class.
	struct MenuItem
	{
	public:
		sf::Rect<int> rect; // Holds the dimensions of the item
		MenuResult action;
		sf::Keyboard::Key altKey; // Stores an alt. key to toggle the item
	};

	MenuResult Show(sf::RenderWindow&);

private:
	MenuResult GetMenuResponse(sf::RenderWindow& window);
	MenuResult HandleClick(int x, int y);
	std::list<MenuItem> _menuItems;
};
