#include "GameEngine.hpp"
#include "move_type.hpp"
#include "IOoperator.hpp"
#include <sstream>

bool isUpKeyPressed()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) == true
		|| sf::Keyboard::isKeyPressed(sf::Keyboard::Up) == true)
	{
		return true;
	}
	return false;
}
bool isLeftKeyPressed()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) == true
		|| sf::Keyboard::isKeyPressed(sf::Keyboard::Left) == true)
	{
		return true;
	}
	return false;
}
bool isRightKeyPressed()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) == true
		|| sf::Keyboard::isKeyPressed(sf::Keyboard::Right) == true)
	{
		return true;
	}
	return false;
}

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

	for (size_t i = 0; i < obstacles.size(); i++)
	{
		if(IsNotCollision(obstacles[i].getPosition(),obstacles[i].getSize()) == false)
		{
			media_container.gameMusic.stop();
			media_container.collisionSound.play();
			return true;
		}
	}

	for (size_t j = 0; j < moneys.size(); j++)
	{
		if (IsNotCollision(moneys[j].getPosition(),moneys[j].getSize()) == false)
		{
			points += 100;
			moneys.erase(moneys.begin() + j);
			break;
		}
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

	size_t lastObj = 0;

	for (size_t i = 0; i < obstacles.size(); i++)
	{
		objPos = obstacles[i].getPosition();
		if (objPos.y > playerPos.y + 200)
		{
			lastObj = i;
		}
	}
		obstacles.erase(obstacles.begin(),obstacles.begin()+lastObj);

		lastObj = 0;
		for (size_t i = 0; i < moneys.size(); i++)
		{
			objPos = moneys[i].getPosition();
			if (objPos.y > playerPos.y + 200)
			{
				lastObj = i;
			}
		}
		moneys.erase(moneys.begin(), moneys.begin() + lastObj);
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
	IOoperator scoreOperator;
	scoreOperator.loadScoreFromFile();
	scoreOperator.divideRawToScoresAndNames();

	sf::Text nameOfplayer;
	nameOfplayer.setFont(this->gameFont);
	nameOfplayer.setPosition(targetWindow->mapPixelToCoords(sf::Vector2i(400,400)));
	nameOfplayer.setFillColor(sf::Color::Blue);

	sf::Text info;
	info.setFont(this->gameFont);
	info.setPosition(targetWindow->mapPixelToCoords(sf::Vector2i(150, 400)));
	info.setFillColor(sf::Color::Red);
	info.setString("Type you name:");
	const size_t maxTextLength = 8;

	bool playerCanRename = true;

	std::string StringnameOfPlayer = "";
	while (targetWindow->isOpen())
	{
		while (targetWindow->pollEvent(events))
		{
			switch (events.type)
			{
			case sf::Event::Closed:
				targetWindow->close();
			}
			if (playerCanRename == true)
			{
				if (events.type == sf::Event::TextEntered)
				{
					if (events.text.unicode < 128)
					{
						if (events.text.unicode == 8)
						{
							if (StringnameOfPlayer.size() > 0)
							{
								StringnameOfPlayer.pop_back();
							}
							nameOfplayer.setString(StringnameOfPlayer);
							break;
						}
						if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return) == true && StringnameOfPlayer.size() >= 2)
						{
							playerCanRename = false;
							scoreOperator.insertNewScore(StringnameOfPlayer, points);
							scoreOperator.saveScoreToFile();
							return true;
						}
						if (StringnameOfPlayer.size() >= maxTextLength)
						{
							break;
						}
						StringnameOfPlayer += static_cast<char>(events.text.unicode);
						nameOfplayer.setString(StringnameOfPlayer);

					}
				}
			}
		}
			nameOfplayer.setString(StringnameOfPlayer);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) == true)
		{
			return true;
		}

		targetWindow->clear();
		HUD.drawGUIWhenPlayerLose(targetWindow);
		targetWindow->draw(nameOfplayer);
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
	obstacles.push_back(obstacle(pos));
	pos.x = static_cast<float>(distribution(rand_engine));
	obstacles.push_back(obstacle(pos));
	pos.x = static_cast<float>(distribution(rand_engine));
	pos.y -= 100.0f;
	moneys.push_back(money(pos));
}

void GameEngine::objectDraw()
{
	for (size_t i = 0; i < moneys.size(); i++)
	{
		targetWindow->draw(*moneys[i].getShape());
	}
	for (size_t i = 0; i < obstacles.size(); i++)
	{
		targetWindow->draw(*obstacles[i].getObstacleShape());
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
	if (this->engine_is_paused == false)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) == true)
		{
			media_container.gameMusic.pause();
			engine_is_paused = true;
			return;
		}

		if (isLeftKeyPressed() && isUpKeyPressed() == true)
		{
			this->player.move(move_type::up_and_left, speedMod);
		}
		else if (isRightKeyPressed() && isUpKeyPressed() == true)
		{
			this->player.move(move_type::up_and_right, speedMod);
		}
		else if (isUpKeyPressed() == true)
		{
			this->player.move(move_type::up, speedMod);
		}
		else if (isLeftKeyPressed() == true)
		{
			this->player.move(move_type::left, speedMod);
		}
		else if (isRightKeyPressed() == true)
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