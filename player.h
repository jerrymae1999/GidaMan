#pragma once

#include "entity.h"

//Derived class
class player :public entity
{
public:
	int movementSpeed = 1;
	int attackDamage = 2;
	int counterWalking = 0;
	int direction = 0;
	bool canMoveUp = true;
	bool canMoveDown = true;
	bool canMoveLeft = true;
	bool canMoveRight = true;
	int hp = 500; // initial hp
	int maxhp = 500;
	int gil = 0; // increases as player acquires dreamcatchers

	player();
	void update();
	void updateMovement();
};