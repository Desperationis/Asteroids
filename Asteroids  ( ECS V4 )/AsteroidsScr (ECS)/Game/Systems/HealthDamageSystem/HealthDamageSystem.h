#pragma once
#include "../../Entities/EntityManager.h"

class HealthDamageSystem {
public:
	static ComponentMap<Damage> damages;
	static ComponentMap<Health> healths;

	static void attack(const EntityID& prey, const EntityID& predator);
	static void allocateDamageID(const EntityID& id);
	static void allocateHealthID(const EntityID& id);
	static void freeID(const EntityID& id);
};