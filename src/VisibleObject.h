#pragma once
#include <SFML/Graphics.hpp>

class VisibleObject
{
public:
	VisibleObject();
	~VisibleObject();

	virtual void update();
	virtual void draw(sf::RenderWindow &window);
};