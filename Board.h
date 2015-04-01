#pragma once
#include "VisibleObject.h"

class Board : public VisibleObject
{
public:
	Board();
	~Board();

	void Update();
	void Draw(sf::RenderWindow &window);

	int CheckForLines();
	void DeleteLine(int line); // Deletes line and moves above lines down
	int getwidth();
	std::vector<std::vector<int>> getboard();
	void SetBlock(int, int);

private:
	sf::Sprite sprite;
	sf::Texture texture;
	std::vector<std::vector<int>> board; // first coordinate is y, second is x
};