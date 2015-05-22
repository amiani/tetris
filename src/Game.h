#pragma once
#include "Board.h"
#include "Tetromino.h"

class Game
{
public:
	Game();
	~Game();

	static void start();	

private:
	static void updateAll(sf::Event currevent);
	static void drawAll(sf::RenderWindow &window);	
	static void gameLoop();

	static bool blockexists;

	static sf::Texture texture;
	static sf::Sprite background;
	static sf::RenderWindow mainwindow;

	enum GameState { Uninitialized, Setup, Paused, Playing, Exiting };
	static GameState gamestate;

	static std::vector<Tetromino> tetrominoes;
	static Board board;
	static Tetromino* activetetro;
};