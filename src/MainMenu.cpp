#include "stdafx.h"
#include "MainMenu.h"
#include "ServiceLocator.h"

MainMenu::MenuResult MainMenu::Show(sf::RenderWindow& window)
{
	sf::Texture texture;
	if(texture.loadFromFile("img/mainMenu.png") != true)
	{
		std::cout << "Error loading main menu image\n";
		// Can't just return since it must return a value
	}
	sf::Sprite sprite(texture);

	// Setup clickable regions

	// Play menu item coordinates
	MenuItem playButton;
	playButton.rect.top= 145;
	playButton.rect.height = 380;
	playButton.rect.left = 0;
	playButton.rect.width = 1023;
	playButton.action = Play;
	playButton.altKey = sf::Keyboard::S;

	// Exit menu item coordinates
	MenuItem exitButton;
	exitButton.rect.left = 0;
	exitButton.rect.height = 1023;
	exitButton.rect.top = 383;
	exitButton.rect.width = 560;
	exitButton.action = Exit;
	exitButton.altKey = sf::Keyboard::Escape;

	_menuItems.push_back(playButton);
	_menuItems.push_back(exitButton);

	window.clear();
	window.draw(sprite);
	window.display();

	return GetMenuResponse(window);
}

MainMenu::MenuResult MainMenu::HandleClick(int x, int y)
{
	std::list<MenuItem>::iterator it;

	for (it = _menuItems.begin(); it != _menuItems.end(); it++)
	{
		sf::Rect<int> menuItemRect = (*it).rect;
		if((menuItemRect.height > y
			&& menuItemRect.top < y
			&& menuItemRect.left < x
			&& menuItemRect.width > x)
			|| sf::Keyboard::isKeyPressed((*it).altKey))
		{
			return (*it).action;
		}
	}

	return Nothing;
}

MainMenu::MenuResult MainMenu::GetMenuResponse(sf::RenderWindow& window)
{
	sf::Event menuEvent;

	while(true)
	{
		while(window.pollEvent(menuEvent))
		{
			if(menuEvent.type == sf::Event::MouseButtonPressed ||
				menuEvent.type == sf::Event::KeyPressed)
			{
				if(ServiceLocator::GetAudio()->IsSongPlaying())
					ServiceLocator::GetAudio()->StopAllSounds();

				return HandleClick(menuEvent.mouseButton.x, menuEvent.mouseButton.y);
			}

			if(menuEvent.type == sf::Event::Closed)
			{
				return Exit;
			}
		}
	}
}
