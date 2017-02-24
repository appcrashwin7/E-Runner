#include "gameGUI.hpp"
#include <sstream>
#include <SFML/Window/Mouse.hpp>

gameGUI::gameGUI()
{
}

gameGUI::~gameGUI()
{
}

void gameGUI::create(sf::RenderWindow *targetWindow,sf::Font *font)
{
	this->information.setString("Game Paused");
	this->information.setPosition(targetWindow->mapPixelToCoords(sf::Vector2i(400, 200)));
	this->information.setFont(*font);

	this->score.setString("0");
	this->score.setPosition(targetWindow->mapPixelToCoords(sf::Vector2i(100, 100)));
	this->score.setFont(*font);
	this->score.setFillColor(sf::Color::White);

	this->youLose.setString("You Lose");
	this->youLose.setFillColor(sf::Color(150, 100, 50));
	this->youLose.setFont(*font);

	this->continueb.create(targetWindow->mapPixelToCoords(sf::Vector2i(400, 400)), sf::Vector2i(400, 400),
		sf::Vector2i(100, 50), "Continue", *font);
	this->exit.create(targetWindow->mapPixelToCoords(sf::Vector2i(400, 500)), sf::Vector2i(400, 500),
		sf::Vector2i(100, 50), "Exit", *font);
}

void gameGUI::setScore(int newScore)
{
	std::ostringstream sc;
	sc << newScore;
	this->score.setString(sc.str());
}

void gameGUI::setNewGUIElementsPos(sf::RenderWindow * window)
{
	this->score.setPosition(window->mapPixelToCoords(sf::Vector2i(200, 100)));
	this->information.setPosition(window->mapPixelToCoords(sf::Vector2i(400, 200)));
	this->youLose.setPosition(window->mapPixelToCoords(sf::Vector2i(400, 50)));

	this->continueb.setButtonPosition(window->mapPixelToCoords(sf::Vector2i(400, 400)));
	this->exit.setButtonPosition(window->mapPixelToCoords(sf::Vector2i(400, 500)));
}

unsigned int gameGUI::getEvent(sf::RenderWindow *targetWindow)
{
	if (continueb.isClick(sf::Mouse::getPosition(*targetWindow),
		sf::Mouse::isButtonPressed(sf::Mouse::Left)) == true)
	{
		return 1;
	}
	else if(exit.isClick(sf::Mouse::getPosition(*targetWindow),
		sf::Mouse::isButtonPressed(sf::Mouse::Left)) == true)
	{
		return 2;
	}

	return 0;
}

void gameGUI::drawGameGUI(sf::RenderWindow *targetWindow, bool isgamePaused)
{
	targetWindow->draw(this->score);

	if (isgamePaused == false)
	{
		return;
	}
	targetWindow->draw(this->information);
	targetWindow->draw(this->continueb.getText());
	targetWindow->draw(this->exit.getText());
}

void gameGUI::drawGUIWhenPlayerLose(sf::RenderWindow * targetWindow)
{
	targetWindow->draw(this->score);
	targetWindow->draw(this->youLose);
}
