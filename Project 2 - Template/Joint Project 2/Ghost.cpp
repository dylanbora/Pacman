// Ghost function definitions here

#include "Ghost.h"
#include "Globals.h"

Ghost::Ghost()
{

	row = (rand() % 11) + 2;
	col = (rand() % 11) + 2;

	xPos = col * 32;
	yPos = row * 32;

	loadGhostImage();
	ghostSprite.setTexture(ghostTextureSouth);
	ghostSprite.setPosition(xPos, yPos);


}

void Ghost::loadGhostImage()
{
	if (!ghostTextureSouth.loadFromFile("ASSETS/IMAGES/greenghost32down.png")) 
	{
		std::cout << "error with GREEN GHOST texture file";
	}

	if (!ghostTextureNorth.loadFromFile("ASSETS/IMAGES/greenghost32up.png")) 
	{
		std::cout << "error with GREEN GHOST texture file";
	}

	if (!ghostTextureWest.loadFromFile("ASSETS/IMAGES/greenghost32left.png")) 
	{
		std::cout << "error with GREEN GHOST texture file";
	}

	if (!ghostTextureEast.loadFromFile("ASSETS/IMAGES/greenghost32right.png")) 
	{
		std::cout << "error with GREEN GHOST texture file";
	}

}

sf::Sprite Ghost::getGhostbody()
{
	return ghostSprite;
}


int Ghost::getRow()
{
	return row;
}

int Ghost::getCol()
{
	return col;
}

void Ghost::ghostMoveLeft()
{
	ghostSprite.setTexture(ghostTextureWest);

	col--;

	xPos = col * 32;
	yPos = row * 32;

	ghostSprite.setPosition(xPos, yPos);
	
}

void Ghost::ghostMoveRight()
{
	ghostSprite.setTexture(ghostTextureEast);
	
	col++;
	xPos = col * 32;
	yPos = row * 32;

	ghostSprite.setPosition(xPos, yPos);
}

void Ghost::ghostMoveUp()
{
	ghostSprite.setTexture(ghostTextureNorth);
		
	row--;
	xPos = col * 32;
	yPos = row * 32;

	ghostSprite.setPosition(xPos, yPos);
}

void Ghost::ghostMoveDown()
{
	ghostSprite.setTexture(ghostTextureSouth);

	row++;
	xPos = col * 32;
	yPos = row * 32;

	ghostSprite.setPosition(xPos, yPos);
}

void Ghost::resetGame()
{
	ghostSprite.setTexture(ghostTextureSouth);
	
	row = (rand() % 12) + 2;
	col = (rand() % 12) + 2;

	xPos = col * 32;
	yPos = row * 32;

	ghostSprite.setPosition(xPos, yPos);
}


