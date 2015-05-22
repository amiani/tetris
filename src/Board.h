#pragma once
#include "VisibleObject.h"

class Board : public VisibleObject
{
public:
	Board();
	~Board();

	void update();
	void draw(sf::RenderWindow &window);

	int chcekForLines();
	void deleteLine(int line); // Deletes line and moves above lines down
	int getWidth();
	std::vector<std::vector<int>> getBoard();
	void setBlock(int, int);

private:
	sf::Sprite sprite;
	sf::Texture texture;
	std::vector<std::vector<int>> board; // first coordinate is y, second is x
};