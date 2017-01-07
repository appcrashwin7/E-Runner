#pragma once
#include <SFML/Window.hpp>

struct keyEvents
{
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
};