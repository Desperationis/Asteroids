#pragma once
#include "../Entities/Entity.h"

namespace MASK_ENTITY {
	const EntityMask COMPONENT_NONE = 0;
	const EntityMask COMPONENT_POSITION = 1 << 0;
	const EntityMask COMPONENT_VELOCITY = 1 << 1;
	const EntityMask COMPONENT_TEXTURE = 1 << 2;
	const EntityMask COMPONENT_INPUT = 1 << 3;
	const EntityMask COMPONENT_DRIFT = 1 << 4;
	const EntityMask COMPONENT_WALLLOOP = 1 << 5;
	const EntityMask COMPONENT_COLLISION = 1 << 6;
	const EntityMask COMPONENT_WALLDEATH = 1 << 7;
	const EntityMask COMPONENT_INFINITE_SPIN = 1 << 8;
	const EntityMask COMPONENT_SCORE = 1 << 9;
	const EntityMask COMPONENT_HITBOX = 1 << 10;
	const EntityMask COMPONENT_HEALTH = 1 << 11;
	const EntityMask COMPONENT_DAMAGE = 1 << 12;
	const EntityMask COMPONENT_SPLIT= 1 << 13;

	const EntityMask POWERUP_RAPIDFIRE = 1 << 14;
	const EntityMask POWERUP_GRAPESHOT = 1 << 15;

	const EntityMask COMPONENT_MOVEMENT = COMPONENT_POSITION | COMPONENT_VELOCITY;
	const EntityMask COMPONENT_DUMMY = COMPONENT_MOVEMENT | COMPONENT_TEXTURE | COMPONENT_COLLISION;
	const EntityMask COMPONENT_VESSEL = COMPONENT_DUMMY | COMPONENT_INPUT | COMPONENT_DRIFT | COMPONENT_WALLLOOP | COMPONENT_SCORE | COMPONENT_HITBOX ;
	const EntityMask COMPONENT_BULLET = COMPONENT_DUMMY | COMPONENT_WALLDEATH | COMPONENT_DAMAGE | COMPONENT_HITBOX;
	const EntityMask COMPONENT_METEOR = COMPONENT_DUMMY | COMPONENT_WALLLOOP | COMPONENT_INFINITE_SPIN | COMPONENT_HITBOX | COMPONENT_HEALTH | COMPONENT_SPLIT;
}


struct Position {
	float x = 0, y = 0;
	float angle = 90.0f;
	int node = 0;
};

struct Velocity {
	float dx = 0.0f, dy = 0.0f;
	bool thrust = false;
	float rotation = 0.0f;
};

struct Texture {
	SDL_Rect dest, scr;
};

struct Name {
	std::string name = "NULL";
};

struct Rect {
	float left = 0.0f, right = 0.0f, top = 0.0f, bottom = 0.0f, center[2] = { 0.0f,0.0f };
	float hitboxScaling = 1.0f;
	double angleOfImpact = 0.0;
};

struct Score {
	Uint64 preScore = 0, score = 0;
};

struct Health {
	float health = 100.0f;
};

struct Damage {
	float damage = 50.0f;
	float multiplier = 1.0f;
	float hardness = 1;
};

struct Split {
	int size = 0;
};