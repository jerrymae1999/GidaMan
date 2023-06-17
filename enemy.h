#pragma once
#include "entity.h"
#include "random.h"

//Derived class
class enemy :public entity
{
public:
	int movementSpeed = 1;
	int movementLength = 100;
	int attackDamage = 2;
	int counterWalking = 0;
	int direction = 0;
	int counter = 0;
	int hp = 10;
	int maxhp = 10;
	bool alive = true;
	bool boss = false;

	bool canMoveUp = true;
	bool canMoveDown = true;
	bool canMoveLeft = true;
	bool canMoveRight = true;

	bool pissed = false;

	enemy();
	void update();
	void updateMovement();
};