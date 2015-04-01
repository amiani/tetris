#pragma once


class VisibleObject
{
public:
	VisibleObject();
	~VisibleObject();

	virtual void Update();
	virtual void Draw(sf::RenderWindow &window);
};