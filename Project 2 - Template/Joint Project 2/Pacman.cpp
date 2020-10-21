// Pacman function definitions here

#include "Pacman.h"
#include "Globals.h"
#include "Game.h"


Pacman::Pacman()
{

	int xPos = SCREEN_WIDTH / 2;  //
	int yPos = SCREEN_HEIGHT / 2; // sets the players position to the centre of the screen
	setPacmanPosition(xPos, yPos);  // set the position of the players sprite
	pacmanLookDirection = EAST; // the players starting look direction
	playerScore = 0; // the players score
	pacmanLives = 3; // the players health 

	row = 7;
	col = 7;
	loadImages();

}
	

void Pacman::loadImages()
{

	if (!pacmanTextureNorth.loadFromFile("ASSETS/IMAGES/pacmanUp.png"))
	{
		std::cout << "error with player north player file";
	}

	if (!pacmanTextureWest.loadFromFile("ASSETS/IMAGES/pacmanLeft.png"))
	{
		std::cout << "error with player image move left file";
	}

	if (!pacmanTextureEast.loadFromFile("ASSETS/IMAGES/pacmanRight.png"))
	{
		std::cout << "error with fireball image right file";
	}

	if (!pacmanTextureSouth.loadFromFile("ASSETS/IMAGES/pacmanDown.png"))
	{
		std::cout << "error with player image file";
	}

	pacmanSprite.setTexture(pacmanTextureEast);
}

sf::Sprite Pacman::getPacmanBody()
{

	return pacmanSprite;

}

void Pacman::setPacmanPosition(int xPos, int yPos)
{
	pacmanSprite.setPosition(xPos, yPos);

}

void Pacman::setPacmanSpeed(int t_speed)
{
	pacmanSpeed = t_speed;

}

void Pacman::setLookDirection(int t_direction)
{
	pacmanLookDirection = t_direction;
}

void Pacman::moveLeft()
{

	if (col > 1)
	{
		col--;
	}

	pacmanLookDirection = WEST;
	pacmanSprite.setTexture(pacmanTextureWest);

}

void Pacman::moveRight()
{

	pacmanLookDirection = EAST;
	pacmanSprite.setTexture(pacmanTextureEast);

	if (col < MAX_COLS - 2)
	{
		col++;
	}

}

void Pacman::moveUp()
{

	pacmanLookDirection = NORTH;
	pacmanSprite.setTexture(pacmanTextureNorth);

	if (row > 1)
	{
		row--;
	}

}

void Pacman::moveDown()
{
	pacmanLookDirection = SOUTH;
	pacmanSprite.setTexture(pacmanTextureSouth);

	if (row < MAX_ROWS - 2)
	{
		row++;
	}
}

int Pacman::getRow()
{
	return row;
}

int Pacman::getCol()
{
	return col;
}

void Pacman::pacmanMazePosition()
{
	int xPos = col * 32;
	int yPos = row * 32;
	pacmanSprite.setPosition(xPos, yPos); // put in move functions 
}

int Pacman::getScore()
{
	return playerScore;
}

void Pacman::setScore(int t_score)
{
	playerScore = t_score;
}

int Pacman::getLives()
{
	return pacmanLives;
}
void Pacman::setLives(int t_lives)
{
	pacmanLives = t_lives;
}

void Pacman::increaseScore() // increase score
{
	playerScore ++;
}

void Pacman::decreaseLives()
{

	pacmanLives--;

}

void Pacman::increaseLives()
{
	pacmanLives++;
}

void Pacman::collisionReset()
{
	row = 7;
	col = 7;
	int xPos = col * 32;
	int yPos = row * 32;
	pacmanSprite.setPosition(xPos, yPos);
}

void Pacman::resetGame()
{
	    playerScore = 0;
	    pacmanLives = 3;
		pacmanLookDirection = EAST;
		row = 7;
		col = 7;
		int xPos = col * 32;
		int yPos = row * 32;
		pacmanSprite.setPosition(xPos, yPos); // put in move functions 

}

void Pacman::roundReset()
{
	pacmanLookDirection = EAST;
	row = 7;
	col = 7;
	int xPos = col * 32;
	int yPos = row * 32;
	pacmanSprite.setPosition(xPos, yPos); // put in move functions 
}



