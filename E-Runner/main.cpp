#include <SFML/Graphics.hpp>

#include "StartMenu.hpp"

int main()
{
	sf::RenderWindow Window;
	Window.create(sf::VideoMode(1024, 968, 32), "E-Runner", sf::Style::Default);
	Window.setFramerateLimit(60);
	StartMenu menuStart;
	menuStart.create(Window);

	while (Window.isOpen())
	{
		sf::Event event;

		while (Window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				Window.close();
		}

		switch (menuStart.MenuEvents())
		{
		case 10:
			Window.close();
			break;
		case 5:
			Window.close();
			break;
		case 1:
			//GameEngine.start();
			break;
		case 2:
			//BestRuns.menu_Start();
			break;
		case 3:
			Window.close();
			break;
		}

		menuStart.draw();
	}
	return EXIT_SUCCESS;
}