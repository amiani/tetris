#pragma once
#include "Board.h"
#include "Tetromino.h"

class Game
{
public:
	Game();
	~Game();

	static void Start();	

private:
	static void UpdateAll(sf::Event currevent);
	static void DrawAll(sf::RenderWindow &window);	
	static void GameLoop();

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