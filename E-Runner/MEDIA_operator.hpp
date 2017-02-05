#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

struct MEDIA_operator
{
	sf::Music gameMusic;
	sf::SoundBuffer collisonSoundBuffer;
	sf::Sound collisionSound;

	sf::Texture obstTexture;
	sf::Texture moneysTexture;
	sf::Texture runnerTexture;

	void loadAllMedia()
	{
		gameMusic.openFromFile("music.flac");
		collisonSoundBuffer.loadFromFile("qubodup__fast-collision-reverb.flac");
		collisionSound.setBuffer(collisonSoundBuffer);
		obstTexture.loadFromFile("obstacle.png");
		obstTexture.generateMipmap();
		obstTexture.setSmooth(true);

		moneysTexture.loadFromFile("moneys.png");
		moneysTexture.generateMipmap();
		moneysTexture.setSmooth(true);

		runnerTexture.loadFromFile("runner.png");
		runnerTexture.generateMipmap();
		runnerTexture.setSmooth(true);
	}
};