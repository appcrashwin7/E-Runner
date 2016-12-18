#include "money.hpp"

money::money()
{
	moneyShape.setSize(sf::Vector2f(50, 50));
	moneyShape.setFillColor(sf::Color::Yellow);
}

money::money(sf::Vector2f pos)
	:money()
{
	moneyShape.setPosition(pos);
}

money::~money()
{}

sf::Vector2f money::getPosition()
{
	return moneyShape.getPosition();
}

sf::Vector2f money::getSize()
{
	return moneyShape.getSize();
}

sf::RectangleShape * money::getShape()
{
	return &moneyShape;
}
