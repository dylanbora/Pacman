// Name: 
// Login: 
// Date: 
// Approximate time taken: 
//---------------------------------------------------------------------------
// Project 2 -  Description Template
// ---------------------------------------------------------------------------
// Known Bugs:
// List your bugs here

//////////////////////////////////////////////////////////// 
// Headers for SFML projects
// include correct library file for release and debug versions
// include iostream for console window output
// include 
//////////////////////////////////////////////////////////// 

#ifdef _DEBUG 
#pragma comment(lib,"sfml-graphics-d.lib") 
#pragma comment(lib,"sfml-audio-d.lib") 
#pragma comment(lib,"sfml-system-d.lib") 
#pragma comment(lib,"sfml-window-d.lib") 
#pragma comment(lib,"sfml-network-d.lib") 
#else 
#pragma comment(lib,"sfml-graphics.lib") 
#pragma comment(lib,"sfml-audio.lib") 
#pragma comment(lib,"sfml-system.lib") 
#pragma comment(lib,"sfml-window.lib") 
#pragma comment(lib,"sfml-network.lib") 
#endif 
#pragma comment(lib,"opengl32.lib") 
#pragma comment(lib,"glu32.lib") 

#include "Game.h"   // include Game header file
#include "Globals.h"
#include "Pacman.h"
#include "Cell.h"
#include "Ghost.h"



int main()
{
	Game aGame;
	aGame.LoadContent();
	aGame.run();
	Pacman();
	Cell();
	Ghost();

	return 0;
}

Game::Game() : window(sf::VideoMode(480, 568), "Project 2")
// Default constructor
{
	setUpMaze();

}


void Game::LoadContent()
// Load the font file & set up message
{
	if (!m_font.loadFromFile("ASSETS/FONTS/BebasNeue.otf"))
	{
		std::cout << "error with font file file";
	}

	m_message.setFont(m_font);
	m_message.setCharacterSize(30);
	m_message.setFillColor(sf::Color::White);
	m_message.setPosition(160, 15);
	
	m_scoreText.setFont(m_font);
	m_scoreText.setCharacterSize(24);
	m_scoreText.setFillColor(sf::Color::White);
	m_scoreText.setPosition(140, 510);

	m_healthText.setFont(m_font);
	m_healthText.setCharacterSize(24);
	m_healthText.setFillColor(sf::Color::White);
	m_healthText.setPosition(240, 510);

	m_gameOverText.setFont(m_font);
	m_gameOverText.setCharacterSize(30);
	m_gameOverText.setFillColor(sf::Color::White);
	m_gameOverText.setPosition(90, 270);

	m_instructionsText.setFont(m_font);
	m_instructionsText.setCharacterSize(18);
	m_instructionsText.setFillColor(sf::Color::White);
	m_instructionsText.setPosition(100, 70);

	m_inputNameText.setFont(m_font);
	m_inputNameText.setCharacterSize(24);
	m_inputNameText.setFillColor(sf::Color::White);
	m_inputNameText.setPosition(20, 270);

	m_highScoreText.setFont(m_font);
	m_highScoreText.setCharacterSize(24);
	m_highScoreText.setFillColor(sf::Color::White);
	m_highScoreText.setPosition(340, 510);

	m_levelText.setFont(m_font);
	m_levelText.setCharacterSize(24);
	m_levelText.setFillColor(sf::Color::White);
	m_levelText.setPosition(340, 510);

}


