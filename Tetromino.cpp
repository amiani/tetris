#include "stdafx.h"
#include "Tetromino.h"
#include "assert.h"

Tetromino::Tetromino() : shape((Shape)(rand()%7))
{
	switch(shape)
	{
	case 0:
	{
		shapematrix.resize(4, std::vector<int>(4, 0));
		for (auto &elem : shapematrix[1])
			elem = 1;

		position.x = 3;
		break;
	}
	case 1:
	{
		shapematrix.resize(2, std::vector<int>(2, 1));
		position.x = 4;
		break;
	}
	case 2:
	{
		int arr[3][3] = {{0,1,1},
						 {1,1,0},
						 {0,0,0}};
		shapematrix.resize(3);
		for (int i = 0; i != shapematrix.size(); i++)
			shapematrix[i].assign(arr[i],arr[i]+3);

		position.x = 3;
		break;
	}
	case 3:
	{
		int arr[3][3] = {{1,1,0},
						 {0,1,1},
						 {0,0,0}};
		shapematrix.resize(3);
		for (int i = 0; i != shapematrix.size(); i++)
			shapematrix[i].assign(arr[i],arr[i]+3);

		position.x = 3;
		break;
	}
	case 4:
	{
		int arr[3][3] = {{1,0,0},
						 {1,1,1},
						 {0,0,0}};
		shapematrix.resize(3);
		for (int i = 0; i != shapematrix.size(); i++)
			shapematrix[i].assign(arr[i],arr[i]+3);

		position.x = 3;
		break;
	}
	case 5:
	{
		int arr[3][3] = {{0,0,1},
						 {1,1,1},
						 {0,0,0}};
		shapematrix.resize(3);
		for (int i = 0; i != shapematrix.size(); i++)
			shapematrix[i].assign(arr[i],arr[i]+3);

		position.x = 3;
		break;
	}
	case 6:
	{
		int arr[3][3] = {{0,1,0},
						 {1,1,1},
						 {0,0,0}};
		shapematrix.resize(3);
		for (int i = 0; i != shapematrix.size(); i++)
			shapematrix[i].assign(arr[i],arr[i]+3);

		position.x = 3;
		break;
	}
	}
	position.y = 0;
	
	texture.loadFromFile("images/block2.png");
	sprite.setTexture(texture, true);
}

Tetromino::~Tetromino()
{
}

bool Tetromino::Update(Board &board, sf::Event currevent)
{
	if (!CheckCollision(board))
	{
		if (currevent.type == sf::Event::KeyPressed && currevent.key.code == sf::Keyboard::Left)
		{
			position.x--;
			if (!IsPlaceable(board, shapematrix))
				position.x++;
		}
		if (currevent.type == sf::Event::KeyPressed	&& currevent.key.code == sf::Keyboard::Right)
		{
			position.x++;
			if (!IsPlaceable(board, shapematrix))
				position.x--;
		}
		if (currevent.type == sf::Event::KeyPressed
			&& currevent.key.code == sf::Keyboard::Up && shape != 1)
			Rotate(board);

		if (clock.getElapsedTime().asSeconds() >= 0.2)
		{
			position.y++;
			clock.restart();
		}
	}
	else
	{
		for (int y = 0; y != shapematrix.size(); y++)
			for (int x = 0; x != shapematrix[0].size(); x++)
			{
				int ypos = y + position.y;
				int xpos = x + position.x;

				if (shapematrix[y][x] == 1)
					board.SetBlock(ypos, xpos);
			}

		return false;
	}

	return true;
}

void Tetromino::Draw(sf::RenderWindow &window)
{
	int blockx = 0, blocky = 0;
	
	for (int i = 0; i != shapematrix.size(); i++)
		for (int j = 0; j != shapematrix[0].size(); j++)
			if (shapematrix[i][j])
			{
				blockx = position.x + j;
				blocky = position.y + i - 2;
				sprite.setPosition(blockx*24, blocky*24);
				window.draw(sprite);
			}
}

void Tetromino::Rotate(Board board)
{
	std::vector<std::vector<int>> tempmatrix(shapematrix.size(), std::vector<int>(shapematrix.size(), 0));
	
	for (int y = 0; y != shapematrix.size(); y++)
		for (int x = 0; x != shapematrix[0].size(); x++)
			tempmatrix[x][y] = shapematrix[y][x];

	for (auto &vec : tempmatrix)
		std::reverse(vec.begin(), vec.end());

	if (IsPlaceable(board, tempmatrix))
		shapematrix = tempmatrix;
}

bool Tetromino::CheckCollision(Board board)
{
	for (int y = 0; y != shapematrix.size(); y++)
		for (int x = 0; x != shapematrix[y].size(); x++)
		{
			int ypos = y + position.y;
			int xpos = x + position.x;

			if (shapematrix[y][x] == 1)
				if (ypos == 21 || board.getboard()[ypos+1][xpos] == 1)
					return true;
		}
	
	return false;
}

bool Tetromino::IsPlaceable(Board board, std::vector<std::vector<int>> piece)
{
	for (int y = 0; y != piece.size(); y++)
		for (int x = 0; x != piece[y].size(); x++)
		{
			int ypos = y + position.y;
			int xpos = x + position.x;

			if (piece[y][x] == 1)
			{
				if (xpos >= board.getwidth() || xpos < 0)
					return false;

				if (board.getboard()[ypos][xpos] == 1)
					return false;
			}

		}

		return true;
}

sf::Texture Tetromino::texture;