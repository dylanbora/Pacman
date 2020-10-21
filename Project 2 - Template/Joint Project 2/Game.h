// Game class declaration
#pragma once

#include "SFML/Graphics.hpp" 
#include <iostream>
#include <cstdlib>  // include support for randomizing
#include <ctime>   // supports ctime function


#include "Cell.h"   // include Cell header file
#include "Pacman.h"   // include Pacman header file
#include "Ghost.h"   // include Ghost header file
#include "Globals.h"

class Game
{
	// private data members
	// put your game objects here eg 2D array and Pacman object and 1D array of ghosts objects etc.


	sf::RenderWindow window;
	Pacman myPlayer;
	Ghost ghost[MAX_GHOSTS];
	
public:

	
	

	sf::Font m_font;  // font for writing text
	sf::Text m_message;  // text to write on the screen
	sf::Text m_scoreText;
	sf::Text m_healthText;
	sf::Text m_gameOverText;
	sf::Text m_instructionsText;
	sf::Text m_inputNameText;
	sf::Text m_highScoreText;
	sf::Text m_levelText;

	int highScore = 0;

	bool gameOver = false;
	bool instructions = false;
	bool gamePlay = false;
	bool enterName = true;
	bool levelOne = true;

	std::string playerName = "";

	Cell level[MAX_ROWS][MAX_COLS]; // pass to move function in ghost.cpp
	sf::Texture wallTexture;
	sf::Texture pelletTexture;
	sf::Texture emptyTexture;

	sf::Clock movementCounter;
	sf::Time movementTimer = sf::seconds(0.6f);
	sf::Time collisionTime = sf::seconds(0.1f);
	
	


public:	  // declaration of member functions	
	Game();  // default constructor
	void	LoadContent();
	void	run();
	void	update();
	void	draw();
	void	setUpMaze();
	void	drawMaze();
	void	pickupCheck();

	bool    canMoveUp(int t_row, int t_col);
	bool    canMoveDown(int t_row, int t_col);
	bool    canMoveLeft(int t_row, int t_col);
	bool    canMoveRight(int t_row, int t_col);

	void ghostMovement();
	void gameCollisions();
	void isGameOver();
	void resetGame();
	void highScoreCheck();


	
};

