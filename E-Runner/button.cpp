#include "button.hpp"

const sf::Text button::getText()
{
	return buttText;
}

sf::Vector2i button::getInterBoxSize()
{
	return this->InteractionBoxSize;
}

sf::Vector2i button::getInterBoxPos()
{
	return this->InteractionBoxPosition;
}

bool button::isClick(sf::Vector2i  mousePos,bool isClicked)
{
	sf::Vector2i BoxPos = this->InteractionBoxPosition;
	sf::Vector2i BoxSize = this->InteractionBoxSize;

	if (mousePos.x >=  BoxPos.x && mousePos.x <= BoxPos.x + BoxSize.x
		&& mousePos.y >= BoxPos.y && mousePos.y <= BoxPos.y + BoxSize.y && isClicked == true)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void button::setLogicBoxSize(sf::Vector2i newSize)
{
	this->InteractionBoxSize = newSize;
}

void button::setLogicBoxPos(sf::Vector2i newPosition)
{
	this->InteractionBoxPosition = newPosition;
}

void button::setButtonPosition(sf::Vector2f newPos)
{
	this->buttText.setPosition(newPos);
}

void button::setTextOutlineColor(sf::Color col)
{
	this->buttText.setOutlineColor(col);
}

void button::setTextFillColor(sf::Color col)
{
	this->buttText.setFillColor(col);
}

void button::setTextStyle(sf::Text::Style &style)
{
	this->buttText.setStyle(style);
}

void button::setString(std::string str)
{
	this->buttText.setString(str);
}

void button::setCharacterSize(unsigned int Size)
{
	this->buttText.setCharacterSize(Size);
}

void button::setFont(sf::Font &fon)
{
	this->buttText.setFont(fon);
}

void button::create(sf::Vector2f pos, sf::Vector2i Lpos, sf::Vector2i Lsize, std::string str, sf::Font & fon)
{
	this->buttText.setPosition(pos);
	this->buttText.setString(str);
	this->buttText.setFont(fon);
	this->InteractionBoxPosition = Lpos;
	this->InteractionBoxSize = Lsize;
}

void button::setColor(sf::Color col)
{
	this->buttText.setFillColor(col);
	this->buttText.setOutlineColor(col);
}

button::button()
{}
button::~button()
{}


