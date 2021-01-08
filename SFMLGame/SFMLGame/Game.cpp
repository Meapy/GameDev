#include "Game.h"


//private functions 
void Game::initiVariables()
{
	window = nullptr;

	endGame = false;
	points = 0;
	health = 100;
	enemySpawnTimeMax = 25.f;
	enemySpawnTimer = enemySpawnTimeMax;
	maxEnemies = 8;
	mouseHeld = false;

}

void Game::initWindow()
{
	videoMode.height = 720;
	videoMode.width = 1280;

	window = new sf::RenderWindow(videoMode, "Game_Title", sf::Style::Titlebar | sf::Style::Close);
	window->setFramerateLimit(75);
}
void Game::initFonts()
{
	if (!font.loadFromFile("Fonts/FFF_Tusj.ttf"))
	{
		std::cout << "failed to load font";
	}
}
void Game::initText()
{
	uiText.setFont(font);
	uiText.setCharacterSize(30);
	uiText.setFillColor(sf::Color::Red);
	uiText.setString("None");
}
void Game::initEnemies()
{
	enemy.setPosition(10.f,10.f);
	enemy.setSize(sf::Vector2f(100.f, 100.f));
	enemy.setFillColor(sf::Color::Green);
	//this->enemy.setOutlineColor(sf::Color::White);
	//this->enemy.setOutlineThickness(2.f);

}
//constuctors / destructors 
Game::Game()
{
	initiVariables();
	initWindow();
	initFonts();
	initText();
	initEnemies();
}

Game::~Game()
{
	delete window;
}

const bool Game::getWindowIsOpen() const
{
	return window->isOpen();
}

const bool Game::getEndGame() const
{
	return endGame;
}


//functions


void Game::spawnEnemy()
{
	enemy.setPosition(
		static_cast<float>(rand()%static_cast<int>(window->getSize().x - enemy.getSize().x)),
		0.f
	);

	//randomize enemy type
	int type = rand() % 5;
	switch (type)
	{
	case 0:
		enemy.setFillColor(sf::Color::Cyan);
		enemy.setSize(sf::Vector2f(20.f, 20.f));
		break;	
	case 1:
		enemy.setFillColor(sf::Color::Magenta);
		enemy.setSize(sf::Vector2f(40.f, 40.f));
		break;	
	case 2:
		enemy.setFillColor(sf::Color::Green);
		enemy.setSize(sf::Vector2f(70.f, 70.f));
		break;;	
	case 3:
		enemy.setFillColor(sf::Color::Blue);
		enemy.setSize(sf::Vector2f(100.f, 100.f));
		break;
	default:
		break;
	}

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
	mousePosWindow = sf::Mouse::getPosition(*window);
	mousePosView = window->mapPixelToCoords(mousePosWindow);
}

void Game::updateText()
{
	std::stringstream ss;

	ss << "Score:"<< points
		<< "\nHealth:" << health;
	uiText.setString(ss.str());

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
	for (int i =0; i < enemies.size(); i++)
	{
		bool deleted = false;
		enemies[i].move(0.f,2.f);

		//if enemey gets past the bottom of the screen
		if (enemies[i].getPosition().y > window->getSize().y)
		{
			enemies.erase(enemies.begin() + i);
			health -= 5;
			std::cout << "health:" << health << "\n";
		}

	}

	//check if clicked upon

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		
		if (mouseHeld == false) //stops from mouse being held 
		{
			mouseHeld = true;
			bool deleted = false;
			for (size_t i = 0; i < enemies.size() && deleted == false; i++)
			{
				if (enemies[i].getGlobalBounds().contains(mousePosView))
				{
					
					//gain points
					if (enemies[i].getFillColor() == sf::Color::Cyan)
					{
						points += 25;
						std::cout << "points:" << points << "\n";
					}
					else if (enemies[i].getFillColor() == sf::Color::Magenta)
					{
						points += 20;
						std::cout << "points:" << points << "\n";
					}
					else if (enemies[i].getFillColor() == sf::Color::Green)
					{
						points += 15;
						std::cout << "points:" << points << "\n";
					}
					else if (enemies[i].getFillColor() == sf::Color::Blue)
					{
						points += 10;
						std::cout << "points:" << points << "\n";
					}

					//delete the enemy
					deleted = true;
					enemies.erase(enemies.begin() + i);
				}
			}
		}
		
	}
	else
	{
		mouseHeld = false;
	}
}

void Game::update()
{
	pollEvents();

	if (!endGame)
	{
		updateMousePositions();

		updateText();

		updateEnemies();
	}

	//end game condition
	if (health <= 0)
	{
		endGame = true;
	}
	
}

void Game::renderText(sf::RenderTarget& target)
{
	target.draw(uiText);
}

void Game::renderEnemies(sf::RenderTarget& target)
{
	for (auto& i : enemies)
	{
		target.draw(i);  //renders the enemies
	}

}

void Game::render()
{
	window->clear();

	//draw game objects
	renderEnemies(*window);
	renderText(*window);


	window->display();
}

//functions 