#pragma once

#include "button.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>

class StartMenu
{
	button StartGame;
	button BestRuns;
	button Exit;

	sf::Sprite backgroundImage;
	sf::Text gameName;
	sf::RenderWindow *Pwindow;
	sf::Font SMenuFont;

public:
	int MenuEvents();
	void draw();
	void create(sf::RenderWindow &targetW);

	StartMenu();
	~StartMenu();
};