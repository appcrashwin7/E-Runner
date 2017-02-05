#pragma once

#include <SFML/Graphics/RectangleShape.hpp>

class money
{
	sf::RectangleShape moneyShape;

public:
	money();
	money(sf::Vector2f pos,const sf::Texture &textr);
	~money();

	sf::Vector2f getPosition();
	sf::Vector2f getSize();
	sf::RectangleShape *getShape();
};