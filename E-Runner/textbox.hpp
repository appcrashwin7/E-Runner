#pragma once

#include <SFML/Graphics.hpp>

class textbox
{
	size_t MAX_TEXT_SIZE = 30;

	bool IsEnable = false;
	bool IsConstant = false;
	std::string String;
	sf::Text TXBOX_text;

public:
	textbox();
	~textbox();

	void operator()(sf::Event &event);

	void create(sf::Font &font, bool isConstant, std::string strForTextBox, size_t MAXSIZE);
	void changeVars(sf::Color colorForText, unsigned int CharSize, sf::Uint32 style);
	bool isClick(sf::Vector2i mousePos,bool isMouseClick);

	std::string getString();
	void setString(std::string str);
	sf::Text getText();

	void setEnable(bool var);
	void switchEnable();
	bool getIsEnable();

	void setPosition(sf::Vector2u newPos);
	sf::Vector2u getPosition();
};