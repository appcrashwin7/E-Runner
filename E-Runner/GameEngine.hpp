#pragma once
#include <SFML/Graphics.hpp>

#include <vector>
#include <random>

#include "runner.hpp"
#include "MEDIA_operator.hpp"
#include "gameGUI.hpp"
#include "obstacle.hpp"
#include "money.hpp"

class GameEngine
{
	std::default_random_engine rand_engine;

	sf::Font gameFont;
	sf::Sprite gameBackground;

	sf::RenderWindow *targetWindow;
	sf::View camera;
	gameGUI HUD;

	runner player;
	std::vector <obstacle> obstacles;
	std::vector <money> moneys;

	bool engine_is_prepared;
	bool engine_is_paused;

	//IO_operator score_operator;
	MEDIA_operator media_container;

	int points;
	bool playerIsAlive;

public:
	void configureEngine(sf::RenderWindow &twindow, sf::Vector2u windowSize,
		unsigned int framerate);
	void Start();

	GameEngine();
	~GameEngine();
private:
	bool checkEngine();
	int gameLoop();	
	void setCameraPos();
	bool loseLoop();

	void objectDraw();
	void drawGameArea();

	int EventManager();
	void KeyboardEventManager(float speedMod);
	bool colisionManager();

	void objectGenerator();
	void dataCleaner();
};