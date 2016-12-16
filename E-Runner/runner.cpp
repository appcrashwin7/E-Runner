#include "runner.hpp"

runner::runner()
{
	runnerBody.setSize(sf::Vector2f(100, 100));
	runnerBody.setFillColor(sf::Color::Blue);
}

runner::~runner()
{}

void runner::create(sf::Texture * text, sf::Vector2f pos)
{
	runnerBody.setSize(sf::Vector2f(100, 100));
	runnerBody.setPosition(pos);
	runnerBody.setTexture(text);
}

void runner::setTexture(sf::Texture * texture)
{
	runnerBody.setTexture(texture);
}

void runner::setPosition(sf::Vector2f newPos)
{
	this->runnerBody.setPosition(newPos);
}

sf::Vector2f runner::getPosition()
{
	return runnerBody.getPosition();
}

sf::Vector2f runner::getSize()
{
	return runnerBody.getSize();
}

sf::RectangleShape runner::getShape()
{
	return runnerBody;
}

void runner::move(move_type var,float speed_factor)
{
	sf::Vector2f added_vector;
	added_vector.x = 0, added_vector.y = 0;
	switch (var)
	{
	case up:
		added_vector.y = -20.0f * speed_factor;
		break;
	case up_and_left:
		added_vector.y = -15.0f * speed_factor;
		added_vector.x = -10.0f;
		break;
	case up_and_right:
		added_vector.y = -15.0f * speed_factor;
		added_vector.x = 10.0f;
		break;
	case left:
		added_vector.y = -10.0f * speed_factor;
		added_vector.x = -10.0f;
		break;
	case right:
		added_vector.y = -10.0f * speed_factor;
		added_vector.x = 10.0f;
		break;
	default:
		added_vector.y = -10.0f * speed_factor;
		break;
	}
	sf::Vector2f newPosition = runnerBody.getPosition() + added_vector;
	runnerBody.setPosition(newPosition);
}