#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

struct MEDIA_operator
{
	sf::Music gameMusic;
	sf::SoundBuffer collisonSoundBuffer;
	sf::Sound collisionSound;

	sf::Image textures;

	sf::Texture backobstTexture;
	sf::Texture obstTexture;
	sf::Texture moneysTexture;
	sf::Texture runnerTexture;

	void loadAllMedia()
	{
		gameMusic.openFromFile("music.flac");
		collisonSoundBuffer.loadFromFile("collision.flac");
		collisionSound.setBuffer(collisonSoundBuffer);

		textures.loadFromFile("textures.png");

		obstTexture.loadFromImage(textures, sf::IntRect(0, 0, 200, 200));
		obstTexture.setSmooth(true);

		moneysTexture.loadFromImage(textures, sf::IntRect(0, 210, 200, 200));
		moneysTexture.setSmooth(true);

		runnerTexture.loadFromImage(textures, sf::IntRect(0, 410, 200, 200));
		runnerTexture.setSmooth(true);

		backobstTexture.loadFromImage(textures, sf::IntRect(0, 610, 100, 100));
		backobstTexture.setSmooth(true);
	}
};