#pragma once
#include "entity.h"

//Derived class
class wall :public entity
{
public:
	bool destructable = false;
	int hp = 30;
	bool destroy = false;

	wall();
	void update();
};