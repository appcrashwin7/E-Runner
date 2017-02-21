#include "GameEngine.hpp"
#include "move_type.hpp"
#include "IOoperator.hpp"
#include "keyEvents.hpp"
#include "textbox.hpp"
#include <sstream>

void GameEngine::configureEngine(sf::RenderWindow & twindow, sf::Vector2u windowSize, unsigned int framerate)
{
	gameFont.loadFromFile("arial.ttf");

	targetWindow = &twindow;
	targetWindow->setSize(windowSize);
	targetWindow->setFramerateLimit(framerate);
	engine_is_paused = false;
	camera.setSize((sf::Vector2f)windowSize);
	HUD.create(targetWindow, &gameFont);
}

bool GameEngine::colisionManager()
{
	sf::Vector2f playerPos = this->player.getPosition();
	sf::Vector2f playerSize = this->player.getSize();

	if (playerPos.x <= -200.0f)
	{
		playerPos.x = -201.0f;
		this->player.setPosition(playerPos);
	}
	else if (playerPos.x + playerSize.x >= 600.0f)
	{
		float mov = playerPos.x + playerSize.x - 600.0f;
		playerPos.x = playerPos.x - mov;
		this->player.setPosition(playerPos);
	}

	size_t max;
	size_t i = 0;
	if (obstacles.size() > moneys.size())
	{
		max = obstacles.size();
	}
	else
	{
		max = moneys.size();
	}

	while (i<max)
	{
		if (i < obstacles.size())
		{
			if (IsNotCollision(obstacles[i].getPosition(), obstacles[i].getSize()) == false)
			{
				media_container.gameMusic.stop();
				media_container.collisionSound.play();
				return true;
			}
		}

		if (i < moneys.size())
		{
			if (IsNotCollision(moneys[i].getPosition(), moneys[i].getSize()) == false)
			{
				points += 100;
				moneys.erase(moneys.begin() + i);
				break;
			}
		}
		i++;
	}

	return false;
}

bool GameEngine::IsNotCollision(sf::Vector2f objPos, sf::Vector2f objSize)
{
	sf::Vector2f playerPos = this->player.getPosition();
	sf::Vector2f playerSize = this->player.getSize();
	if (playerPos.x > objPos.x + objSize.x || playerPos.x + playerSize.x < objPos.x ||
		playerPos.y > objPos.y + objSize.y || playerPos.y + playerSize.y < objPos.y)
	{
		return true;
	}
	return false;
}

void GameEngine::dataCleaner()
{
	sf::Vector2f objPos;
	sf::Vector2f playerPos = this->player.getPosition();

	size_t lastObj_a = 0;
	size_t lastObj_b = 0;

	size_t max;
	if (obstacles.size() > moneys.size())
	{
		max = obstacles.size();
	}
	else
		max = moneys.size();

	size_t i = 0;
	while (i < max)
	{
		if (i < obstacles.size())
		{
			objPos = obstacles[i].getPosition();
			if (objPos.y > playerPos.y + 200)
			{
				lastObj_a = i;
			}
		}
		if (i < moneys.size())
		{
			objPos = moneys[i].getPosition();
			if (objPos.y > playerPos.y + 200)
			{
				lastObj_b = i;
			}
		}
		i++;
	}
		obstacles.erase(obstacles.begin(),obstacles.begin()+lastObj_a);
		moneys.erase(moneys.begin(), moneys.begin() + lastObj_b);
}

void GameEngine::Start()
{
		this->gameLoop();
}

GameEngine::GameEngine()
{
	rand_engine.seed(static_cast<unsigned int>(time(NULL)));
	points = 0;
	playerIsAlive = true;
	media_container.loadAllMedia();
	player.create(&media_container.runnerTexture, sf::Vector2f());
}

GameEngine::~GameEngine()
{
	targetWindow = nullptr;
	obstacles.clear();
	moneys.clear();
}

int GameEngine::gameLoop()
{
	float speed = 0.5f;
	int Numloop = 1;
	media_container.gameMusic.play();
	media_container.gameMusic.setVolume(40);
	media_container.gameMusic.setLoop(true);

	sf::Event loopEvents;

	while (targetWindow->isOpen())
	{
		this->EventManager(loopEvents);

		if (engine_is_paused == true)
		{
			switch (HUD.getEvent(targetWindow))
			{
			case 1:
				engine_is_paused = false;
				break;
			case 2:
				targetWindow->close();
				break;
			default:
				break;
			}
		}
		KeyboardEventManager(speed);
		if (this->engine_is_paused == false)
		{
			if (Numloop % 50 == 0)
			{
				this->objectGenerator();
			}

			bool game_over = colisionManager();
			if (game_over == true)
			{
				playerIsAlive = false;
			}

			setCameraPos();
			targetWindow->setView(camera);
			HUD.setNewGUIElementsPos(targetWindow);

			addSomePoint();
			speed += 0.001f;
			Numloop++;
		}
		
		dataCleaner();

		if (playerIsAlive == false)
		{
			bool playerWantRestartGame = loseLoop(loopEvents);
			if (playerWantRestartGame == true)
			{
				speed = 0.5f;
				points = 0;
				Numloop = 1;
				player.setPosition(sf::Vector2f(0,0));

				obstacles.clear();
				moneys.clear();
				playerIsAlive = true;
				media_container.gameMusic.play();
			}
			else
			{
				return 0;
			}
		}
		this->HUD.setScore(points);

		targetWindow->clear();
		this->drawGameArea();
			this->HUD.drawGameGUI(targetWindow,engine_is_paused);
		objectDraw();
		targetWindow->display();
	}
	return 0;
}

