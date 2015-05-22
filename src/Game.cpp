#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Game.h"
#include "time.h"

void Game::start()
{
	gamestate = Setup;
	srand(time(NULL));

	texture.loadFromFile("images/background.png");
	background.setTexture(texture, true);
	
	mainwindow.create(sf::VideoMode(240, 480, 32), "Tetris");
	blockexists = false;

	gamestate = Paused;
	while (gamestate != Exiting)
		gameLoop();

	delete activetetro;
	mainwindow.close();
}

void Game::updateAll(sf::Event currevent)
{
	for (auto &itr : tetrominoes)
		if (!itr.update(board, currevent))
			blockexists = false;
	if (!blockexists)
		tetrominoes.pop_back();
	board.update();
}

void Game::drawAll(sf::RenderWindow &window)
{
	if (blockexists)
		for (auto tet : tetrominoes)
			tet.draw(mainwindow);
	board.draw(mainwindow);
}

void Game::gameLoop()
{
	sf::Event currevent;
	mainwindow.pollEvent(currevent);
	switch (gamestate)
	{
	case Paused:		
		if (currevent.type == sf::Event::KeyPressed && currevent.key.code == sf::Keyboard::P)
			gamestate = Playing;

		break;

	case Playing:
		if (currevent.type == sf::Event::KeyPressed && currevent.key.code == sf::Keyboard::P)
			gamestate = Paused;
		else
		{
			if (!blockexists)
			{
				tetrominoes.push_back(Tetromino());
				blockexists = true;				
			}
			updateAll(currevent);
		}
		break;
	}
	if (currevent.type == sf::Event::KeyPressed && currevent.key.code == sf::Keyboard::Escape)
		gamestate = Exiting;

	mainwindow.clear(sf::Color::White);
	mainwindow.draw(background);
	drawAll(mainwindow);
	mainwindow.display();
}

bool Game::blockexists = false;
sf::Texture Game::texture;
sf::Sprite Game::background;
sf::RenderWindow Game::mainwindow;
Game::GameState Game::gamestate = Uninitialized;
std::vector<Tetromino> Game::tetrominoes;
Board Game::board;
Tetromino* Game::activetetro;