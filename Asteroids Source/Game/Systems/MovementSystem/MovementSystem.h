#pragma once
#include "../../Entities/EntityManager.h"

class InputSystem;
class MovementSystem
{
public:
	void allocateID(const EntityID& id);
	void freeID(const EntityID& id);
	void updatePhysics(const EntityID& id, const EntityMask& mask);
	int getNode(const Rect& rect);

	static void formatIDVelocity(EntityID& id, float dx, float dy, bool thrust);
	static void formatIDPosition(EntityID& id, float x, float y, double angle);

	static ComponentMap<Velocity> velocities;
	static ComponentMap<Position> positions;
private:
	void calculateThrust(Velocity& currentVelocity, Position& currentPosition);
};
