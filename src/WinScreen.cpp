#include "stdafx.h"
#include "WinScreen.h"

void WinScreen::Show(sf::RenderWindow& renderWindow)
{
	sf::Texture texture;
	if(texture.loadFromFile("img/winScreen.png") != true)
	{
		std::cout << "Error loading win screen image" << std::endl;
		return;
	}

	sf::Sprite sprite(texture);

	renderWindow.draw(sprite);
	renderWindow.display();

	sf::Event event;
	while(true)
	{
		while(renderWindow.pollEvent(event))
		{
			if(event.type == sf::Event::EventType::KeyPressed 
				|| event.type == sf::Event::EventType::MouseButtonPressed
				|| event.type == sf::Event::EventType::Closed )
			{
				return;
			}
		}
	}
}
