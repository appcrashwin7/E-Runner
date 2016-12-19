#pragma once
#include <SFML/Graphics/RectangleShape.hpp>

#include "move_type.hpp"

class runner
{
	sf::RectangleShape runnerBody;

public:
	runner();
	~runner();

	void create(sf::Texture *text,sf::Vector2f pos);
	void setTexture(sf::Texture *texture);
	void setPosition(sf::Vector2f newPos);
	sf::Vector2f getPosition();
	sf::Vector2f getSize();
	sf::RectangleShape getShape();

	void move(move_type var,float speed_factor);
};