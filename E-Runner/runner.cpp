#include "runner.hpp"

runner::runner()
{}

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
		added_vector.y = -20 * speed_factor;
		break;
	case up_and_left:
		added_vector.y = -10 * speed_factor;
		added_vector.x = -10;
		break;
	case up_and_right:
		added_vector.y = -10 * speed_factor;
		added_vector.x = 10;
		break;
	default:
		added_vector.y = -10 * speed_factor;
		break;
	}
	sf::Vector2f newPosition = runnerBody.getPosition() + added_vector;
	runnerBody.setPosition(newPosition);
}