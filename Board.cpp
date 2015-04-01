#include "stdafx.h"
#include "Board.h"

Board::Board()
{
	board.resize(22);
	for (auto &vec : board)           // Initialize each horiz vector with 10 zeroes
		for (int i = 0; i < 10; i++)
			vec.push_back(0);

	texture.loadFromFile("images/block.png");
	sprite.setTexture(texture, true);
}

Board::~Board()
{
}

void Board::Update()
{
	while (CheckForLines() != -1)   // Perhaps this loop could be removed
		DeleteLine(CheckForLines());
}

void Board::Draw(sf::RenderWindow &window)
{
	for (int y = 2; y != 22; y++)
		for (int x = 0; x != 10; x++)
			if (board[y][x])
			{
				sprite.setPosition(x*24, (y-2)*24);
				window.draw(sprite);
			}
}

int Board::CheckForLines()
{
	for (int y = 21; y != 1; y--) // For every horiz vector (reverse)
	{
		int result = 0;
		for (auto elem : board[y]) {// For every elem of horiz vector
			if (elem) result++;    // If elem is filled
		}

		if (result == 10) return y; // if they're all filled, we have a complete line!
	}
	return -1;                  // no complete line found
}

void Board::DeleteLine(int line)
{
	for (int i = line; i != 0; i--)
		for (int j = 0; j < 10; j++)
			board[i][j] = board[i-1][j];
}

int Board::getwidth()
{
	return board[0].size();
}

std::vector<std::vector<int>> Board::getboard()
{
	return board;
}

void Board::SetBlock(int y, int x)
{
	board[y][x] = 1;
}