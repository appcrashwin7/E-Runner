#include "GameEngine.hpp"
#include <iostream>

bool isUpKeyPressed()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)
		|| sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		return true;
	}
	return false;
}
bool isLeftKeyPressed()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)
		|| sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		return true;
	}
	return false;
}
bool isRightKeyPressed()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)
		|| sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		return true;
	}
	return false;
}

void GameEngine::configureEngine(sf::RenderWindow & twindow, sf::Vector2u windowSize, unsigned int framerate)
{
	targetWindow = &twindow;
	targetWindow->setSize(windowSize);
	targetWindow->setFramerateLimit(framerate);

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
}

int GameEngine::gameLoop()
{
	return 0;
}

void GameEngine::drawGameArea()
{
	targetWindow->clear();
	targetWindow->draw(player.getShape());
	targetWindow->display();
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