#include "GameEngine.hpp"
#include "move_type.h"
#include <iostream>

bool isUpKeyPressed()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) == true
		|| sf::Keyboard::isKeyPressed(sf::Keyboard::Up) == true)
	{
		return true;
	}
	return false;
}
bool isLeftKeyPressed()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) == true
		|| sf::Keyboard::isKeyPressed(sf::Keyboard::Left) == true)
	{
		return true;
	}
	return false;
}
bool isRightKeyPressed()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) == true
		|| sf::Keyboard::isKeyPressed(sf::Keyboard::Right) == true)
	{
		return true;
	}
	return false;
}

void GameEngine::configureEngine(sf::RenderWindow & twindow, sf::Vector2u windowSize, unsigned int framerate)
{
	gameFont.loadFromFile("arial.ttf");

	targetWindow = &twindow;
	targetWindow->setSize(windowSize);
	targetWindow->setFramerateLimit(framerate);
	engine_is_paused = false;
	camera.setSize((sf::Vector2f)windowSize);
	HUD.create(targetWindow, &gameFont);

	if(checkEngine() != false)
		this->engine_is_prepared = true;
}

bool GameEngine::checkEngine()
{
	if (targetWindow == nullptr)
	{
		std::cout << "GameEngine::targetWindow is null!" << std::endl;
		return false;
	}
	sf::Vector2u size = targetWindow->getSize();
	if (size.x < 800 || size.y < 600)
	{
		std::cout << "Window size is too small!" << std::endl;
		return false;
	}
	if (size.x > 1920 || size.y > 1080)
	{
		std::cout << "Window size is too big!" << std::endl;
		return false;
	}
	return true;
}

bool GameEngine::colisionManager()
{
	sf::Vector2f playerPos = this->player.getPosition();
	sf::Vector2f playerSize = this->player.getSize();

	if (playerPos.x <= -200.0f)
	{
		playerPos.x = -201.0f;
		this->player.setPosition(playerPos);
	}
	else if (playerPos.x + playerSize.x >= 600.0f)
	{
		float mov = playerPos.x + playerSize.x - 600.0f;
		playerPos.x = playerPos.x - mov;
		this->player.setPosition(playerPos);
	}

	// TODO : add colision with obstacles

	return false;
}

void GameEngine::dataCleaner()
{
	sf::Vector2f obsPos;
	sf::Vector2f playerPos = this->player.getPosition();

	size_t lastObstacle = 0;

	for (size_t i = 0; i < obstacles.size(); i++)
	{
		obsPos = obstacles[i].getPosition();
		if (obsPos.y > playerPos.y + 200)
		{
			lastObstacle = i;
		}
	}
		obstacles.erase(obstacles.begin(),obstacles.begin()+lastObstacle);

		//TODO :add a eraser to moneys vector
}

void GameEngine::Start()
{
	if(engine_is_prepared == true)
		this->gameLoop();
	return;
}

GameEngine::GameEngine()
{}

GameEngine::~GameEngine()
{
	targetWindow = nullptr;
	obstacles.clear();
}

int GameEngine::gameLoop()
{
	float speed = 0.5f;
	int Numloop = 1;
	while (true)
	{
		//events
		if (this->engine_is_paused == true)
		{
			int event = this->EventManager();
			switch (event)
			{
			case 1:
				return 0;
				break;
			case 2:
				break;
			case 3:
				break;
			}
		}
		else
		{
			int event = this->EventManager();
			switch (event)
			{
			case 1:
				return 0;
				break;
			case 2:
				break;
			case 3:
				this->engine_is_paused = true;
				break;
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) == true)
		{
			if (engine_is_paused == true)
			{
				engine_is_paused = false;
			}
			else
			{
				engine_is_paused = true;
			}
		}
		if (engine_is_paused == true)
		{
			switch (HUD.getEvent(targetWindow))
			{
			case 1:
				engine_is_paused = false;
				break;
			case 2:
				targetWindow->close();
				break;
			default:
				break;
			}
		}
		if (this->engine_is_paused == false)
		{
			int keyEvents = this->KeyboardEventManager();
			if (keyEvents == 5)
			{
				this->player.move(move_type::up_and_left, speed);
			}
			else if (keyEvents == 4)
			{
				this->player.move(move_type::up_and_right, speed);
			}
			else if (keyEvents == 3)
			{
				this->player.move(move_type::up, speed);
			}
			else if (keyEvents == 2)
			{
				this->player.move(move_type::left, speed);
			}
			else if (keyEvents == 1)
			{
				this->player.move(move_type::right, speed);
			}
			else
			{
				this->player.move(move_type::other, speed);
			}
			if (Numloop % 200 == 0)
			{
				this->obstacleGenerator();
			}

			colisionManager();

			sf::Vector2f test = this->player.getPosition();
			std::cout << test.x << " " << test.y << "\n";

			setCameraPos();
			targetWindow->setView(camera);
			HUD.setNewGUIElementsPos(targetWindow);

			speed += 0.001f;
			Numloop++;
		}
		
		dataCleaner();

		//graphics
		targetWindow->clear();
		this->drawGameArea();
		if (engine_is_paused == true)
			this->HUD.drawGameGUI(targetWindow, true);
		else
			this->HUD.drawGameGUI(targetWindow);
		obstacleDraw();
		targetWindow->display();
	}
}

void GameEngine::drawGameArea()
{
	targetWindow->draw(player.getShape());
}

void GameEngine::setCameraPos()
{
	sf::Vector2u windowSize = this->targetWindow->getSize();
	sf::Vector2f playerPos = this->player.getPosition();

	sf::Vector2f newCameraPos = playerPos;
	float sizeY = (float)windowSize.y / 4;
	newCameraPos.y -= sizeY;
	newCameraPos.x = 200;
	camera.setCenter(newCameraPos);
}

void GameEngine::obstacleGenerator()
{
	sf::Vector2f pos = player.getPosition();
	pos.y -= 500;
	obstacles.push_back(obstacle::obstacle(pos));
	pos.x += 100;
	obstacles.push_back(obstacle::obstacle(pos));
}

void GameEngine::obstacleDraw()
{
	for (size_t i = 0; i < obstacles.size(); i++)
	{
		targetWindow->draw(*obstacles[i].getObstacleShape());
	}
}

int GameEngine::EventManager()
{
	sf::Event windowEvent;

	targetWindow->pollEvent(windowEvent);

	switch (windowEvent.type)
	{
	case sf::Event::Closed :
		return 1;
		break;
	case sf::Event::GainedFocus :
		return 2;
		break;
	case sf::Event::LostFocus :
		return 3;
		break;
	default:
		return 0;
		break;
	}

	return 0;
}

int GameEngine::KeyboardEventManager()
{
	if (isLeftKeyPressed() && isUpKeyPressed() == true)
	{
		return 5;
	}
	else if (isRightKeyPressed() && isUpKeyPressed() == true)
	{
		return 4;
	}
	else if (isUpKeyPressed() == true)
	{
		return 3;
	}
	else if (isLeftKeyPressed() == true)
	{
		return 2;
	}
	else if (isRightKeyPressed() == true)
	{
		return 1;
	}

	return 0;
}