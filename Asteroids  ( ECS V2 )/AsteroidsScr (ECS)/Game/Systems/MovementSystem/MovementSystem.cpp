#include "MovementSystem.h"
#include "../RenderingSystem/RenderingSystem.h"
#include "../CollisionSystem/CollisionSystem.h"
#include "../InputSystem/InputSystem.h"

ComponentMap<Velocity> MovementSystem::velocities;
ComponentMap<Position> MovementSystem::positions;

void MovementSystem::allocateID(const EntityID& id)
{
	positions[id] = Position{  };
	velocities[id] = Velocity{ };
}
void MovementSystem::freeID(const EntityID& id) {
	velocities.erase(id);
	positions.erase(id);
}

void MovementSystem::updatePhysics(const EntityID& id, const EntityMask& mask)
{
	auto& currentPosition = positions[id];
	auto& currentVelocity = velocities[id];
	auto& currentRect = CollisionSystem::rects[id];
	auto& currentTexture = RenderingSystem::textures[id];
	int tmp = currentPosition.node;
	auto& currentNode = CollisionSystem::nodes[currentPosition.node][id];
	auto& currentTmpNode = CollisionSystem::nodes[tmp];


	if ((mask & COMPONENT_INPUT) == COMPONENT_INPUT) {
		InputSystem::getInput(id); // const speed set to spaceship speed
	}
	if (currentVelocity.thrust) { calculateThrust(currentVelocity, currentPosition); }


	currentPosition.x += currentVelocity.dx;
	currentPosition.y += currentVelocity.dy;

	currentPosition.node = getNode(currentRect);

	if (tmp == -1) {
		currentNode = id;
	}
	else if (tmp != currentPosition.node) {
		currentNode = currentTmpNode[id];
		currentTmpNode.erase(id);
	}

	if ((mask & COMPONENT_DRIFT) == COMPONENT_DRIFT) {
		currentVelocity.dx *= 0.985f;
		currentVelocity.dy *= 0.985f;
	}
	if ((mask & COMPONENT_WALLLOOP) == COMPONENT_WALLLOOP) {
		if (currentRect.right < 0) {
			currentPosition.x = CONSOLE::WINDOW_WIDTH - ((currentRect.right - currentRect.left) / 2.0f);
		}
		if (currentRect.left > CONSOLE::WINDOW_WIDTH) {
			currentPosition.x = -(currentRect.right - currentRect.left) / 1.0f;
		}

		if (currentRect.top > CONSOLE::WINDOW_HEIGHT) {
			currentPosition.y = -(currentRect.bottom - currentRect.top);
		}
		if (currentRect.bottom < 0) {
			currentPosition.y = CONSOLE::WINDOW_HEIGHT - ((currentRect.bottom - currentRect.top) / 2.0f);
		}
		CollisionSystem::updateSingle(id);
	}
	if ((mask& COMPONENT_INFINITE_SPIN) == COMPONENT_INFINITE_SPIN) {
		currentPosition.angle += currentVelocity.rotation;
	}

	if ((mask & COMPONENT_TEXTURE) == COMPONENT_TEXTURE) {
		currentTexture.dest.x = static_cast<int>(currentPosition.x);
		currentTexture.dest.y = static_cast<int>(currentPosition.y);
	}//make sure this is used after any change in direction
	if (((mask & COMPONENT_WALLDEATH) == COMPONENT_WALLDEATH) && (currentPosition.x > CONSOLE::WINDOW_WIDTH || currentPosition.x < 0 || currentPosition.y < 0 || currentPosition.y > CONSOLE::WINDOW_HEIGHT)) {
		EntityManager::freeID(id);
	} // make sure this is last, otherwise false-calling will be used


}

void MovementSystem::calculateThrust(Velocity& currentVelocity, Position& currentPosition) {
	float speed = sqrt((currentVelocity.dx * currentVelocity.dx) + (currentVelocity.dy * currentVelocity.dy));
	if (speed > SPACESHIP::MAX_SPEED)
	{
		currentVelocity.dx *= SPACESHIP::MAX_SPEED / speed;
		currentVelocity.dy *= SPACESHIP::MAX_SPEED / speed;
	}
	currentVelocity.dx += static_cast<float>(std::cos(currentPosition.angle * 0.0174533f)) * SPACESHIP::MOVEMENT_SPEED;
	currentVelocity.dy += static_cast<float>(std::sin(currentPosition.angle * 0.0174533f)) * SPACESHIP::MOVEMENT_SPEED;
}

int columns = 10;
int cellWidth = (CONSOLE::WINDOW_WIDTH / columns);
int cellHeight = (CONSOLE::WINDOW_HEIGHT / columns);



int MovementSystem::getNode(const Rect& rect) {
	int xcell = floor(rect.center[0] / cellWidth);
	int ycell = floor(rect.center[1] / cellHeight);

	if (xcell > columns - 1) {
		xcell = columns - 1;
	}
	if (xcell < 0) {
		xcell = 0;
	}
	if (ycell > columns - 1) {
		ycell = columns - 1;
	}
	if (ycell < 0) {
		ycell = 0;
	}


	return (xcell + (ycell  * columns));
}

void MovementSystem::formatIDVelocity(EntityID& id, float dx = 0.0f, float dy = 0.0f, bool thrust = false) {
	auto& vel = MovementSystem::velocities[id];

	if (!thrust) {
		vel.dx = dx;
		vel.dy = dy;
	}
	else {
		vel.thrust = true;
	}
}

void MovementSystem::formatIDPosition(EntityID& id, float x, float y, double angle = 0.0) {
	auto& pos = MovementSystem::positions[id];
	auto& res = RenderingSystem::textures[id];

	pos.x = x;
	pos.y = y;
	res.dest.x = static_cast<int>(x);
	res.dest.y = static_cast<int>(y);
	pos.angle = angle;
}