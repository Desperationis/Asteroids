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

//SPACESHIP SETUP

namespace SPACESHIP
{
	const float MAX_SPEED = 10.0f;
	const float MOVEMENT_SPEED = 0.15f;
	const float DRIFT = 0.985f;
}

//BULLET SETUP

namespace BULLET
{
	const float BULLET_SPEED = 100.0f;
}




