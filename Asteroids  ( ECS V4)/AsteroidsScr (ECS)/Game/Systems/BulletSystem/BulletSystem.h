#pragma once
#include "../../Entities/EntityManager.h"
class BulletSystem
{
public:
	void update();
	void allocateBullet(double angleOffset);
	void recoil();
	bool timer(int delay);
	void shoot();

	Uint64 now = 0;
};