void GameEngine::drawGameArea()
{
	targetWindow->draw(player.getShape());
}

void GameEngine::setCameraPos()
{
	sf::Vector2u windowSize = this->targetWindow->getSize();
	sf::Vector2f playerPos = this->player.getPosition();

	sf::Vector2f newCameraPos = playerPos;
	float sizeY = (float)windowSize.y / 4;
	newCameraPos.y -= sizeY;
	newCameraPos.x = 200;
	camera.setCenter(newCameraPos);
}

bool GameEngine::loseLoop(sf::Event &events)
{
	targetWindow->setView(targetWindow->getDefaultView());
	HUD.setNewGUIElementsPos(targetWindow);

	IOoperator scoreOperator;
	scoreOperator.loadScoreFromFile();
	scoreOperator.divideRawToScoresAndNames();

	sf::Text info;
	info.setFont(this->gameFont);
	info.setPosition(sf::Vector2f(100, 400));
	info.setFillColor(sf::Color::Red);
	
	textbox playerName;
	playerName.create(this->gameFont, false, "", 12);
	playerName.changeVars(sf::Color::Blue, 32, sf::Text::Regular);
	playerName.setPosition(sf::Vector2u(320, 400));

	if (scoreOperator.thisScoreIsEnough(points) == true)
	{
		info.setString("Type you name:");
		playerName.setEnable(true);
	}
	else
	{
		info.setString(":(");
	}

	while (targetWindow->isOpen())
	{
		while (targetWindow->pollEvent(events))
		{
			switch (events.type)
			{
			case sf::Event::Closed:
				targetWindow->close();
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) == true)
			{
				return false;
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return) == true && scoreOperator.thisScoreIsEnough(points) == true)
			{
				scoreOperator.insertNewScore(playerName.getString(), points);
				scoreOperator.saveScoreToFile();
				return true;
			}
			playerName(events);
		}

		targetWindow->clear();
		HUD.drawGUIWhenPlayerLose(targetWindow);
		targetWindow->draw(playerName.getText());
		targetWindow->draw(info);
		targetWindow->display();
	}
	return false;
}

void GameEngine::addSomePoint()
{
	sf::Vector2f playerPos = player.getPosition();
	int number = static_cast<int>(playerPos.y);
	if (number % 25 == 0)
	{
		points += 1;
	}
}

void GameEngine::objectGenerator()
{
	std::uniform_int_distribution <int> distribution(-100,500);

	sf::Vector2f pos = player.getPosition();
	pos.y -= 1000;
	pos.x = static_cast<float>(distribution(rand_engine));
	obstacles.push_back(obstacle(pos,media_container.obstTexture));
	pos.x = static_cast<float>(distribution(rand_engine));
	obstacles.push_back(obstacle(pos,media_container.obstTexture));
	pos.x = static_cast<float>(distribution(rand_engine));
	pos.y -= 100.0f;
	moneys.push_back(money(pos,media_container.moneysTexture));
}

void GameEngine::objectDraw()
{
	size_t max;
	size_t i = 0;
	if (obstacles.size() > moneys.size())
	{
		max = obstacles.size();
	}
	else
	{
		max = moneys.size();
	}

	while (i < max)
	{
		if (i < obstacles.size())
		{
			targetWindow->draw(*obstacles[i].getObstacleShape());
		}

		if (i < moneys.size())
		{
			targetWindow->draw(*moneys[i].getShape());
		}
		i++;
	}
}

int GameEngine::EventManager(sf::Event &windowEvent)
{
	targetWindow->pollEvent(windowEvent);

	switch (windowEvent.type)
	{
	case sf::Event::Closed :
		targetWindow->close();
		break;
	case sf::Event::LostFocus :
		if (engine_is_paused == false)
		{
			engine_is_paused = true;
		}
		break;
	default:
		break;
	}
	return 0;
}

void GameEngine::KeyboardEventManager(float speedMod)
{
	keyEvents keEv;
	if (this->engine_is_paused == false)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) == true)
		{
			media_container.gameMusic.pause();
			engine_is_paused = true;
			return;
		}

		if (keEv.isLeftKeyPressed() && keEv.isUpKeyPressed() == true)
		{
			this->player.move(move_type::up_and_left, speedMod);
		}
		else if (keEv.isRightKeyPressed() && keEv.isUpKeyPressed() == true)
		{
			this->player.move(move_type::up_and_right, speedMod);
		}
		else if (keEv.isUpKeyPressed() == true)
		{
			this->player.move(move_type::up, speedMod);
		}
		else if (keEv.isLeftKeyPressed() == true)
		{
			this->player.move(move_type::left, speedMod);
		}
		else if (keEv.isRightKeyPressed() == true)
		{
			this->player.move(move_type::right, speedMod);
		}
		else
		{
			this->player.move(move_type::other, speedMod);
		}
	}
	else
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) == true)
		{
			media_container.gameMusic.play();
			engine_is_paused = false;
		}
	}
}