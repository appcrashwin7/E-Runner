#pragma once

#include <SFML/Graphics/RectangleShape.hpp>

class obstacle
{
	sf::RectangleShape obstacleShape;

public:
	obstacle();
	~obstacle();

	obstacle(sf::Vector2f position);

	sf::Vector2f getPosition();
	const  sf::RectangleShape *getObstacleShape();
};