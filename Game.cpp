#include "stdafx.h"
#include "Game.h"
#include "time.h"

void Game::Start()
{
	gamestate = Setup;
	srand(time(NULL));

	texture.loadFromFile("images/background.png");
	background.setTexture(texture, true);
	
	mainwindow.create(sf::VideoMode(240, 480, 32), "Tetris");
	blockexists = false;

	gamestate = Paused;
	while (gamestate != Exiting)
		GameLoop();

	delete activetetro;
	mainwindow.close();
}

void Game::UpdateAll(sf::Event currevent)
{
	for (auto &itr : tetrominoes)
		if (!itr.Update(board, currevent))
			blockexists = false;
	if (!blockexists)
		tetrominoes.pop_back();
	board.Update();
}

void Game::DrawAll(sf::RenderWindow &window)
{
	if (blockexists)
		for (auto tet : tetrominoes)
			tet.Draw(mainwindow);
	board.Draw(mainwindow);
}

void Game::GameLoop()
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
			UpdateAll(currevent);
		}
		break;
	}
	if (currevent.type == sf::Event::KeyPressed && currevent.key.code == sf::Keyboard::Escape)
		gamestate = Exiting;

	mainwindow.clear(sf::Color::White);
	mainwindow.draw(background);
	DrawAll(mainwindow);
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