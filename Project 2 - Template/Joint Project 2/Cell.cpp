#include "Cell.h"
#include <iostream>

Cell::Cell()
{
	if (!wallTexture.loadFromFile("ASSETS/IMAGES/wallCell.jpg"))
	{
		std::cout << "Error loading from file";
	}

	if (!pelletTexture.loadFromFile("ASSETS/IMAGES/bigpill.png"))
	{
		std::cout << "Error loading from file";
	}

	if (!emptyTexture.loadFromFile("ASSETS/IMAGES/emptyCell.png"))
	{
		std::cout << "Error loading from file";
	}
	
	if (!extraLifeTexture.loadFromFile("ASSETS/IMAGES/live.png"))
	{
		std::cout << "Error loading from file";
	}
}

void Cell::loadImages()
{

	
}
