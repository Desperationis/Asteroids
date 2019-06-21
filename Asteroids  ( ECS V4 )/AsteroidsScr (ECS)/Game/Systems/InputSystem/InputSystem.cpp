#include "InputSystem.h"
#include "../MovementSystem/MovementSystem.h"

const Uint8* InputSystem::keys;
SDL_GameController* InputSystem::controller = nullptr;
bool InputSystem::controllerConnected = false, InputSystem::usingController = false;
int InputSystem::mouse[5];

void InputSystem::PumpEvents()
{
	SDL_PumpEvents();
	keys = SDL_GetKeyboardState(NULL);
	mouse[LEFT] = SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT);
	mouse[RIGHT] = SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_RIGHT);
	SDL_GetMouseState(&mouse[X], &mouse[Y]);
}

void InputSystem::getInput(const EntityID& id)
{
	auto& currentPosition = MovementSystem::positions[id];
	auto& currentVelocity = MovementSystem::velocities[id];

	if (usingController) {
		currentPosition.angle += (GetAxis(SDL_CONTROLLER_AXIS_LEFTX) / 32767.0f) * SPACESHIP::ROTATION_SPEED;
		currentVelocity.thrust = GetAxis(SDL_CONTROLLER_AXIS_TRIGGERLEFT);
	}

	if (!usingController) {
		currentVelocity.thrust = keys[SDL_SCANCODE_UP] || keys[SDL_SCANCODE_W];
		if (keys[SDL_SCANCODE_RIGHT] || keys[SDL_SCANCODE_D]) {
			currentPosition.angle += SPACESHIP::ROTATION_SPEED;
		}
		if (keys[SDL_SCANCODE_LEFT] || keys[SDL_SCANCODE_A]) {
			currentPosition.angle -= SPACESHIP::ROTATION_SPEED;
		}
	}

}
