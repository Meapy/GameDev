#include <iostream>
#include "Game.h"

//using namespace sf;

int main()
{
	//init game engine
	Game game;


	//game loop
	while (game.getWindowIsOpen()) 
	{
		
		//update
		game.update();

		//render
		game.render();

	}

	


	return 0;
}