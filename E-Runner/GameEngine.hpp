#pragma once
#include <SFML/Graphics.hpp>

#include <vector>

#include "runner.hpp"
#include "MEDIA_operator.hpp"

class GameEngine
{
	sf::RenderWindow *targetWindow;
	sf::View camera;
	runner player;
	sf::Sprite gameBackground;

	//std::vector <object> objects;
	//std::vector <money> moneys;

	bool engine_is_prepared;

	//IO_operator score_operator;
	MEDIA_operator media_container;
public:
	void configureEngine(sf::RenderWindow &twindow, sf::Vector2u windowSize,
		unsigned int framerate);
	bool checkEngine();
	void Start();

	GameEngine();
	~GameEngine();
private:
	int gameLoop();
	void drawGameArea();

	int EventManager();
	int KeyboardEventManager();

	//void dataCleaner();
};