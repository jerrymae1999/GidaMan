#pragma once
#include "entity.h"

//Derived class
class pickup :public entity
{
public:
	bool isToken = true;
	int dreamValue = 5;
	int heartValue = 2;
	bool destroy = false;

	pickup();
	void update();

};
