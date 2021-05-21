#pragma once
#include <bitset>

using EntityMask = std::bitset<25>; // 20 is the maxium amount of bits
using EntityID = Uint64;

class Entity
{
public:
	//mask - Details every component contained in an entity.
	//id - Details the ID of the entity for future reference.

	EntityID id = 0;
	EntityMask mask = 0;
};