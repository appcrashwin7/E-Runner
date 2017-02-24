#pragma once

#include <string>

#include <SFML/Graphics.hpp>

class BestRunsRank
{
	sf::Font font;
	sf::Text info;
	sf::Text ScoreText[10];

public:
	BestRunsRank();
	~BestRunsRank();

	void Loop(sf::RenderWindow *targetWindow);
private:
	void loadScoresFromFile();
};