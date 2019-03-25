#pragma once
#include "SDL.h"
#include <fstream>
#include <iostream>
struct Input
{
public:
	Input()
	{
		for (int i = 0; i < SDL_NumJoysticks(); i++)
		{
			if (SDL_IsGameController(i))
			{
				controller = SDL_GameControllerOpen(i);
				if (controller)
				{
					SDL_GameControllerGetJoystick(controller);
					std::cout << "Joystick connected: " << SDL_GameControllerName(controller) << std::endl;

					controllerConnected = true;
					break;
				}
				else
				{
					std::cout << "Could not open Game Controller " << i << " " << std::endl;
				}
			}
		}
		SDL_GameControllerEventState(SDL_IGNORE);
		std::cout << "Keyboard connected." << std::endl;
	}

	/**
 *  \brief Pumps Events to be queried.
 */
	void PumpEvents()
	{
		SDL_PumpEvents();
		keys = SDL_GetKeyboardState(NULL);
		mouse[LEFT] = SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT);
		mouse[RIGHT] = SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_RIGHT);
		SDL_GetMouseState(&mouse[X], &mouse[Y]);
	};



	/**
 *  \brief Gets a button.
 *
 *  \param button Button wanting to be pressed SDL_CONTROLLER_BUTTON

 *  \return 1 if pressed, 0 if failure or not pressed.
 */
	inline Sint16 GetButton(const SDL_GameControllerButton button)
	{
		return SDL_GameControllerGetButton(controller, button);
	}

	/**
 *  \brief Gets axis of controller.
 *
 *  \param axis Axis that needs reading. (SDL_CONTROLLER_AXIS)

 *  \return Value fo Axis.
 */
	inline Sint16 GetAxis(const SDL_GameControllerAxis axis)
	{
		return SDL_GameControllerGetAxis(controller, axis);
	}




	const Uint8* keys;
	SDL_GameController* controller = NULL;
	enum MOUSE { X, Y, LEFT, RIGHT };
	int mouse[5];
	bool controllerConnected = false;
};
