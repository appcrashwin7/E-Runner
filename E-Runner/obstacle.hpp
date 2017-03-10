#pragma once

#include <SFML/Graphics/RectangleShape.hpp>

class obstacle
{
	sf::RectangleShape obstacleShape;

public:
	obstacle()
	{
		obstacleShape.setSize(sf::Vector2f(100.0f, 100.0f));
		obstacleShape.setFillColor(sf::Color::White);
	}
	obstacle(sf::Vector2f position, const sf::Texture &textr)
		:obstacle()
	{
		obstacleShape.setTexture(&textr);
		obstacleShape.setPosition(position);
	}
	~obstacle(){}

	sf::Vector2f getPosition()
	{
		return obstacleShape.getPosition();
	}
	sf::Vector2f getSize()
	{
		return obstacleShape.getSize();
	}
	sf::RectangleShape *getObstacleShape()
	{
		return  &obstacleShape;
	}
};