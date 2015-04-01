#pragma once
#include "VisibleObject.h"
#include "Board.h"

class Tetromino : public VisibleObject
{
public:
	Tetromino();
	~Tetromino();

	bool Update(Board &board, sf::Event currevent);
	void Draw(sf::RenderWindow &window);

private:
	void Rotate(Board board);
	bool CheckCollision(Board board);
	bool IsPlaceable(Board board, std::vector<std::vector<int>>);

	enum Shape { I, O, S, Z, J, L, T };
	Shape shape;

	sf::Clock clock;

	static sf::Texture texture;
	sf::Sprite sprite;
	sf::Vector2i position;
	std::vector<std::vector<int>> shapematrix;
};