#include "obstacle.hpp"

obstacle::obstacle()
{
	obstacleShape.setSize(sf::Vector2f(100.0f, 100.0f));
	obstacleShape.setFillColor(sf::Color::Red);
}

obstacle::~obstacle()
{}

obstacle::obstacle(sf::Vector2f position)
	:obstacle()
{
	obstacleShape.setPosition(position);
}

sf::Vector2f obstacle::getPosition()
{
	return obstacleShape.getPosition();
}

const sf::RectangleShape * obstacle::getObstacleShape()
{
	return  &obstacleShape;
}
