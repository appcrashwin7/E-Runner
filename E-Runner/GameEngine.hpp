#pragma once
#include <SFML/Graphics.hpp>

#include <vector>
#include <random>

#include "runner.hpp"
#include "MEDIA_operator.hpp"
#include "gameGUI.hpp"
#include "obstacle.hpp"
#include "money.hpp"
#include "back_obstacle.hpp"

class GameEngine
{
	std::default_random_engine rand_engine;

	sf::Font gameFont;

	sf::RenderWindow *targetWindow;
	sf::View camera;
	gameGUI HUD;

	runner player;
	std::vector <obstacle> obstacles;
	std::vector <money> moneys;
	back_obstacle walls[2];

	bool engine_is_paused;

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
	int gameLoop();	
	void setCameraPos();
	bool loseLoop(sf::Event &events);
	void addSomePoint();

	void objectDraw();
	void drawGameArea();

	int EventManager(sf::Event &windowEvent);
	void KeyboardEventManager(float speedMod);
	bool colisionManager();
	bool IsNotCollision(sf::Vector2f objPos, sf::Vector2f objSize);

	void objectGenerator();
	void dataCleaner();
	void setWallPosition();
};