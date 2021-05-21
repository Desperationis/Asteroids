#pragma once
#include "../Game/Game.h"
#include "../Components/EntityComponents.h"
#include "tsl/hopscotch_map.h"
#include "../stdafx.h"
#include "Entity.h"

//namespaces
template <typename Type>
using ComponentMap = tsl::hopscotch_map<EntityID, Type>;  
using namespace MASK_ENTITY;

struct MeteorData;
class EntityManager
{
public:
	EntityManager();

	void update();
	void render();
	static Entity& allocateEntity(const char* name, int x, int y, int w, int h, int x2, int y2, int w2, int h2, EntityMask flags);
	static void allocateID(Entity& entity, const char* name);
	static void allocateMemory();
	static void freeID(const EntityID& id);
	static void reset();


	static SDL_Texture* spritesheet;
	static ComponentMap<Entity> entities;
	static ComponentMap<Name> names;
	static std::vector<MeteorData> queue;

	static int nextID;
	static EntityID currentVessel;
};