void Game::run()
{
	srand(time(nullptr)); // set the seed once
	sf::Time timePerFrame = sf::seconds(1.0f / 60.0f);
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	// the clock object keeps the time.
	sf::Clock clock;


	clock.restart();

	while (window.isOpen())
	{
		// check if the close window button is clicked on
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (enterName == true)
			{
				if (event.type == sf::Event::TextEntered)
				{
					bool backSpace_down = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::BackSpace);

					if (backSpace_down == true && playerName.length() != 0)
					{
						playerName.pop_back();
					}

					else if (event.text.unicode < 123 && event.text.unicode > 64)
					{
						if (event.text.unicode > 96 || event.text.unicode < 91)
						{
							playerName.push_back((char)event.text.unicode);
						}
					}
				}
			}
		
			if (gameOver == false)
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
				{
					if (canMoveLeft(myPlayer.getRow(), myPlayer.getCol()) == true)
					{
						myPlayer.moveLeft(); // calls the move player left function when the left key is pressed 
					}
				}

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
				{
					if (canMoveRight(myPlayer.getRow(), myPlayer.getCol()) == true)
					{
						myPlayer.moveRight(); // calls player move player right function when the right key is pressed
					}
				}

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
				{
					if (canMoveUp(myPlayer.getRow(), myPlayer.getCol()) == true)
					{
						myPlayer.moveUp(); // calls the move plater up fucntion when the up key is pressed
					}
				}

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
				{
					if (canMoveDown(myPlayer.getRow(), myPlayer.getCol()) == true)
					{
						myPlayer.moveDown(); // calls the move player down function when the down key is pressed 
					}
				}
			}
		}
		

		//get the time since last update and restart the clock
		timeSinceLastUpdate += clock.restart();

		//update every 60th of a second
		//only when the time since last update is greater than 1/60 update the world.
		if (timeSinceLastUpdate > timePerFrame)
		{

			update();
			draw();
			pickupCheck();
			isGameOver();

			if (movementCounter.getElapsedTime() >= movementTimer)
			{
				ghostMovement();
				movementCounter.restart();
			}

			if (enterName == true);
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) 
				{
					enterName = false;
					instructions = true;
				}
			}

			if (instructions == true)
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) 
				{
					instructions = false;
					gamePlay = true;
				}
			}

			if (gamePlay == true)
			{
				m_scoreText.setPosition(140, 510);
				m_highScoreText.setPosition(340, 510);
				m_inputNameText.setString("" + playerName);
				m_inputNameText.setPosition(40, 510);
			}

			if (gameOver == true)
			{
				highScoreCheck();
				m_scoreText.setCharacterSize(30),
				m_scoreText.setPosition(100, 100);
				m_highScoreText.setCharacterSize(30);
				m_highScoreText.setPosition(100, 130);

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) 
				{
					gameOver = false; //
					resetGame();             // when r is pressed game over is now false and the game resets by calling the reset game function
				}
			}

			// reset the timeSinceLastUpdate to 0 
			timeSinceLastUpdate = sf::Time::Zero;
		}
	}  // end while loop

}

void Game::update()
// This function takes the keyboard input and updates the game world
{

	myPlayer.pacmanMazePosition();
	pickupCheck();
	gameCollisions();
	isGameOver();	
	

}


void Game::draw()
// This function draws the game world
{
	// Clear the screen and draw your game sprites

	m_gameOverText.setString("GAME OVER ! Press R to Restart"); // tells the player to press R to restart if the payer has has been killed
	m_scoreText.setString("Score: " + std::to_string(myPlayer.getScore()));
	m_healthText.setString("Lives: " + std::to_string(myPlayer.getLives()));
	m_instructionsText.setString("Game Instructions: \n  \n Move around the maze using the 4 arrow keys \n \n Collect the yellow pellets to increase your score \n \n If you collide with a ghost you lose a life \n \n Gain an extra life by collecting a Heart \n \n If your lives reach 0 the game is over. \n \n \n \n \n \n \n \n \n \n Press the S key the start playing.");
	m_highScoreText.setString("Highscore: " + std::to_string(highScore));
	m_message.setString("Pelletman:");

	if (enterName == true)
	{
		window.clear();
		myPlayer.setPacmanPosition(280 , 18);
		window.draw(myPlayer.getPacmanBody());
		window.draw(m_message);
		m_inputNameText.setString("Please Enter Your Name: " + playerName + " \n \n \n \n \n \n \n \n \n                              Press Enter to continue:");
		window.draw(m_inputNameText);
	}

	else if (instructions == true)
	{
		window.clear();
		window.draw(m_instructionsText);
	}
	else if ( gamePlay == true)
	{

		window.clear();
		drawMaze();
		window.draw(m_scoreText);
		window.draw(m_healthText);
		window.draw(m_highScoreText);
		window.draw(m_inputNameText);
		

		for (int row = 0; row < MAX_ROWS; row++)
		{
			for (int col = 0; col < MAX_COLS; col++)
			{
				window.draw(level[row][col].cellSprite);
			}
		}

		for (int i = 0; i < MAX_GHOSTS; i++)
		{
			window.draw(ghost[i].getGhostbody());
		}

		window.draw(myPlayer.getPacmanBody());
	}

	if ( gameOver == true)
	{
		window.clear();
		window.draw(m_gameOverText);
		window.draw(m_scoreText);
		window.draw(m_highScoreText);
		
		for (int i = 0; i < MAX_GHOSTS; i++)
		{
			window.draw(ghost[i].getGhostbody());
		}
	}

	/*if (myPlayer.getScore() > 5)
	{
		window.clear();
		m_levelText.setString("Level one Complete ! Press Enter to Restart");
		window.draw(m_levelText);
	}*/

	window.display();
}



