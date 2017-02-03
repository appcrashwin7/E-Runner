#pragma once

#include <SFML/Graphics.hpp>

#include <string>

class button
{
protected:
	sf::Text buttText;

	sf::Vector2i InteractionBoxPosition;
	sf::Vector2i InteractionBoxSize;
public:
	const sf::Text getText();
	sf::Vector2i getInterBoxSize();
	sf::Vector2i getInterBoxPos();

	bool isClick(sf::Vector2i mousePos,bool isClicked);

	void setLogicBoxSize(sf::Vector2i newSize);
	void setLogicBoxPos(sf::Vector2i newPosition);

	void setButtonPosition(sf::Vector2f newPos);
	void setTextOutlineColor(sf::Color col);
	void setTextFillColor(sf::Color col);
	void setTextStyle(sf::Text::Style &style);
	void setString(std::string str);
	void setCharacterSize(unsigned int Size);
	void setFont(sf::Font &fon);
	
	void create(sf::Vector2f pos, sf::Vector2i Lpos,sf::Vector2i Lsize, std::string str, sf::Font &fon);
	void setColor(sf::Color col);

	button();
	~button();
};