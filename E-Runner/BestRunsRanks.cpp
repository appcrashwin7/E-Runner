#include "BestRunsRanks.hpp"
#include "IOoperator.hpp"

BestRunsRank::BestRunsRank()
{
	font.loadFromFile("arial.ttf");

	float posX = 400;
	float posY = 100;
	for (auto i = 0; i < 10; i++)
	{
		ScoreText[i].setString("0");
		ScoreText[i].setPosition(sf::Vector2f(posX,posY));
		ScoreText[i].setFont(font);

		posY += 50;
	}
	loadScoresFromFile();
	info.setPosition(sf::Vector2f(200, 50));
	info.setFillColor(sf::Color::Red);
	info.setString("Best Runs:");
	info.setFont(font);
}

BestRunsRank::~BestRunsRank()
{
}

void BestRunsRank::Loop(sf::RenderWindow * targetWindow)
{
	while (targetWindow->isOpen())
	{
		sf::Event event;
		targetWindow->pollEvent(event);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) == true)
		{
			return;
		}

		targetWindow->clear();
		for (auto i = 0; i < 10; i++)
		{
			targetWindow->draw(ScoreText[i]);
		}
		targetWindow->draw(info);
		targetWindow->display();
	}
}

void BestRunsRank::loadScoresFromFile()
{
	IOoperator scoreLoader;
	std::string scoreToLoad;

	scoreLoader.loadScoreFromFile();

	for (size_t i = 0; i < 10; i++)
	{
		scoreToLoad = scoreLoader.getRawData(i);
		ScoreText[i].setString(scoreToLoad);
	}
}
