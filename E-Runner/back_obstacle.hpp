#pragma once

#include <SFML/Graphics/RectangleShape.hpp>

class back_obstacle
{
	sf::RectangleShape obstShape;

public:
	back_obstacle(sf::Texture *txtr)
	{
		//obstShape.setFillColor(sf::Color::White);
		obstShape.setSize(sf::Vector2f(100, 800));
		obstShape.setPosition(sf::Vector2f(1000, 1000));
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