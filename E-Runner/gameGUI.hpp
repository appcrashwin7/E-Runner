#pragma once

#include "button.hpp"
#include <SFML/Graphics.hpp>


class gameGUI
{
	sf::Text score;
	sf::Text information;
	sf::Text youLose;

	button continueb;
	button exit;

public:
	gameGUI();
	~gameGUI();

	void create(sf::RenderWindow *targetWindow, sf::Font *font);
	void setScore(int newScore);

	void setNewGUIElementsPos(sf::RenderWindow *window);

	unsigned int getEvent(sf::RenderWindow *targetWindow);
	
	void drawGameGUI(sf::RenderWindow *targetWindow,bool isgamePaused);

	void drawGUIWhenPlayerLose(sf::RenderWindow *targetWindow);
};