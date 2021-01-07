#pragma once

#include<iostream>
#include<vector>
#include<ctime>

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

	//mouse positions
	sf::Vector2i mousePosWindow;

	//game logic
	int points;
	float enemySpawnTimer;
	float enemySpawnTimeMax;
	int maxEnemies;

	//game objects
	std::vector<sf::RectangleShape> enemies;
	sf::RectangleShape enemy;


	//private functions

	void initiVariables();
	void initWindow();
	void initEnemies();
public:
	//constructors / destructors
	Game();
	virtual ~Game();

	//accessors
	const bool getWindowIsOpen() const;


	//functions 
	void spawnEnemy();

	void pollEvents();
	void updateMousePositions();
	void updateEnemies();
	void update();
	void renderEnemies();
	void render(); 
};

