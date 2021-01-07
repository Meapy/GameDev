#include "Game.h"


//private functions 
void Game::initiVariables()
{
	this->window = nullptr;
}

void Game::initWindow()
{
	this->videoMode.height = 720;
	this->videoMode.width = 1280;

	this->window = new sf::RenderWindow(this->videoMode, "Game_Title", sf::Style::Titlebar | sf::Style::Close);
}
//constuctors / destructors 
Game::Game()
{
	this->initiVariables();
	this->initWindow();
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

void Game::update()
{
	this->pollEvents();
	
}

void Game::render()
{
	window->clear();

	//draw game objects
	window->display();
}

//functions 