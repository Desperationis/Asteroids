#pragma once
#include "../../Entities/EntityManager.h"

class MeteorSystem
{
public:
	EntityID nameID = 0;

	//don't reference EntityMask as it is unlikely we'll refrence from a variable
	void allocateMeteor(float x, float y, float dx, float dy, EntityMask mask);
};

