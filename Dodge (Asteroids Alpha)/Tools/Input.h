#pragma once
#include "SDL.h"

struct Input
{
	const Uint8* keys;
	
	enum MOUSE{X,Y,LEFT,RIGHT};
	int mouse[5];
	void PumpKeys() {
		SDL_PumpEvents();
		keys = SDL_GetKeyboardState(NULL);
		mouse[LEFT] = SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT);
		mouse[RIGHT] = SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_RIGHT);

		SDL_GetMouseState(&mouse[X], &mouse[Y]);
	}
};