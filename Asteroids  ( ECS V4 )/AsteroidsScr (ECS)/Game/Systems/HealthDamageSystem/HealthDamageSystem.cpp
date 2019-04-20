#include "HealthDamageSystem.h"

ComponentMap<Damage> HealthDamageSystem::damages;
ComponentMap<Health> HealthDamageSystem::healths;

void HealthDamageSystem::attack(const EntityID& prey, const EntityID& predator) {
	healths[prey].health -= damages[predator].damage * damages[predator].multiplier;
	damages[predator].hardness--;
}

void HealthDamageSystem::allocateDamageID(const EntityID& id) {
	damages[id] = Damage{ };
}

void HealthDamageSystem::allocateHealthID(const EntityID& id) {
	healths[id] = Health{ };
}

void HealthDamageSystem::freeID(const EntityID& id) {
	healths.erase(id);
	damages.erase(id);
}