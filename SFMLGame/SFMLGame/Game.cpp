#include "Game.h"


//private functions 
void Game::initiVariables()
{
	this->window = nullptr;

	points = 0;
	enemySpawnTimeMax = 1000.f;
	enemySpawnTimer = enemySpawnTimeMax;
	maxEnemies = 10;

}

void Game::initWindow()
{
	this->videoMode.height = 720;
	this->videoMode.width = 1280;

	this->window = new sf::RenderWindow(this->videoMode, "Game_Title", sf::Style::Titlebar | sf::Style::Close);
	this->window->setFramerateLimit(75);
}
void Game::initEnemies()
{
	this->enemy.setPosition(10.f,10.f);
	this->enemy.setSize(sf::Vector2f(100.f, 100.f));
	this->enemy.setScale(sf::Vector2f(0.5f, 0.5f));
	this->enemy.setFillColor(sf::Color::Green);
	this->enemy.setOutlineColor(sf::Color::White);
	this->enemy.setOutlineThickness(2.f);

}
//constuctors / destructors 
Game::Game()
{
	this->initiVariables();
	this->initWindow();
	this->initEnemies();
}

Game::~Game()
{
	delete this->window;
}

const bool Game::getWindowIsOpen() const
{
	return this->window->isOpen();
}


//functions


void Game::spawnEnemy()
{
	enemy.setPosition(
		static_cast<float>(rand()%static_cast<int>(window->getSize().x - enemy.getSize().x)),
		0.f
	);

	enemy.setFillColor(sf::Color::Blue);
	//spawns the enemy
	enemies.push_back(enemy);
}

void Game::pollEvents()
{
	while (window->pollEvent(ev))
	{
		switch (ev.type)
		{
		case sf::Event::Closed:
			window->close();
			break;
		case sf::Event::KeyPressed:
			if (ev.key.code == sf::Keyboard::Escape)
			{
				window->close();
			}
			break;
		}
	}
}

void Game::updateMousePositions()
{
	this->mousePosWindow = sf::Mouse::getPosition(*window);
}

void Game::updateEnemies()
{
	//updates enemy spawn timer
	if (enemies.size() < maxEnemies)
	{
		if (enemySpawnTimer >= enemySpawnTimeMax)
		{
			//spawn enemy and reset timer
			spawnEnemy();
			enemySpawnTimer = 0.f;
		}
		else
		{
			enemySpawnTimer += 1.f;
		}
	}
	//move the enemies
	for (auto &i : enemies)
	{
		i.move(0.f,1.f);
	}
	
}

void Game::update()
{
	this->pollEvents();

	this->updateMousePositions();
	
	this->updateEnemies();
	
}

void Game::renderEnemies()
{
	for (auto& i : enemies)
	{
		window->draw(i);  //renders the enemies
	}

}

void Game::render()
{
	window->clear();

	//draw game objects
	this->renderEnemies();
	


	window->display();
}

//functions 