#pragma once
#include "../../Entities/EntityManager.h"


class MeteorSystem
{
public:
	static EntityID nameID;
	static int meteorsOnScreen;
	enum METEOR{SMALL,MEDIUM,LARGE};
	static ComponentMap<Split> sizes;
	static EntityID allocateMeteor(float x, float y, float dx, float dy, EntityMask mask, METEOR size);
	static void allocateID(const EntityID& id);
	static void splitMeteor(const EntityID& id);
	
};

struct MeteorData {
	float x = 0.0f, y = 0.0f, dx = 0.0f, dy = 0.0f;
	double angle = 0.0;
	MeteorSystem::METEOR size;
};
