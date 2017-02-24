#pragma once

#include <SFML/Graphics/RectangleShape.hpp>

class back_obstacle
{
	sf::RectangleShape obstShape;

public:
	back_obstacle()
	{
		obstShape.setFillColor(sf::Color::Red);
		obstShape.setSize(sf::Vector2f(100, 800));
	}
	~back_obstacle(){}

	void move(sf::Vector2f vect)
	{
		obstShape.move(vect);
	}
	void setPosition(sf::Vector2f newPos)
	{
		obstShape.setPosition(newPos);
	}
	sf::RectangleShape *getShape()
	{
		return &obstShape;
	}
};