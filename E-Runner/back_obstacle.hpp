#pragma once

#include <SFML/Graphics/RectangleShape.hpp>

class back_obstacle
{
	sf::RectangleShape obstShape;
public:
	back_obstacle()
	{
		obstShape.setSize(sf::Vector2f(100.0f, 800.0f));
		obstShape.setPosition(sf::Vector2f(1000, 1000));
		obstShape.setFillColor(sf::Color::White);
	}
	back_obstacle(const sf::Texture *txtr)
		:back_obstacle()
	{
		obstShape.setTexture(txtr);
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