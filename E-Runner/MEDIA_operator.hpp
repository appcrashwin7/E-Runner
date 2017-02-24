#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

struct MEDIA_operator
{
	sf::Music gameMusic;
	sf::SoundBuffer collisonSoundBuffer;
	sf::Sound collisionSound;

	sf::Texture backobstTexture;
	sf::Texture moneysTexture;
	sf::Texture runnerTexture;

	void loadAllMedia()
	{
		gameMusic.openFromFile("music.flac");
		collisonSoundBuffer.loadFromFile("collision.flac");
		collisionSound.setBuffer(collisonSoundBuffer);

		moneysTexture.loadFromFile("bonus.png");
		moneysTexture.setSmooth(true);

		runnerTexture.loadFromFile("runner.png");
		runnerTexture.setSmooth(true);
	}
};