void Game::setUpMaze()
// Setup the sprites for the 2D maze game
{
	if (levelOne == true)
	{
		int theMaze[MAX_ROWS][MAX_COLS] =
		{

		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,1,1,1,1,1,1,0,1,1,1,1,1,1,0 },
		{ 0,1,0,1,0,0,1,0,1,0,0,1,0,1,0 },
		{ 0,1,0,1,1,0,1,1,1,0,1,1,0,1,0 },
		{ 0,1,0,0,1,0,0,1,0,0,1,0,0,1,0 },
		{ 0,1,1,1,1,1,1,1,1,1,1,1,1,1,0 },
		{ 0,3,0,1,0,1,0,1,0,1,0,1,0,1,0 },
		{ 0,0,0,1,0,1,0,2,0,1,0,1,0,0,0 },
		{ 0,1,0,1,0,1,0,0,0,1,0,1,0,3,0 },
		{ 0,1,1,1,1,1,1,0,1,1,1,1,1,1,0 },
		{ 0,1,0,0,1,0,1,0,1,0,1,0,0,1,0 },
		{ 0,1,0,1,1,0,1,1,1,0,1,1,0,1,0 },
		{ 0,1,0,1,0,0,1,0,1,0,0,1,0,1,0 },
		{ 0,1,1,1,1,1,1,0,1,1,1,1,1,1,0 },
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 }

		};

		for (int row = 0; row < MAX_ROWS; row++)
		{
			for (int col = 0; col < MAX_COLS; col++)
			{
				level[row][col].cellType = theMaze[row][col];
				level[row][col].cellSprite.setPosition(col * 32, row * 32);
			}
		}
	}

}


void Game::drawMaze()
// Draw the 2D maze
{
	for (int row = 0; row < MAX_ROWS; row++)
	{
		for (int col = 0; col < MAX_COLS; col++)
		{
			
			if (level[row][col].cellType == 0)
			{
				level[row][col].cellSprite.setTexture(level[row][col].wallTexture);
			}

			else if (level[row][col].cellType == 1)
			{
				level[row][col].cellSprite.setTexture(level[row][col].pelletTexture);
			}

			else if (level[row][col].cellType == 2)
			{
				level[row][col].cellSprite.setTexture(level[row][col].emptyTexture);
			}

			else if (level[row][col].cellType == 3)
			{
				level[row][col].cellSprite.setTexture(level[row][col].extraLifeTexture);
			}

		}
	}
}

