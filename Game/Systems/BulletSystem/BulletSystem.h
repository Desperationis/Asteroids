#pragma once
#include "../../Entities/EntityManager.h"
class BulletSystem
{
public:
	void update();
	static EntityID allocateBullet(double angleOffset);
	void recoil();
	bool timer(int delay, Uint64& t);
	void shoot();


	static float currentHard;
	static int currentGrapes;
	Uint64 bulletTimer = 1, now = 0;
	bool powerUp = false;
};

