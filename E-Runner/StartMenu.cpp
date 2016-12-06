#include "StartMenu.hpp"
#include <iostream>

void StartMenu::draw()
{
	if (Pwindow != nullptr)
	{
		Pwindow->clear();
		Pwindow->draw(this->gameName);
		Pwindow->draw(this->StartGame.getText());
		Pwindow->draw(this->BestRuns.getText());
		Pwindow->draw(this->Exit.getText());
		//Pwindow->draw(this->backgroundImage);
		Pwindow->display();
	}
	else
	{
		std::cout << "StartMenu::Pwindow is null!" << std::endl;
	}
}

int StartMenu::MenuEvents()
{
	if (Pwindow == nullptr)
	{
		std::cout << "StartMenu::Pwindow is null!" << std::endl;
		return 10;
	}
	sf::Event event;
	Pwindow->pollEvent(event);
	switch (event.type)
	{
	case sf::Event::Closed:
		return 5;
		break;
	}
	if (this->StartGame.isClick(sf::Mouse::getPosition(*Pwindow), sf::Mouse::isButtonPressed(sf::Mouse::Left)))
	{
		return 1;
	}
	else if (this->BestRuns.isClick(sf::Mouse::getPosition(*Pwindow), sf::Mouse::isButtonPressed(sf::Mouse::Left)))
	{
		return 2;
	}
	else if (this->Exit.isClick(sf::Mouse::getPosition(*Pwindow), sf::Mouse::isButtonPressed(sf::Mouse::Left)))
	{
		return 3;
	}

	return 0;
}

void StartMenu::create(sf::RenderWindow & targetW/* sf::Texture & textureForBackgImage*/)
{
	Pwindow = &targetW;
	//backgroundImage.setTexture(textureForBackgImage);
}

StartMenu::StartMenu()
{
	this->SMenuFont.loadFromFile("arial.ttf");
	this->StartGame.create(sf::Vector2f(300, 300), sf::Vector2i(300, 300),
		sf::Vector2i(100, 50), "Start Game", this->SMenuFont);
	this->BestRuns.create(sf::Vector2f(300, 500), sf::Vector2i(300, 500),
		sf::Vector2i(100, 50), "Best Runs", this->SMenuFont);
	this->Exit.create(sf::Vector2f(300, 700), sf::Vector2i(300, 700),
		sf::Vector2i(100, 50), "Exit", this->SMenuFont);
	this->backgroundImage.setPosition(sf::Vector2f(0, 0));
	this->gameName.setPosition(sf::Vector2f(50, 50));
	this->gameName.setString("E-Runner");
	this->gameName.setFillColor(sf::Color::Green);
	this->gameName.setFont(SMenuFont);
}

StartMenu::~StartMenu()
{
	Pwindow = nullptr;
}