void Game::pickupCheck() // this function checks if the player has moved into the same cell as a pellet or any other of the pickups.
{
	for (int row = 0; row < MAX_ROWS; row++) 
	{
		for (int col = 0; col < MAX_COLS; col++)
		{
			if (level[row][col].cellType == 1) 
			{
				if (myPlayer.getRow() == row && myPlayer.getCol() == col) // this checks if the cell pacman is in has a pellet
				{
					level[row][col].cellType = 2; // if it does it sets the cell texture to empty 
					myPlayer.increaseScore(); // then increases the player score when he eats a pellet 
				}
			}

			if (level[row][col].cellType == 3) // this checks if the cell pacman is in has a extra life pickup
			{
				if (myPlayer.getRow() == row && myPlayer.getCol() == col)
				{
					level[row][col].cellType = 2; // if it does it sets the cell texture to empty 
					myPlayer.increaseLives(); // then increases his number of lives 
				}
			}
		}
	}
}

bool Game::canMoveUp(int t_row, int t_col)
{
	int cellAbove = t_row - 1; // checks cell above the player

	if (level[cellAbove][t_col].cellType == 0) // if any cell being used as a wall
	{
		return false;
	}
	else
	{
		return true;
	}
}

bool Game::canMoveDown(int t_row, int t_col)
{
	int cellBelow = t_row + 1; // checks cell below the player

	if (level[cellBelow][t_col].cellType == 0) // if any cell being used as a wall
	{
		return false;
	}
	else
	{
		return true;
	}
}

bool Game::canMoveRight(int t_row, int t_col)
{
	int cellToRight = t_col + 1; // checks cell to the right of the player

	if (level[t_row][cellToRight].cellType == 0) // if any cell being used as a wall
	{
		return false;
	}
	else
	{
		return true;
	}

}

bool Game::canMoveLeft(int t_row, int t_col)
{
	int cellToLeft = t_col - 1; // checks cell to the left of the player

	if (level[t_row][cellToLeft].cellType == 0) // if any cell being used as a wall
	{
		return false;
	}
	else
	{
		return true;
	}
}

