#include <SFML/Graphics.hpp>

#include "StartMenu.hpp"
#include "GameEngine.hpp"
#include "BestRunsRanks.hpp"

int main()
{
	sf::RenderWindow Window;
	Window.create(sf::VideoMode(1024, 768, 32), "E-Runner", sf::Style::Default);
	Window.setFramerateLimit(30);
	StartMenu menuStart;
	menuStart.create(Window);

	while (true)
	{
		sf::Event event;

		while (Window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				return 1;
		}

		switch (menuStart.MenuEvents())
		{
		case 10:
			return 1;
			break;
		case 5:
			return 1;
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
		{
			BestRunsRank *rank = new BestRunsRank();
			rank->Loop(&Window);
			delete rank;
			break;
		}
		case 3:
			return 1;
			break;
		}

		menuStart.draw();
	}
	return EXIT_SUCCESS;
}