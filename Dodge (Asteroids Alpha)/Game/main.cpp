// Template.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Game.h"
#include <Windows.h>

Game* game = nullptr;

int main(int arc, char* argv[])
{
	const int FPS = FPS_;
	const int frameDelay = 1000 / FPS;

	Uint32 frameStart;
	int frameTime;
	game = new Game("?", 1000, 800);
	SDL_ShowCursor(SDL_DISABLE);

	while (game->Running())
	{
		frameStart = SDL_GetTicks();

		game->events();
		game->update();
		game->render();

		frameTime = SDL_GetTicks() - frameStart;
		if (frameDelay > frameTime)
		{
			SDL_Delay(frameDelay - frameTime);
		}
	}

	game->clean();
    return 0;
}

