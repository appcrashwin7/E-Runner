#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

struct MEDIA_operator
{
	sf::Texture playerTexture;
	sf::Texture objectsTexture[5];
	sf::Texture Backgroundtexture;

	sf::Font gameFonts[2];

	sf::Music gameMusic;
	sf::Sound collisionSounds[5];


	void loadAllMedia()
	{}
};