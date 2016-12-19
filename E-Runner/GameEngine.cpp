#include "GameEngine.hpp"
#include "move_type.hpp"
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
	sf::Vector2f objPos;
	sf::Vector2f objSize;
	for (size_t i = 0; i < obstacles.size(); i++)
	{
		objPos = obstacles[i].getPosition();
		objSize = obstacles[i].getSize();

		if (playerPos.x > objPos.x + objSize.x || playerPos.x + playerSize.x < objPos.x ||
			playerPos.y > objPos.y + objSize.y || playerPos.y + playerSize.y < objPos.y)
		{ }
		else
		{
			return true;
		}
	}

	for (size_t j = 0; j < moneys.size(); j++)
	{
		objPos = moneys[j].getPosition();
		objSize = moneys[j].getSize();

		if (playerPos.x > objPos.x + objSize.x || playerPos.x + playerSize.x < objPos.x ||
			playerPos.y > objPos.y + objSize.y || playerPos.y + playerSize.y < objPos.y)
		{
		}
		else
		{
			points += 100;
			moneys.erase(moneys.begin() + j);
			break;
		}

	}

	return false;
}

void GameEngine::dataCleaner()
{
	sf::Vector2f objPos;
	sf::Vector2f playerPos = this->player.getPosition();

	size_t lastObj = 0;

	for (size_t i = 0; i < obstacles.size(); i++)
	{
		objPos = obstacles[i].getPosition();
		if (objPos.y > playerPos.y + 200)
		{
			lastObj = i;
		}
	}
		obstacles.erase(obstacles.begin(),obstacles.begin()+lastObj);

		lastObj = 0;
		for (size_t i = 0; i < moneys.size(); i++)
		{
			objPos = moneys[i].getPosition();
			if (objPos.y > playerPos.y + 200)
			{
				lastObj = i;
			}
		}
		moneys.erase(moneys.begin(), moneys.begin() + lastObj);
}

void GameEngine::Start()
{
	if(engine_is_prepared == true)
		this->gameLoop();
	return;
}

GameEngine::GameEngine()
{
	rand_engine.seed(static_cast<unsigned int>(time(NULL)));
	points = 0;
	playerIsAlive = true;
}

GameEngine::~GameEngine()
{
	targetWindow = nullptr;
	obstacles.clear();
	moneys.clear();
}

int GameEngine::gameLoop()
{
	float speed = 0.5f;
	int Numloop = 1;
	while (targetWindow->isOpen())
	{
		this->EventManager();

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
		KeyboardEventManager(speed);
		if (this->engine_is_paused == false)
		{
			if (Numloop % 50 == 0)
			{
				this->objectGenerator();
			}

			bool game_over = colisionManager();
			if (game_over == true)
			{
				playerIsAlive = false;
			}

			sf::Vector2f test = this->player.getPosition();
			std::cout << test.x << " " << test.y << "\n";

			setCameraPos();
			targetWindow->setView(camera);
			HUD.setNewGUIElementsPos(targetWindow);

			addSomePoint();
			speed += 0.001f;
			Numloop++;
		}
		
		dataCleaner();

		if (playerIsAlive == false)
		{
			bool playerWantRestartGame = loseLoop();
			if (playerWantRestartGame == true)
			{
				speed = 0.5f;
				points = 0;
				Numloop = 1;
				player.setPosition(sf::Vector2f(0,0));

				obstacles.clear();
				moneys.clear();
				playerIsAlive = true;
			}
			else
			{
				return 0;
			}
		}
		this->HUD.setScore(points);

		//graphics
		targetWindow->clear();
		this->drawGameArea();
			this->HUD.drawGameGUI(targetWindow,engine_is_paused);
		objectDraw();
		targetWindow->display();
	}
	return 0;
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

bool GameEngine::loseLoop()
{
	while (targetWindow->isOpen())
	{
		sf::Event events;
		while (targetWindow->pollEvent(events))
		{
			switch (events.type)
			{
			case sf::Event::Closed :
				targetWindow->close();
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::R) == true)
		{
			return true;
		}

		targetWindow->clear();
		this->HUD.drawGUIWhenPlayerLose(targetWindow);
		targetWindow->display();
	}
	return false;
}

void GameEngine::addSomePoint()
{
	sf::Vector2f playerPos = player.getPosition();
	int number = static_cast<int>(playerPos.y);
	if (number % 25 == 0)
	{
		points += 1;
	}
}

void GameEngine::objectGenerator()
{
	std::uniform_int_distribution <int> distribution(-100,500);


	sf::Vector2f pos = player.getPosition();
	pos.y -= 1000;
	pos.x = static_cast<float>(distribution(rand_engine));
	obstacles.push_back(obstacle(pos));
	pos.x = static_cast<float>(distribution(rand_engine));
	obstacles.push_back(obstacle(pos));
	pos.x = static_cast<float>(distribution(rand_engine));
	pos.y -= 100.0f;
	moneys.push_back(money(pos));
}

void GameEngine::objectDraw()
{
	for (size_t i = 0; i < moneys.size(); i++)
	{
		targetWindow->draw(*moneys[i].getShape());
	}
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
		targetWindow->close();
		break;
	case sf::Event::LostFocus :
		if (engine_is_paused == false)
		{
			engine_is_paused = true;
		}
		break;
	default:
		break;
	}
	return 0;
}

void GameEngine::KeyboardEventManager(float speedMod)
{
	if (this->engine_is_paused == false)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) == true)
		{
			engine_is_paused = true;
			return;
		}

		if (isLeftKeyPressed() && isUpKeyPressed() == true)
		{
			this->player.move(move_type::up_and_left, speedMod);
		}
		else if (isRightKeyPressed() && isUpKeyPressed() == true)
		{
			this->player.move(move_type::up_and_right, speedMod);
		}
		else if (isUpKeyPressed() == true)
		{
			this->player.move(move_type::up, speedMod);
		}
		else if (isLeftKeyPressed() == true)
		{
			this->player.move(move_type::left, speedMod);
		}
		else if (isRightKeyPressed() == true)
		{
			this->player.move(move_type::right, speedMod);
		}
		else
		{
			this->player.move(move_type::other, speedMod);
		}
	}
	else
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) == true)
		{
			engine_is_paused = false;
		}
	}
}