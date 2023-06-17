#include "player.h"

player::player()
{
	rect.setSize(sf::Vector2f(40, 40));
	rect.setPosition(400, 200);
	rect.setFillColor(sf::Color::Blue);
	sprite.setTextureRect(sf::IntRect(0, 0, 40, 40));
}

void player::update()
{
	sprite.setPosition(rect.getPosition());
}

void player::updateMovement()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		if (canMoveUp = true)
		{
			rect.move(0, -movementSpeed);
			sprite.setTextureRect(sf::IntRect(counterWalking * 40, 40, 40, 40));
			direction = 1;
			canMoveUp = true;
			canMoveDown = true;
			canMoveLeft = true;
			canMoveRight = true;
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		if (canMoveDown = true)
		{
			rect.move(0, movementSpeed);
			sprite.setTextureRect(sf::IntRect(counterWalking * 40, 40 * 2, 40, 40));
			direction = 2;
			canMoveUp = true;
			canMoveDown = true;
			canMoveLeft = true;
			canMoveRight = true;
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		if (canMoveLeft = true)
		{
			rect.move(-movementSpeed, 0);
			sprite.setTextureRect(sf::IntRect(counterWalking * 40, 40 * 4, 40, 40));
			direction = 3;
			canMoveUp = true;
			canMoveDown = true;
			canMoveLeft = true;
			canMoveRight = true;
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		if (canMoveRight = true)
		{
			rect.move(movementSpeed, 0);
			sprite.setTextureRect(sf::IntRect(counterWalking * 40, 40 * 3, 40, 40));
			direction = 4;
			canMoveUp = true;
			canMoveDown = true;
			canMoveLeft = true;
			canMoveRight = true;
		}
	}
	else
	{
		//Player not Moving
	}

	counterWalking++;

	if (counterWalking == 3)
	{
		counterWalking = 0;
	}
}