#pragma once
#include "SDL.h"
#include <fstream>
#include <iostream>
#include "../../Entities/EntityManager.h"
class InputSystem
{
public:
	InputSystem()
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
	void PumpEvents();

	/**
 *  \brief Gets a button.
 *
 *  \param button Button wanting to be pressed SDL_CONTROLLER_BUTTON

 *  \return 1 if pressed, 0 if failure or not pressed.
 */
	static Sint16 GetButton(const SDL_GameControllerButton button) { return SDL_GameControllerGetButton(controller, button); }

	/**
 *  \brief Gets axis of controller.
 *
 *  \param axis Axis that needs reading. (SDL_CONTROLLER_AXIS)

 *  \return Value fo Axis.
 */
	static Sint16 GetAxis(const SDL_GameControllerAxis axis) { return SDL_GameControllerGetAxis(controller, axis); }


	static void getInput(const EntityID& id);

	static const Uint8* keys;
	static SDL_GameController* controller;
	enum MOUSE { X, Y, LEFT, RIGHT };
	int mouse[5];
	static bool controllerConnected;
};
