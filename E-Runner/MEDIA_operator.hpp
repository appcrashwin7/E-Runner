#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

struct MEDIA_operator
{
	sf::Music gameMusic;
	sf::SoundBuffer collisonSoundBuffer;
	sf::Sound collisionSound;

	void loadAllMedia()
	{
		gameMusic.openFromFile("music.flac");
		collisonSoundBuffer.loadFromFile("qubodup__fast-collision-reverb.flac");
		collisionSound.setBuffer(collisonSoundBuffer);
	}
};