#include "projectile.h"



projectile::projectile()
{
	rect.setSize(sf::Vector2f(15, 15));
	sprite.setTextureRect(sf::IntRect(0, 0, 15, 15));
}



void projectile::update()
{
	if (direction == 1)//Up
	{
		rect.move(0, -movementSpeed);
	}
	if (direction == 2)//Down
	{
		rect.move(0, movementSpeed);
	}
	if (direction == 3)//Left
	{
		rect.move(-movementSpeed, 0);
	}
	if (direction == 4)//Right
	{
		rect.move(movementSpeed, 0);
	}

	counterLifeTime++;
	if (counterLifeTime >= LifeTime)
	{
		destroy = true;
	}

	//Sprite set at Rect
	sprite.setPosition(rect.getPosition());
}