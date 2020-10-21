#pragma once
#include "SFML/Graphics.hpp" 
#include "globals.h"

class Cell
{
	// private data members


public:

	Cell();

	int cellType;

	//sf::Sprite level[MAX_ROWS][MAX_COLS];

	sf::Sprite cellSprite;
	sf::Texture wallTexture;
	sf::Texture pelletTexture;
	sf::Texture emptyTexture;
	sf::Texture extraLifeTexture;

	void loadImages();


};