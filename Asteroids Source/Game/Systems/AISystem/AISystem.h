#pragma once
#include "../../Entities/EntityManager.h"

class AISystem {
public:
	enum AIType {UFO};
	enum AIState {CHASE, SHOOT, FLEE};

	static void update();
	static void allocateID(const EntityID& id);
	static void freeID(const EntityID& id);

	static ComponentMap<AIData> AI;
};