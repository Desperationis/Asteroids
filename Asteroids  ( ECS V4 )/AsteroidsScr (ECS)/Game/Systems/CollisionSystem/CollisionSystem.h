#pragma once
#include "../../Entities/EntityManager.h"

class CollisionSystem
{
public:
	void update();
	void checkCollision(const EntityID& id, const char* name);
	void checkCollisions();
	void allocateID(const EntityID& id);
	void freeID(const EntityID& id);

	static void updateSingle(const EntityID& id);
	static void formatRect(const EntityID& id, int x, int y, int w, int h);
	static void renderRect(const EntityID& id);

	template<class T> static bool CollideRect(const T& target1, const T& target2)
	{
		if (target1.left < target2.right &&
			target1.right > target2.left &&
			target1.bottom > target2.top &&
			target1.top < target2.bottom)
		{
			return true;
		}
		return false;
	}

	static ComponentMap<Rect> rects;
	static ComponentMap<ComponentMap<EntityID>> nodes;
};

