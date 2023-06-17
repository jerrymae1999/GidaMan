#pragma once
#include "entity.h"

//Derived class
class projectile :public entity
{
public:
	int movementSpeed = 10;
	int attackDamage = 1;
	int LifeTime = 15; // projectile lifetime before being destroyed

	int direction = 0;
	bool destroy = false;
	int counterLifeTime = 0;
	bool enemyProjectile = false;
	bool enemy2Projectile = false;
	bool enemy3Projectile = false;
	bool enemy4Projectile = false;


	projectile();
	void update();
};