#pragma once
#include "../../Tools/TM.h"
#include "../Entities/Entity.h"
#include "../Systems/FontSystem/FontSystem.h"

using ButtonMask = std::bitset<10>;

struct Button{
	Button() {};
	
	EntityID id = 0;
	ButtonMask mask;
	SDL_Rect dest;
	SDL_Color bg_color{ 255,255,255,255 };
};
