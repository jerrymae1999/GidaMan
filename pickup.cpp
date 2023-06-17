#include "pickup.h"



pickup::pickup()
{
	rect.setSize(sf::Vector2f(15, 15));
	rect.setPosition(0, 0);
	rect.setFillColor(sf::Color::Yellow);
	//sprite.setTextureRect(sf::IntRect(0, 0, 40, 40));
}

void pickup::update()
{
	sprite.setPosition(rect.getPosition());
}
