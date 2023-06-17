#include "enemy.h"


enemy::enemy()
{
	rect.setSize(sf::Vector2f(22, 33));
	rect.setPosition(400, 200);
	rect.setFillColor(sf::Color::Blue);
	sprite.setTextureRect(sf::IntRect(0, 0, 22, 33)); // enemy1 white lady
	sprite2.setTextureRect(sf::IntRect(0, 0, 37, 37)); // enemy2 manananggal
	sprite3.setTextureRect(sf::IntRect(0, 0, 33, 39)); // enemy3 serena
	sprite4.setTextureRect(sf::IntRect(0, 0, 27, 39)); // enemy4 dewende
}


void enemy::update()
{
	sprite.setPosition(rect.getPosition());
	sprite2.setPosition(rect.getPosition());
	sprite3.setPosition(rect.getPosition());
	sprite4.setPosition(rect.getPosition());
	text.setPosition(rect.getPosition().x - rect.getSize().x / 2, rect.getPosition().y - rect.getSize().y / 2 - 5);
}

void enemy::updateMovement()
{

	if (direction == 1)//Up
	{
		if (canMoveUp == true)
		{
			rect.move(0, -movementSpeed);
			sprite.setTextureRect(sf::IntRect(22 + 22 * counterWalking, 0, 22, 33));
			sprite2.setTextureRect(sf::IntRect(37 + 37 * counterWalking, 0, 37, 37));
			sprite3.setTextureRect(sf::IntRect(33 + 33 * counterWalking, 0, 33, 39));
			sprite4.setTextureRect(sf::IntRect(27 + 27 * counterWalking, 0, 27, 39));
			canMoveUp = true;
			canMoveDown = true;
			canMoveLeft = true;
			canMoveRight = true;
		}
	}
	else if (direction == 2)//Down
	{
		if (canMoveDown == true)
		{
			rect.move(0, movementSpeed);
			sprite.setTextureRect(sf::IntRect((22 * 2) * counterWalking, 0, 22, 33));
			sprite2.setTextureRect(sf::IntRect((37 * 2) * counterWalking, 0, 37, 37));
			sprite3.setTextureRect(sf::IntRect((33 * 2) * counterWalking, 0, 33, 39));
			sprite4.setTextureRect(sf::IntRect((27 * 2) * counterWalking, 0, 27, 39));
			canMoveUp = true;
			canMoveDown = true;
			canMoveLeft = true;
			canMoveRight = true;
		}
	}
	else if (direction == 3)//Left
	{
		if (canMoveLeft == true)
		{
			rect.move(-movementSpeed, 0);
			sprite.setTextureRect(sf::IntRect(22 + 22 * counterWalking, 0, 22, 33));
			sprite2.setTextureRect(sf::IntRect(37 + 37 * counterWalking, 0, 37, 37));
			sprite3.setTextureRect(sf::IntRect(33 + 33 * counterWalking, 0, 33, 39));
			sprite4.setTextureRect(sf::IntRect(27 + 27 * counterWalking, 0, 27, 39));
			canMoveUp = true;
			canMoveDown = true;
			canMoveLeft = true;
			canMoveRight = true;
		}
	}
	else if (direction == 4)//Right
	{
		if (canMoveRight == true)
		{
			rect.move(movementSpeed, 0);
			sprite.setTextureRect(sf::IntRect((22 * 2) * counterWalking, 0, 22, 33));
			sprite2.setTextureRect(sf::IntRect((37 * 2) * counterWalking, 0, 37, 37));
			sprite3.setTextureRect(sf::IntRect((33 * 2) * counterWalking, 0, 33, 39));
			sprite4.setTextureRect(sf::IntRect((27 * 2) * counterWalking, 0, 27, 39));
			canMoveUp = true;
			canMoveDown = true;
			canMoveLeft = true;
			canMoveRight = true;
		}
	}
	else
	{
		//No movement
	}

	counterWalking++;
	if (counterWalking == 1)
	{
		counterWalking = 0;
	}

	counter++;
	if (counter >= movementLength)
	{
		direction = generateRandom(10);
		counter = 0;
	}
}