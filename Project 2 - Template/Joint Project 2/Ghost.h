#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Ghost
{
	// private data members
	// the 4 textures for each look directions and the follower sprite 
	sf::Texture ghostTextureNorth;
	sf::Texture ghostTextureSouth;
	sf::Texture ghostTextureWest;
	sf::Texture ghostTextureEast;
	

	int ghostLookDirection; // followers look direction

	int row;
	int col;

	int xPos;
	int yPos;

public:

	Ghost();
	sf::Sprite ghostSprite;

	void loadGhostImage();
	sf::Sprite getGhostbody();

	int getRow();
	int getCol();

	void ghostMoveLeft();  //
	void ghostMoveRight(); // functions for moving the ghost up , down , left and right 
	void ghostMoveUp();	  //
	void ghostMoveDown();

	void resetGame();

	



};
