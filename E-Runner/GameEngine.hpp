#pragma once
#include <SFML/Graphics.hpp>

#include <vector>

#include "runner.hpp"
#include "MEDIA_operator.hpp"
#include "gameGUI.hpp"

class GameEngine
{
	sf::Font gameFont;
	sf::RenderWindow *targetWindow;
	sf::View camera;
	runner player;
	sf::Sprite gameBackground;
	gameGUI HUD;

	//std::vector <object> objects;
	//std::vector <money> moneys;

	bool engine_is_prepared;
	bool engine_is_paused;

	//IO_operator score_operator;
	MEDIA_operator media_container;

public:
	void configureEngine(sf::RenderWindow &twindow, sf::Vector2u windowSize,
		unsigned int framerate);
	void Start();

	GameEngine();
	~GameEngine();
private:
	int gameLoop();
	void drawGameArea();
	void setCameraPos();

	int EventManager();
	int KeyboardEventManager();

	bool checkEngine();

	bool colisionManager();
	//void dataCleaner();
};