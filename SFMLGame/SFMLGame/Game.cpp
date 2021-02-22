#include "Game.h"


//private functions 
void Game::initiVariables()
{
	window = nullptr;

	endGame = false;
	points = 0;
	health = 100;
	enemySpawnTimeMax = 20.f;
	sidespeed = 0.5f;
	invertsidespeed = sidespeed * -1.f;
	movespeed = 4.f;
	enemySpawnTimer = enemySpawnTimeMax;
	maxEnemies = 6;
	mouseHeld = false;
	movedRight = true;
	evenLevel = true;

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

	infoUpdate.setFont(font);
	infoUpdate.setCharacterSize(30);
	infoUpdate.setFillColor(sf::Color::White);
	infoUpdate.setString("None");
	infoUpdate.setPosition(window->getSize().x *.85 , 0);
}
void Game::initEnemies()
{
	enemy.setPosition(10.f,10.f);
	enemy.setSize(sf::Vector2f(100.f, 100.f));
	enemy.setFillColor(sf::Color::Green);


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
	std::vector<float> list{ 30,50,70,100 };
	sf::Color colors[] = { sf::Color::White, sf::Color::Black };
	int index = rand() % list.size();
	int direction = rand() % 2;
	float value = list[index];
	switch (type)
	{
	case 0:
		enemy.setFillColor(sf::Color::Cyan);
		enemy.setSize(sf::Vector2f(40.f, 40.f));
		enemy.setOutlineColor(colors[direction]);
		break;	
	case 1:
		enemy.setFillColor(sf::Color::Magenta);
		enemy.setSize(sf::Vector2f(50.f, 50.f));
		enemy.setOutlineColor(colors[direction]);
		break;	
	case 2:
		enemy.setFillColor(sf::Color::Green);
		enemy.setSize(sf::Vector2f(60.f, 60.f));
		enemy.setOutlineColor(colors[direction]);
		break;
	case 3:
		enemy.setFillColor(sf::Color::Blue);
		enemy.setSize(sf::Vector2f(90.f, 90.f));
		enemy.setOutlineColor(colors[direction]);
		break;
	case 4:
		enemy.setFillColor(sf::Color::Red);
		enemy.setSize(sf::Vector2f(value, value));
		enemy.setOutlineColor(colors[direction]);
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
			if (ev.key.code == sf::Keyboard::Enter && endGame == true)
			{
				endGame = false;
				health = 100;
				points = 0;
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
	std::stringstream ss;
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
		//check if enemy moves sideways
		if (enemies[i].getPosition().x > window->getSize().x - 50)
		{
			enemies[i].setOutlineColor(sf::Color::White);
		}
		else if (enemies[i].getPosition().x < 50 )
		{
			enemies[i].setOutlineColor(sf::Color::Black);
		}

		if (enemies[i].getPosition().x < window->getSize().x && enemies[i].getOutlineColor() == sf::Color::White)
		{
			
			enemies[i].move(invertsidespeed, movespeed);
		}
		else if (enemies[i].getPosition().x > 0 && enemies[i].getOutlineColor() == sf::Color::Black)
		{
			enemies[i].move(sidespeed, movespeed);
		}

		//if enemy gets past the bottom of the screen
		if (enemies[i].getPosition().y > window->getSize().y)
		{
			if (enemies[i].getFillColor() != sf::Color::Red)
			{
				if (enemies[i].getFillColor() == sf::Color::Black)
				{
					enemies.erase(enemies.begin() + i);
				}
				else
				{
					enemies.erase(enemies.begin() + i);
					health -= 5;
					std::cout << "health:" << health << "\n";
				}
				
			}
			else 
			{
				enemies.erase(enemies.begin() + i);
				std::cout << "health:" << health << "\n";
			}
			
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
					if (enemies[i].getFillColor() == sf::Color::Green)
					{
						points += 25;
						health += 5;
						std::cout << "points:" << points << "\n";
						std::cout << "health:" << health << "\n";
						ss << "Score: + 15 \n Health + 5";
						
					}
					else if (enemies[i].getFillColor() == sf::Color::Magenta)
					{
						points += 20;
						std::cout << "points:" << points << "\n";
						ss << "Score: + 20";
					}
					else if (enemies[i].getFillColor() == sf::Color::Cyan)
					{
						points += 15;
						std::cout << "points:" << points << "\n";
						ss << "Score: + 15";
					}
					else if (enemies[i].getFillColor() == sf::Color::Blue)
					{
						points += 10;
						std::cout << "points:" << points << "\n";
						ss << "Score: + 10";
					}
					else if (enemies[i].getFillColor() == sf::Color::Red )
					{
						if (points > 20) 
						{
							points -= 20;

							
						}
						health -= 5;
						std::cout << "points:" << points << "\n";
						std::cout << "health:" << health << "\n";
						ss << "Score: - 20 \n Health -5";
					}
					infoUpdate.setString(ss.str());
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

void Game::updateDifficulty()
{
	if(points < 1000 && evenLevel == true)
	{
		enemySpawnTimeMax = 15.f;
		sidespeed = 0.f;
		movespeed = 4.f;
		enemySpawnTimer = enemySpawnTimeMax;
		maxEnemies = 6;
		evenLevel = false;
	}
	else if (points >= 1000 && points < 2000 && evenLevel == false)
	{
		enemySpawnTimeMax = 15.f;
		sidespeed = 1.5f;
		movespeed = 5.f;
		enemySpawnTimer = enemySpawnTimeMax;
		maxEnemies = 8;
		evenLevel = true;
	}
	else if (points >= 2000 && evenLevel == true)
	{
		enemySpawnTimeMax = 10.f;
		sidespeed = 2.f;
		movespeed = 5.5f;
		enemySpawnTimer = enemySpawnTimeMax;
		maxEnemies = 10;
		evenLevel = false;
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

		updateDifficulty();

	}
	//end game condition
	if (health <= 0 && !endGame)
	{
	
		std::ifstream input("Resources/highscore.txt");
		int i = 0;
		while (input >> highscore[i])
		{
			std::cout << highscore[i]<<"\n";
			i++;
		}
		input.close();
		std::ofstream output("Resources/highscore.txt");
		int k;
		for (size_t i = 0; i < 5; i++)
		{
			if (points >= highscore[i])
			{
				temp = highscore[i];
				highscore[i] = points;			
				output << std::to_string(highscore[i]) << "\n";
				for(k = i + 1; k < 5; k++)
				{
					output << std::to_string(temp) << "\n";
					i++;
					temp = highscore[k];
					highscore[i] = temp;
				}
				break;
			}
			else 
			{

				output << std::to_string(highscore[i]) << "\n";
			}
		}
		output.close();
		for (int i = 0; i <= enemies.size(); i++)
		{
			enemies[i].setFillColor(sf::Color::Black);
		}
		endGame = true;
		updateText();


	} 
	if (endGame)
	{
		updateText();
		window->clear();
		std::stringstream highscores;
		std::stringstream message;
		message << "Press Enter\n to go again \n";
		
		highscores << "Your score that round: " << points << "\n";
		int i = 0;
		std::ifstream input("Resources/highscore.txt");
		while (input >> highscore[i])
		{
			highscores << "High Score " << i + 1 << ": " << highscore[i] << "\n";
			i++;
		}
		input.close();
		uiText.setString(highscores.str());
		infoUpdate.setString(message.str());
		updateMousePositions();
	}
	
}

void Game::renderText(sf::RenderTarget& target)
{
	target.draw(uiText);
	target.draw(infoUpdate);
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
