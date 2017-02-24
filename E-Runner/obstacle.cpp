#include "obstacle.hpp"

obstacle::obstacle()
{
	obstacleShape.setSize(sf::Vector2f(100.0f, 100.0f));
	obstacleShape.setFillColor(sf::Color::Red);
}

obstacle::obstacle(sf::Vector2f position)
	:obstacle()
{
	obstacleShape.setPosition(position);
}

obstacle::~obstacle()
{}

obstacle::obstacle(sf::Vector2f position,const sf::Texture &textr)
	:obstacle()
{
	obstacleShape.setTexture(&textr);
	obstacleShape.setPosition(position);
}

sf::Vector2f obstacle::getPosition()
{
	return obstacleShape.getPosition();
}

sf::Vector2f obstacle::getSize()
{
	return obstacleShape.getSize();
}

sf::RectangleShape * obstacle::getObstacleShape()
{
	return  &obstacleShape;
}
