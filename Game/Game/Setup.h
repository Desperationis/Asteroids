#pragma once
#include "SDL.h"
//WINDOW, RENDERER SETUP

namespace CONSOLE
{
	constexpr unsigned int WINDOW_WIDTH = 1920;
	constexpr unsigned int WINDOW_HEIGHT = 1080;

	constexpr unsigned int FPS = 60;

	const SDL_RendererFlags RENDERER_FLAGS = SDL_RENDERER_PRESENTVSYNC;
	constexpr Uint8 RENDERER_DRAWCOLOR[3] = { 0,0,0 };
}

//ENTITY SETUP

namespace ENTITY {
	constexpr unsigned int RESERVE_ENTITIES = 1;
	constexpr unsigned int BORDER_DISTANCE = 0;
}

//SPACESHIP SETUP

namespace SPACESHIP
{
	const float MAX_SPEED = 9.0f;
	const float MOVEMENT_SPEED = 0.35f;
	const float RECOIL = 0.03f;
	const float DRIFT = 0.96f;
	constexpr int ROTATION_SPEED = 5;
	constexpr int INVINCIBILITY_FRAMES = 180;
}

//BULLET SETUP

namespace BULLET
{
	const float MOVEMENT_SPEED = 20.0f;
	const int RAPIDFIRE_TICKS = 8;
	const int RAPIDFIRE_LENGTH = 300;
	//int HARDNESS = 1;
	//float DAMAGE = 25.0f;
	//float MULTIPLIER = 1.0f;
}

//METEOR SETUP

namespace METEOR_
{
	const float SPEED = 2.0f;
}



