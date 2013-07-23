#include "stdafx.h"
#include "SplashScreen.h"

void SplashScreen::Show(sf::RenderWindow& renderWindow)
{
	sf::Texture texture;
	// Error handling
	if(texture.loadFromFile("img/splashScreen.png") != true)
	{
		std::cout << "Error loading splash screen image\n";
		return;
	}

	sf::Sprite sprite(texture);

	renderWindow.draw(sprite);
	renderWindow.display();

	sf::Event event;
	while(true)
	{
		// All windows are responsible for their own event handling
		while(renderWindow.pollEvent(event))
		{
			// Close the splash scren window upon any of these events
			if(event.type == sf::Event::EventType::KeyPressed 
				|| event.type == sf::Event::EventType::MouseButtonPressed
				|| event.type == sf::Event::EventType::Closed )
			{
				return;
			}
		}
	}
}