void Game::ghostMovement()
{
	
		for (int i = 0; i < MAX_GHOSTS - 2; i++)
		{
			int moveDirection = (rand() % 4) + 1;

			if (moveDirection == 1)
			{
				if (canMoveDown(ghost[i].getRow(), ghost[i].getCol()) == true)
				{
					ghost[i].ghostMoveDown(); //moves ghost down	
				
				}
				else
				{
					moveDirection = (rand() % 4) + 1;
				}
			}

			if (moveDirection == 2)
			{
				if (canMoveUp(ghost[i].getRow(), ghost[i].getCol()) == true)
				{
					ghost[i].ghostMoveUp(); //moves ghost down	
				}
				else
				{
					moveDirection = (rand() % 4) + 1;
				}
			}

			if (moveDirection == 3)
			{
				if (canMoveRight(ghost[i].getRow(), ghost[i].getCol()) == true)
				{
					ghost[i].ghostMoveRight(); 
				}
				else
				{
					moveDirection = (rand() % 4) + 1;
				}
			}

			if (moveDirection == 4)
			{
				if (canMoveLeft(ghost[i].getRow(), ghost[i].getCol()) == true)
				{
					ghost[i].ghostMoveLeft(); //moves ghost down	
				}
				else
				{
					moveDirection = rand() % +1;;
				}
			}

		}

		for (int i = 2; i < MAX_GHOSTS; i++)
		{
			if (ghost[i].getRow() < myPlayer.getRow()) // above 
			{
				if (canMoveDown(ghost[i].getRow(), ghost[i].getCol()) == true) // if can move down
				{
					ghost[i].ghostMoveDown(); //moves ghost down
				}
				else if (canMoveLeft(ghost[i].getRow(), ghost[i].getCol()) == true) // cant go down go left
				{
					ghost[i].ghostMoveLeft(); // moves left
				}
				else if (canMoveUp(ghost[i].getRow(), ghost[i].getCol()) == true) // if cant move right move up
				{
					ghost[i].ghostMoveUp(); // moves up
				}
				else if (canMoveUp(ghost[i].getRow(), ghost[i].getCol()) == true) // if cant move right move up
				{
					ghost[i].ghostMoveRight(); // moves up
				}
			}

			if (ghost[i].getRow() > myPlayer.getRow()) // if player is below  ghost
			{
				if (canMoveUp(ghost[i].getRow(), ghost[i].getCol()) == true) // if can move up
				{
					ghost[i].ghostMoveUp(); //moves ghost down
				}
				else if (canMoveRight(ghost[i].getRow(), ghost[i].getCol()) == true) // if can move right
				{
					ghost[i].ghostMoveRight();  // moves right
				}
				else if (canMoveUp(ghost[i].getRow(), ghost[i].getCol()) == true) // if cant move right move up
				{
					ghost[i].ghostMoveDown(); // moves up
				}
				else if (canMoveUp(ghost[i].getRow(), ghost[i].getCol()) == true) // if cant move right move up
				{
					ghost[i].ghostMoveLeft(); // moves up
				}
			}


			if (ghost[i].getCol() > myPlayer.getCol()) // if player is right of ghost
			{
				if (canMoveLeft(ghost[i].getRow(), ghost[i].getCol()) == true)
				{
					ghost[i].ghostMoveLeft(); // move left
				}
				else if (canMoveDown(ghost[i].getRow(), ghost[i].getCol()) == true) // if cant move right move down
				{
					ghost[i].ghostMoveDown(); // move down
				}
				else if (canMoveUp(ghost[i].getRow(), ghost[i].getCol()) == true) // if cant move right move up
				{
					ghost[i].ghostMoveUp(); // moves up
				}
				else if (canMoveUp(ghost[i].getRow(), ghost[i].getCol()) == true) // if cant move right move up
				{
					ghost[i].ghostMoveRight(); // moves up
				}
			}


			if (ghost[i].getCol() < myPlayer.getCol())  // if player is right of ghost
			{
				if (canMoveRight(ghost[i].getRow(), ghost[i].getCol()) == true) // if can move me right
				{
					ghost[i].ghostMoveRight(); // move right
				}
				else if (canMoveUp(ghost[i].getRow(), ghost[i].getCol()) == true) // if cant move right move up
				{
					ghost[i].ghostMoveUp(); // moves up
				}
				else if (canMoveUp(ghost[i].getRow(), ghost[i].getCol()) == true) // if cant move right move up
				{
					ghost[i].ghostMoveDown(); // moves up
				}
				else if (canMoveUp(ghost[i].getRow(), ghost[i].getCol()) == true) // if cant move right move up
				{
					ghost[i].ghostMoveLeft(); // moves up
				}
			}
		}
	
}

void Game::gameCollisions() // this function checks for collisions between the player and the ghosts by checking if they are in the same cell
{
	for (int i = 0; i < MAX_GHOSTS; i++)
	{
		if (myPlayer.getRow() == ghost[i].getRow())
		{
			if (myPlayer.getCol() == ghost[i].getCol()) 
			{
				myPlayer.decreaseLives();
				myPlayer.collisionReset();
			}
		}
	}
}

void Game::isGameOver() // this fucntion changes the game over bool to true when the players lives reaches 0
{
	if (myPlayer.getLives() <= 0)
	{
		gameOver = true;
	}
}

void Game::resetGame() // this function resets the level and calls both of the reset player and reset ghost functions 
{
	
	setUpMaze();
	drawMaze();
	m_scoreText.setPosition(90, 510);
	m_scoreText.setCharacterSize(24);
	m_highScoreText.setPosition(290, 510);
	m_highScoreText.setCharacterSize(24);
	myPlayer.resetGame(); // resets pacmans data
	ghost[MAX_GHOSTS].resetGame(); // resets the ghosts data
		
}

void Game::highScoreCheck() // this function checks if the players current score is higher than the previous score 
{
	if (gameOver == true)
	{
		if (myPlayer.getScore() > highScore)
		{
			highScore = myPlayer.getScore(); // if it is , it stores the new highest score in the highScore variable
		}
	}
}


