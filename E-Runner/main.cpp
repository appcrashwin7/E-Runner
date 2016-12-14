#include <SFML/Graphics.hpp>

#include "StartMenu.hpp"
#include "GameEngine.hpp"

int main()
{
	sf::RenderWindow Window;
	Window.create(sf::VideoMode(1024, 768, 32), "E-Runner", sf::Style::Default);
	Window.setFramerateLimit(30);
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
		{
			GameEngine *game = new GameEngine();
			game->configureEngine(Window, sf::Vector2u(1024, 768), 30);
			game->Start();
			delete game;
			break;
		}
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