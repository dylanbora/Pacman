#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Pacman
{
	// private data members
	// the 4 textures for each look direction and the player sprite 
	sf::Texture pacmanTextureNorth;
	sf::Texture pacmanTextureSouth;
	sf::Texture pacmanTextureWest;
	sf::Texture pacmanTextureEast;
	sf::Sprite pacmanSprite;

	

	// private data members
	int pacmanLives; // the players health 
	int pacmanSpeed; // the players speed
	int pacmanLookDirection = 1; // the direction the player is facing 
	int playerScore = 0;
	
	int row;
	int col;


public:

	Pacman();

	void loadImages(); // function which loads all sprites for the player and the bullet 
	sf::Sprite getPacmanBody();
	void setPacmanPosition(int xPos, int yPos);
	void setPacmanSpeed(int t_speed);
	void setLookDirection(int t_direction);
	
	

	void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();

	int getRow();
	int getCol();

	void pacmanMazePosition();

	int getScore();
	void setScore(int t_score);

	int getLives();
	void setLives(int t_lives);
	void increaseScore();
	void decreaseLives();
	void increaseLives();

	void collisionReset();
	void resetGame();
	void roundReset();
	

};