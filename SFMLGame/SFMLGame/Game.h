#pragma once

#include<iostream>
#include<vector>
#include<ctime>
#include<sstream>
#include<string>
#include<fstream>
#include<future>

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
	sf::Vector2f mousePosView;



	//resources
	sf::Font font;

	//text
	sf::Text uiText;
	sf::Text infoUpdate;

	//game logic
	bool endGame;
	bool movedRight;
	bool evenLevel;
	unsigned points;
	int health;
	float enemySpawnTimer;
	float enemySpawnTimeMax;
	float movespeed;
	float sidespeed;
	float invertsidespeed;
	int maxEnemies;
	bool mouseHeld;

	unsigned highscore[5];
	int temp;


	//game objects
	std::vector<sf::RectangleShape> enemies;
	sf::RectangleShape enemy;


	//private functions

	void initiVariables();
	void initWindow();
	void initFonts();
	void initText();
	void initEnemies();
public:
	//constructors / destructors
	Game();
	virtual ~Game();

	//accessors
	const bool getWindowIsOpen() const;
	const bool getEndGame() const;


	//functions 
	void spawnEnemy();


	void pollEvents();
	void updateMousePositions();
	void updateText();
	void updateEnemies();
	void updateDifficulty();
	void updateHighscore();
	void displayHighscore();
	void update();


	void renderText(sf::RenderTarget& target);
	void renderEnemies(sf::RenderTarget& target);
	void render(); 
};

