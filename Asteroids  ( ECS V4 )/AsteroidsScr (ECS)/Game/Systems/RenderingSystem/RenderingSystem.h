#pragma once
#include "../../Entities/EntityManager.h"

class RenderingSystem
{
public:
	static ComponentMap<Texture> textures;


	static void allocateID(const EntityID& id);
	static void freeID(const EntityID& id);
	static void renderAll();
	static void renderEntity(const EntityID& id);
	static void renderRect(const EntityID& id);
	void formatID(EntityID& id, int x, int y, int w, int h, int x2, int y2, int w2, int h2);
};
