#pragma once
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "VisibleObject.h"
#include "Board.h"

class Tetromino : public VisibleObject
{
public:
	Tetromino();
	~Tetromino();

	bool update(Board &board, sf::Event currevent);
	void draw(sf::RenderWindow &window);

private:
	void rotate(Board board);
	bool checkCollision(Board board);
	bool isPlaceable(Board board, std::vector<std::vector<int>>);

	enum Shape { I, O, S, Z, J, L, T };
	Shape shape;

	sf::Clock clock;

	static sf::Texture texture;
	sf::Sprite sprite;
	sf::Vector2i position;
	std::vector<std::vector<int>> shapematrix;
};