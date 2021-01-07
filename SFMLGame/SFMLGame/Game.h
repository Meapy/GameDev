#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

/*
	Class that acts as the game engine.
*/

class Game
{
private:
	//variables
	//window
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event ev;


	//private functions

	void initiVariables();
	void initWindow();
public:
	//constructors / destructors
	Game();
	virtual ~Game();

	//accessors
	const bool getWindowIsOpen() const;


	//functions 
	void pollEvents();
	void update();
	void render(); 
};

