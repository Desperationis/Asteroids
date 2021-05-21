// Template.cpp : Defines the entry point for the console application.
//

#include "Game.h"


Game* game = nullptr;

int main(int arc, char* argv[])
{
	srand(static_cast<unsigned int>(time(0)));
	const int frameDelay = 1000 / CONSOLE::FPS;

	Uint32 frameStart;
	int frameTime;
	game = new Game("Asteroids", (int)CONSOLE::WINDOW_WIDTH, (int)CONSOLE::WINDOW_HEIGHT, SDL_WINDOW_FULLSCREEN);

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

